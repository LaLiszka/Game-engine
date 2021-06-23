/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "OperatorArithmetic.h"
#include <ScriptCanvas/Libraries/Core/MethodUtility.h>
#include <ScriptCanvas/Core/Contracts/MathOperatorContract.h>
#include <AzCore/Math/MathUtils.h>

#include <ScriptCanvas/Utils/SerializationUtils.h>

namespace ScriptCanvas
{
    namespace Nodes
    {
        namespace Operators
        {
            bool OperatorArithmetic::OperatorArithmeticVersionConverter(AZ::SerializeContext& serializeContext, AZ::SerializeContext::DataElementNode& classElement)
            {
                if (classElement.GetVersion() < Version::RemoveOperatorBase)
                {
                    // Remove OperatorBase
                    if (!SerializationUtils::RemoveBaseClass(serializeContext, classElement))
                    {
                        return false;
                    }

                    classElement.RemoveElementByName(AZ_CRC("m_unary", 0x1ddbd40d));
                }

                return true;
            }

            void OperatorArithmetic::OnSlotDisplayTypeChanged(const SlotId& slotId, const Data::Type& dataType)
            {
                if (dataType.IsValid())
                {
                    Slot* slot = GetSlot(slotId);

                    if (slot->IsInput() && !slot->IsVariableReference())
                    {
                        InitializeSlot(slot->GetId(), dataType);
                    }
                }
            }

            void OperatorArithmetic::OnDynamicGroupDisplayTypeChanged(const AZ::Crc32& dynamicGroup, const Data::Type&)
            {
                if (dynamicGroup == GetArithmeticDynamicTypeGroup())
                {
                    UpdateArithmeticSlotNames();
                }
            }

            void OperatorArithmetic::OnInputSignal([[maybe_unused]] const SlotId& slotId)
            {
                AZ_PROFILE_FUNCTION(AZ::Debug::ProfileCategory::ScriptCanvas);

                if (!m_scrapedInputs)
                    {
                    m_scrapedInputs = true;

                        AZStd::vector< Slot* > groupedSlots = GetSlotsWithDynamicGroup(GetArithmeticDynamicTypeGroup());

                    SlotId fallbackId;

                        for (Slot* groupedSlot : groupedSlots)
                        {
                            if (groupedSlot->IsInput())
                            {
                                SlotId groupedSlotId = groupedSlot->GetId();

                            if (!fallbackId.IsValid())
                                {
                                fallbackId = groupedSlotId;
                            }

                            if ((groupedSlot->IsVariableReference() && groupedSlot->GetVariableReference().IsValid()) || IsConnected(groupedSlotId) || IsValidArithmeticSlot(groupedSlotId))
                            {
                                const Datum* inputDatum = groupedSlot->FindDatum();

                                if (inputDatum && inputDatum->GetType().IsValid() && inputDatum->GetType().GetType() != Data::eType::BehaviorContextObject)
                                {
                                    m_applicableInputs.emplace_back(inputDatum);
                                }
                                }
                            }
                            else if (groupedSlot->IsOutput())
                            {
                            m_resultSlot = groupedSlot;
                            }

                        m_outSlot = GetSlotByName("Out")->GetId();
                    }

                    // If none of our inputs are valid input slots. Just use the first one we found to fall into a default use case.
                    if (m_applicableInputs.empty())
                    {
                        const Datum* inputDatum = FindDatum(fallbackId);

                        if (inputDatum && inputDatum->GetType().IsValid())
                        {
                            m_applicableInputs.emplace_back(inputDatum);
                        }
                            }

                    if (!m_applicableInputs.empty())
                    {
                        const Datum* datum = m_applicableInputs.front();
                        m_result.SetType(datum->GetType());
                        }
                    }

                    InvokeOperator();
                }

            void OperatorArithmetic::OnConfigured()
            {
                auto slotList = GetSlotsWithDynamicGroup(GetArithmeticDynamicTypeGroup());

                // If we have no dynamically grouped slots. Add in our defaults.
                if (slotList.empty())
                {
                    CreateSlot("Value", "An operand to use in performing the specified Operation", ConnectionType::Input);
                    CreateSlot("Value", "An operand to use in performing the specified Operation", ConnectionType::Input);

                    CreateSlot("Result", "The result of the specified operation", ConnectionType::Output);
                }
            }

            void OperatorArithmetic::OnInit()
            {
                // Version conversion for previous elements                
                for (Slot& currentSlot : ModSlots())
                {                    
                    if (currentSlot.IsData())
                    {
                        auto& contracts = currentSlot.GetContracts();

                        for (auto& currentContract : contracts)
                        {
                            MathOperatorContract* contract = azrtti_cast<MathOperatorContract*>(currentContract.get());

                            if (contract)
                            {
                                if (contract->HasOperatorFunction())
                                {
                                    contract->SetSupportedOperator(OperatorFunction());
                                    contract->SetSupportedNativeTypes(GetSupportedNativeDataTypes());
                                }
                            }                            
                        }

                        if (!currentSlot.IsDynamicSlot())
                        {
                            currentSlot.SetDynamicDataType(DynamicDataType::Value);
                        }

                        currentSlot.SetDisplayGroup(GetArithmeticDisplayGroup());

                        if (currentSlot.GetDynamicGroup() != GetArithmeticDynamicTypeGroup())
                        {
                            SetDynamicGroup(currentSlot.GetId(), GetArithmeticDynamicTypeGroup());
                        }
                    }
                }
            }

            void OperatorArithmetic::OnActivate()
            {
                if (m_scrapedInputs)
            {
                    m_scrapedInputs = false;
                    m_applicableInputs.clear();

                    m_result.ReconfigureDatumTo(AZStd::move(ScriptCanvas::Datum()));                    
                }
            }

            void OperatorArithmetic::ConfigureVisualExtensions()
            {
            {
                    VisualExtensionSlotConfiguration visualExtensions(VisualExtensionSlotConfiguration::VisualExtensionType::ExtenderSlot);

                    visualExtensions.m_name = "Add Operand";
                    visualExtensions.m_tooltip = "Adds a new operand for the operator";

                    visualExtensions.m_displayGroup = GetArithmeticDisplayGroup();
                    visualExtensions.m_identifier = GetArithmeticExtensionId();

                    visualExtensions.m_connectionType = ConnectionType::Input;

                    RegisterExtension(visualExtensions);
                }
            }

            SlotId OperatorArithmetic::HandleExtension(AZ::Crc32 extensionId)
            {
                if (extensionId == GetArithmeticExtensionId())
                {
                    SlotId retVal = CreateSlot("Value", "An operand to use in performing the specified Operation", ConnectionType::Input);
                    UpdateArithmeticSlotNames();

                    return retVal;
                }

                return SlotId();
            }

            bool OperatorArithmetic::CanDeleteSlot(const SlotId& slotId) const
            {
                Slot* slot = GetSlot(slotId);            

                if (slot && slot->GetDynamicGroup() == GetArithmeticDynamicTypeGroup())
                {
                    if (!slot->IsOutput())
                    {                        
                        auto slotList = GetSlotsWithDynamicGroup(GetArithmeticDynamicTypeGroup());

                        int inputCount = 0;

                        for (Slot* slotElement : slotList)
                        {
                            if (slotElement->IsInput())
                            {
                                ++inputCount;
                            }
                        }

                        // Only allow removal if our input count if greater then 2 to maintain our
                        // visual expectation.
                        return inputCount > 2;
                    }
                }

                return false;
            }

            void OperatorArithmetic::Evaluate(const ArithmeticOperands& operands, Datum& result)
            {
                if (operands.empty())
                {
                    return;
                }
                else if (operands.size() == 1)
                {
                const Datum* operand = operands.front();
                    result = (*operand);
                    return;
                }

                auto type = result.GetType();
                    Operator(type.GetType(), operands, result);
                }

            void OperatorArithmetic::Operator(Data::eType type, const ArithmeticOperands& operands, Datum& result)
            {
                AZ_UNUSED(type);
                AZ_UNUSED(operands);
                AZ_UNUSED(result);
            }

            void OperatorArithmetic::InitializeSlot(const SlotId& slotId, const Data::Type& dataType)
            {
                AZ_UNUSED(slotId);
                AZ_UNUSED(dataType);
            }

            void OperatorArithmetic::InvokeOperator()
            {
                if (!m_result.GetType().IsValid())
                {
                    return;
                }

                Evaluate(m_applicableInputs, m_result);

                PushOutput(m_result, (*m_resultSlot));

                SignalOutput(m_outSlot);
            }

            SlotId OperatorArithmetic::CreateSlot(AZStd::string_view name, AZStd::string_view toolTip, ConnectionType connectionType)
            {
                DynamicDataSlotConfiguration slotConfiguration;

                slotConfiguration.m_name = name;
                slotConfiguration.m_toolTip = toolTip;
                slotConfiguration.SetConnectionType(connectionType);

                ContractDescriptor operatorMethodContract;
                operatorMethodContract.m_createFunc = [this]() -> MathOperatorContract* {
                    auto mathContract = aznew MathOperatorContract(OperatorFunction());
                    mathContract->SetSupportedNativeTypes(GetSupportedNativeDataTypes());
                    return mathContract;
                };

                slotConfiguration.m_contractDescs.push_back(AZStd::move(operatorMethodContract));

                slotConfiguration.m_displayGroup = GetArithmeticDisplayGroup();
                slotConfiguration.m_dynamicGroup = GetArithmeticDynamicTypeGroup();
                slotConfiguration.m_dynamicDataType = DynamicDataType::Any;

                slotConfiguration.m_addUniqueSlotByNameAndType = false;

                SlotId slotId = AddSlot(slotConfiguration);
                InitializeSlot(slotId, GetDisplayType(GetArithmeticDynamicTypeGroup()));

                return slotId;
            }

            void OperatorArithmetic::UpdateArithmeticSlotNames()
            {
                Data::Type displayType = GetDisplayType(GetArithmeticDynamicTypeGroup());

                if (displayType.IsValid())
                {
                    AZStd::string dataTypeName = Data::GetName(displayType);
                    SetSourceNames(dataTypeName, "Result");
                }
                else
                {
                    SetSourceNames("Value", "Result");
                }
            }

            void OperatorArithmetic::SetSourceNames(const AZStd::string& inputName, const AZStd::string& outputName)
            {
                AZStd::vector< Slot* > groupedSlots = GetSlotsWithDynamicGroup(GetArithmeticDynamicTypeGroup());
                for (Slot* slot : groupedSlots)
                {
                    if (slot)
                    {
                        if (!slot->IsData())
                        {
                            AZ_Assert(false, "%s", "Unknown Source Slot type for Arithmetic Operator. Cannot perform rename.");
                        }
                        else if (slot->IsInput())
                        {
                            slot->Rename(inputName);
                        }
                        else if (slot->IsOutput())
                        {
                            slot->Rename(outputName);
                        }
                    }
                }
            }

            bool OperatorArithmetic::IsValidArithmeticSlot(const SlotId& slotId) const
            {
                const Datum* datum = FindDatum(slotId);
                return (datum != nullptr);
            }

            AZ::Outcome<DependencyReport, void> OperatorArithmetic::GetDependencies() const
            {
                return AZ::Success(DependencyReport{});
            }
        }
    }
}
