/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <Atom/RPI.Edit/Common/AssetUtils.h>
#include <Atom/RPI.Edit/Material/MaterialPropertyId.h>
#include <Atom/RPI.Edit/Material/MaterialTypeSourceData.h>
#include <Atom/RPI.Edit/Material/MaterialUtils.h>

#include <Atom/Document/MaterialDocumentRequestBus.h>

#include <AtomToolsFramework/DynamicProperty/DynamicPropertyGroup.h>
#include <AtomToolsFramework/Inspector/InspectorPropertyGroupWidget.h>
#include <AtomToolsFramework/Util/MaterialPropertyUtil.h>

#include <Source/Window/MaterialInspector/MaterialInspector.h>

namespace MaterialEditor
{
    MaterialInspector::MaterialInspector(QWidget* parent)
        : AtomToolsFramework::InspectorWidget(parent)
    {
        MaterialDocumentNotificationBus::Handler::BusConnect();
    }

    MaterialInspector::~MaterialInspector()
    {
        MaterialDocumentNotificationBus::Handler::BusDisconnect();
        AtomToolsFramework::InspectorRequestBus::Handler::BusDisconnect();
    }

    void MaterialInspector::Reset()
    {
        m_documentPath.clear();
        m_documentId = AZ::Uuid::CreateNull();
        m_groups = {};

        AtomToolsFramework::InspectorRequestBus::Handler::BusDisconnect();
        AtomToolsFramework::InspectorWidget::Reset();
    }

    void MaterialInspector::OnDocumentOpened(const AZ::Uuid& documentId)
    {
        AddGroupsBegin();

        m_documentId = documentId;

        bool isOpen = false;
        MaterialDocumentRequestBus::EventResult(isOpen, m_documentId, &MaterialDocumentRequestBus::Events::IsOpen);

        MaterialDocumentRequestBus::EventResult(m_documentPath, m_documentId, &MaterialDocumentRequestBus::Events::GetAbsolutePath);

        if (!m_documentId.IsNull() && isOpen)
        {
            // Create the top group for displaying details about the material
            AddDetailsGroup();
            // Create groups for displaying editable UV names
            AddUvNamesGroup();
            // Create groups for displaying editable properties
            AddPropertiesGroup();

            AtomToolsFramework::InspectorRequestBus::Handler::BusConnect(m_documentId);
        }

        AddGroupsEnd();
    }

    void MaterialInspector::AddDetailsGroup()
    {
        const AZ::RPI::MaterialTypeSourceData* materialTypeSourceData = nullptr;
        MaterialDocumentRequestBus::EventResult(materialTypeSourceData, m_documentId, &MaterialDocumentRequestBus::Events::GetMaterialTypeSourceData);

        const AZStd::string groupNameId = "details";
        const AZStd::string groupDisplayName = "Details";
        const AZStd::string groupDescription = materialTypeSourceData->m_description;
        auto& group = m_groups[groupNameId];

        AtomToolsFramework::DynamicProperty property;
        MaterialDocumentRequestBus::EventResult(property, m_documentId, &MaterialDocumentRequestBus::Events::GetProperty, AZ::Name("details.materialType"));
        group.m_properties.push_back(property);

        property = {};
        MaterialDocumentRequestBus::EventResult(property, m_documentId, &MaterialDocumentRequestBus::Events::GetProperty, AZ::Name("details.parentMaterial"));
        group.m_properties.push_back(property);

        // Passing in same group as main and comparison instance to enable custom value comparison for highlighting modified properties
        const AZ::Crc32 saveStateKey(
            AZStd::string::format("MaterialInspector::PropertyGroup::%s::%s", m_documentPath.c_str(), groupDisplayName.c_str()));
        auto propertyGroupWidget = new AtomToolsFramework::InspectorPropertyGroupWidget(
            &group, &group, group.TYPEINFO_Uuid(), this, this, saveStateKey,
            [this](const AzToolsFramework::InstanceDataNode* source, const AzToolsFramework::InstanceDataNode* target) {
                AZ_UNUSED(source);
                const AtomToolsFramework::DynamicProperty* property = AtomToolsFramework::FindDynamicPropertyForInstanceDataNode(target);
                return property && AtomToolsFramework::ArePropertyValuesEqual(property->GetValue(), property->GetConfig().m_parentValue);
            });
        AddGroup(groupNameId, groupDisplayName, groupDescription, propertyGroupWidget);
    }

    void MaterialInspector::AddUvNamesGroup()
    {
        AZ::Data::Asset<AZ::RPI::MaterialAsset> materialAsset;
        MaterialDocumentRequestBus::EventResult(materialAsset, m_documentId, &MaterialDocumentRequestBus::Events::GetAsset);

        const AZStd::string groupNameId = UvGroupName;
        const AZStd::string groupDisplayName = "UV Names";
        const AZStd::string groupDescription = "UV set names in this material, which can be renamed to match those in the model.";
        auto& group = m_groups[groupNameId];

        const auto& uvNameMap = materialAsset->GetMaterialTypeAsset()->GetUvNameMap();
        group.m_properties.reserve(uvNameMap.size());

        for (const auto& uvNamePair : uvNameMap)
        {
            AtomToolsFramework::DynamicProperty property;
            MaterialDocumentRequestBus::EventResult(property, m_documentId, &MaterialDocumentRequestBus::Events::GetProperty, AZ::RPI::MaterialPropertyId(groupNameId, uvNamePair.m_shaderInput.ToString()).GetFullName());
            group.m_properties.push_back(property);

            property.SetValue(property.GetConfig().m_parentValue);
        }

        // Passing in same group as main and comparison instance to enable custom value comparison for highlighting modified properties
        const AZ::Crc32 saveStateKey(
            AZStd::string::format("MaterialInspector::PropertyGroup::%s::%s", m_documentPath.c_str(), groupDisplayName.c_str()));
        auto propertyGroupWidget = new AtomToolsFramework::InspectorPropertyGroupWidget(
            &group, &group, group.TYPEINFO_Uuid(), this, this, saveStateKey,
            [this](const AzToolsFramework::InstanceDataNode* source, const AzToolsFramework::InstanceDataNode* target) {
                AZ_UNUSED(source);
                const AtomToolsFramework::DynamicProperty* property = AtomToolsFramework::FindDynamicPropertyForInstanceDataNode(target);
                return property && AtomToolsFramework::ArePropertyValuesEqual(property->GetValue(), property->GetConfig().m_parentValue);
            });
        AddGroup(groupNameId, groupDisplayName, groupDescription, propertyGroupWidget);
    }

    void MaterialInspector::AddPropertiesGroup()
    {
        const AZ::RPI::MaterialTypeSourceData* materialTypeSourceData = nullptr;
        MaterialDocumentRequestBus::EventResult(materialTypeSourceData, m_documentId, &MaterialDocumentRequestBus::Events::GetMaterialTypeSourceData);

        for (const auto& groupDefinition : materialTypeSourceData->GetGroupDefinitionsInDisplayOrder())
        {
            const AZStd::string& groupNameId = groupDefinition.m_nameId;
            const AZStd::string& groupDisplayName = !groupDefinition.m_displayName.empty() ? groupDefinition.m_displayName : groupNameId;
            const AZStd::string& groupDescription = !groupDefinition.m_description.empty() ? groupDefinition.m_description : groupDisplayName;
            auto& group = m_groups[groupNameId];

            const auto& propertyLayout = materialTypeSourceData->m_propertyLayout;
            const auto& propertyListItr = propertyLayout.m_properties.find(groupNameId);
            if (propertyListItr != propertyLayout.m_properties.end())
            {
                group.m_properties.reserve(propertyListItr->second.size());
                for (const auto& propertyDefinition : propertyListItr->second)
                {
                    AtomToolsFramework::DynamicProperty property;
                    MaterialDocumentRequestBus::EventResult(property, m_documentId, &MaterialDocumentRequestBus::Events::GetProperty, AZ::RPI::MaterialPropertyId(groupNameId, propertyDefinition.m_nameId).GetFullName());
                    group.m_properties.push_back(property);
                }
            }

            // Passing in same group as main and comparison instance to enable custom value comparison for highlighting modified properties
            const AZ::Crc32 saveStateKey(
                AZStd::string::format("MaterialInspector::PropertyGroup::%s::%s", m_documentPath.c_str(), groupDisplayName.c_str()));
            auto propertyGroupWidget = new AtomToolsFramework::InspectorPropertyGroupWidget(
                &group, &group, group.TYPEINFO_Uuid(), this, this, saveStateKey,
                [this](const AzToolsFramework::InstanceDataNode* source, const AzToolsFramework::InstanceDataNode* target) {
                    AZ_UNUSED(source);
                    const AtomToolsFramework::DynamicProperty* property = AtomToolsFramework::FindDynamicPropertyForInstanceDataNode(target);
                    return property && AtomToolsFramework::ArePropertyValuesEqual(property->GetValue(), property->GetConfig().m_parentValue);
                });
            AddGroup(groupNameId, groupDisplayName, groupDescription, propertyGroupWidget);
        }
    }

    void MaterialInspector::OnDocumentPropertyValueModified(const AZ::Uuid& documentId, const AtomToolsFramework::DynamicProperty& property)
    {
        for (auto& groupPair : m_groups)
        {
            for (auto& reflectedProperty : groupPair.second.m_properties)
            {
                if (reflectedProperty.GetId() == property.GetId())
                {
                    if (!AtomToolsFramework::ArePropertyValuesEqual(reflectedProperty.GetValue(), property.GetValue()))
                    {
                        reflectedProperty.SetValue(property.GetValue());
                        AtomToolsFramework::InspectorRequestBus::Event(documentId, &AtomToolsFramework::InspectorRequestBus::Events::RefreshGroup, groupPair.first);
                    }
                    return;
                }
            }
        }
    }

    void MaterialInspector::OnDocumentPropertyConfigModified(const AZ::Uuid& documentId, const AtomToolsFramework::DynamicProperty& property)
    {
        for (auto& groupPair : m_groups)
        {
            for (auto& reflectedProperty : groupPair.second.m_properties)
            {
                if (reflectedProperty.GetId() == property.GetId())
                {
                    // Visibility changes require the entire reflected property editor tree for this group to be rebuilt
                    if (reflectedProperty.GetVisibility() != property.GetVisibility())
                    {
                        reflectedProperty.SetConfig(property.GetConfig());
                        AtomToolsFramework::InspectorRequestBus::Event(documentId, &AtomToolsFramework::InspectorRequestBus::Events::RebuildGroup, groupPair.first);
                    }
                    else
                    {
                        reflectedProperty.SetConfig(property.GetConfig());
                        AtomToolsFramework::InspectorRequestBus::Event(documentId, &AtomToolsFramework::InspectorRequestBus::Events::RefreshGroup, groupPair.first);
                    }
                    return;
                }
            }
        }
    }

    void MaterialInspector::BeforePropertyModified(AzToolsFramework::InstanceDataNode* pNode)
    {
        // For some reason the reflected property editor notifications are not symmetrical
        // This function is called continuously anytime a property changes until the edit has completed
        // Because of that, we have to track whether or not we are continuing to edit the same property to know when editing has started and ended
        const AtomToolsFramework::DynamicProperty* property = AtomToolsFramework::FindDynamicPropertyForInstanceDataNode(pNode);
        if (property)
        {
            if (m_activeProperty != property)
            {
                m_activeProperty = property;
                MaterialDocumentRequestBus::Event(m_documentId, &MaterialDocumentRequestBus::Events::BeginEdit);
            }
        }
    }

    void MaterialInspector::AfterPropertyModified(AzToolsFramework::InstanceDataNode* pNode)
    {
        const AtomToolsFramework::DynamicProperty* property = AtomToolsFramework::FindDynamicPropertyForInstanceDataNode(pNode);
        if (property)
        {
            if (m_activeProperty == property)
            {
                MaterialDocumentRequestBus::Event(m_documentId, &MaterialDocumentRequestBus::Events::SetPropertyValue,
                    property->GetId(), property->GetValue());
            }
        }
    }

    void MaterialInspector::SetPropertyEditingComplete(AzToolsFramework::InstanceDataNode* pNode)
    {
        // As above, there are symmetrical functions on the notification interface for when editing begins and ends and has been completed but they are not being called following that pattern.
        // when this function executes the changes to the property are ready to be committed or reverted
        const AtomToolsFramework::DynamicProperty* property = AtomToolsFramework::FindDynamicPropertyForInstanceDataNode(pNode);
        if (property)
        {
            if (m_activeProperty == property)
            {
                MaterialDocumentRequestBus::Event(m_documentId, &MaterialDocumentRequestBus::Events::SetPropertyValue,
                    property->GetId(), property->GetValue());

                MaterialDocumentRequestBus::Event(m_documentId, &MaterialDocumentRequestBus::Events::EndEdit);
                m_activeProperty = nullptr;
            }
        }
    }
} // namespace MaterialEditor

#include <Source/Window/MaterialInspector/moc_MaterialInspector.cpp>
