/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <Atom/RPI.Reflect/Material/MaterialVersionUpdate.h>
#include <Atom/RPI.Reflect/Material/MaterialAsset.h>
#include <AzCore/Serialization/SerializeContext.h>

namespace AZ
{
    namespace RPI
    {
        void MaterialVersionUpdate::Reflect(ReflectContext* context)
        {
            if (auto* serializeContext = azrtti_cast<SerializeContext*>(context))
            {
                serializeContext->Class<MaterialVersionUpdate::RenamePropertyAction>()
                    ->Version(1)
                    ->Field("From", &MaterialVersionUpdate::RenamePropertyAction::m_fromPropertyId)
                    ->Field("To", &MaterialVersionUpdate::RenamePropertyAction::m_toPropertyId)
                    ;

                serializeContext->RegisterGenericType<MaterialVersionUpdate::Actions>();

                serializeContext->Class<MaterialVersionUpdate>()
                    ->Version(1)
                    ->Field("ToVersion", &MaterialVersionUpdate::m_toVersion)
                    ->Field("Actions", &MaterialVersionUpdate::m_actions)
                    ;
            }
        }

        MaterialVersionUpdate::MaterialVersionUpdate(uint32_t toVersion)
            : m_toVersion(toVersion)
        {
        }

        uint32_t MaterialVersionUpdate::GetVersion() const
        {
            return m_toVersion;
        }

        void MaterialVersionUpdate::SetVersion(uint32_t toVersion)
        {
            m_toVersion = toVersion;
        }

        bool MaterialVersionUpdate::ApplyVersionUpdates(MaterialAsset& materialAsset) const
        {
            bool changesWereApplied = false;

            for (auto& propertyName : materialAsset.m_propertyNames)
            {
                for (const auto& action : m_actions)
                {
                    if (propertyName == action.m_fromPropertyId)
                    {
                        propertyName = action.m_toPropertyId;
                        changesWereApplied = true;
                    }
                }
            }

            return changesWereApplied;
        }

        const AZ::RPI::MaterialVersionUpdate::Actions& MaterialVersionUpdate::GetActions() const
        {
            return m_actions;
        }

        void MaterialVersionUpdate::AddAction(const RenamePropertyAction& action)
        {
            m_actions.push_back(action);
        }
    } // namespace RPI
} // namespace AZ
