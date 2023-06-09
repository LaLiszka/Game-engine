/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Settings/SettingsRegistryVisitorUtils.h>


namespace AZ::SettingsRegistryVisitorUtils
{
    // Field Visitor implementation
    FieldVisitor::FieldVisitor() = default;
    FieldVisitor::FieldVisitor(VisitFieldType visitFieldType)
        : m_visitFieldType{ visitFieldType }
    {
    }

    auto FieldVisitor::Traverse(const AZ::SettingsRegistryInterface::VisitArgs& visitArgs,
        VisitAction action) -> VisitResponse
    {
        // A default response skip prevents visiting grand children(depth 2 or lower)
        VisitResponse visitResponse = VisitResponse::Skip;
        if (action == VisitAction::Begin)
        {
            // Invoke FieldVisitor override if the root path has been set
            if (m_rootPath.has_value())
            {
                // Only check the VisitResponse of Done to halt iteration
                if (VisitResponse fieldResponse = Visit(visitArgs);
                    fieldResponse == VisitResponse::Done)
                {
                    visitResponse = VisitResponse::Done;
                }
            }
            // To make sure only the direct children are visited(depth 1)
            // set the root path once and set the VisitResponse
            // to Continue to recurse into is fields
            if (!m_rootPath.has_value())
            {
                bool visitableFieldType{};
                switch (m_visitFieldType)
                {
                case VisitFieldType::Array:
                    visitableFieldType = visitArgs.m_type.m_type == AZ::SettingsRegistryInterface::Type::Array;
                    break;
                case VisitFieldType::Object:
                    visitableFieldType = visitArgs.m_type.m_type == AZ::SettingsRegistryInterface::Type::Object;
                    break;
                case VisitFieldType::ArrayOrObject:
                    visitableFieldType = visitArgs.m_type.m_type == AZ::SettingsRegistryInterface::Type::Array
                        || visitArgs.m_type.m_type == AZ::SettingsRegistryInterface::Type::Object;
                    break;
                default:
                    AZ_Error("FieldVisitor", false, "The field visitation type value is invalid");
                    break;
                }

                if (visitableFieldType)
                {
                    m_rootPath = visitArgs.m_jsonKeyPath;
                    visitResponse = VisitResponse::Continue;
                }
            }
        }
        else if (action == VisitAction::Value)
        {
            // Invoke FieldVisitor override if the root path has been set
            if (m_rootPath.has_value())
            {
                // Only check the VisitResponse of Done to halt iteration
                if (VisitResponse fieldResponse = Visit(visitArgs);
                    fieldResponse == VisitResponse::Done)
                {
                    visitResponse = VisitResponse::Done;
                }
            }
        }
        else if (action == VisitAction::End)
        {
            // Reset m_rootPath back to null when the root path has finished being visited
            if (m_rootPath.has_value() && *m_rootPath == visitArgs.m_jsonKeyPath)
            {
                m_rootPath = AZStd::nullopt;
            }
        }


        return visitResponse;
    }

    // Array Visitor implementation
    ArrayVisitor::ArrayVisitor()
        : FieldVisitor(VisitFieldType::Array)
    {
    }

    // Object Visitor implementation
    ObjectVisitor::ObjectVisitor()
        : FieldVisitor(VisitFieldType::Object)
    {
    }

    // Generic VisitField Callback implemention
    template <typename BaseVisitor>
    bool VisitFieldCallback(AZ::SettingsRegistryInterface& settingsRegistry, const VisitorCallback& visitCallback, AZStd::string_view path)
    {
        struct VisitFieldVisitor
            : BaseVisitor
        {
            using BaseVisitor::Visit;
            VisitFieldVisitor(const VisitorCallback& visitCallback)
                : m_visitCallback{ visitCallback }
            {}

            AZ::SettingsRegistryInterface::VisitResponse Visit(const AZ::SettingsRegistryInterface::VisitArgs& visitArgs) override
            {
                return m_visitCallback(visitArgs);
            }

            const VisitorCallback& m_visitCallback;
        };

        VisitFieldVisitor visitor{ visitCallback };
        return settingsRegistry.Visit(visitor, path);
    }

    // VisitField implementation
    bool VisitField(AZ::SettingsRegistryInterface& settingsRegistry, const VisitorCallback& visitCallback, AZStd::string_view path)
    {
        return VisitFieldCallback<FieldVisitor>(settingsRegistry, visitCallback, path);
    }

    // VisitArray implementation
    bool VisitArray(AZ::SettingsRegistryInterface& settingsRegistry, const VisitorCallback& visitCallback, AZStd::string_view path)
    {
        return VisitFieldCallback<ArrayVisitor>(settingsRegistry, visitCallback, path);
    }

    // VisitObject implementation
    bool VisitObject(AZ::SettingsRegistryInterface& settingsRegistry, const VisitorCallback& visitCallback, AZStd::string_view path)
    {
        return VisitFieldCallback<ObjectVisitor>(settingsRegistry, visitCallback, path);
    }
}
