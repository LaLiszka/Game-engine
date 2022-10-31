/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/RTTI/RTTI.h>
#include <AzCore/RTTI/ReflectContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/std/any.h>
#include <AzCore/std/containers/set.h>
#include <AzCore/std/containers/unordered_map.h>
#include <AzCore/std/string/string.h>
#include <GraphModel/Model/DataType.h>

namespace AtomToolsFramework
{
    // Contains tables of strings representing application or context specific settings for each node
    using DynamicNodeSettingsMap = AZStd::unordered_map<AZStd::string, AZStd::vector<AZStd::string>>;

    //! Contains all of the settings for an individual input or output slot on a DynamicNode
    struct DynamicNodeSlotConfig final
    {
        AZ_CLASS_ALLOCATOR(DynamicNodeSlotConfig, AZ::SystemAllocator, 0);
        AZ_RTTI(DynamicNodeSlotConfig, "{F2C95A99-41FD-4077-B9A7-B0BF8F76C2CE}");
        static void Reflect(AZ::ReflectContext* context);

        DynamicNodeSlotConfig(
            const AZStd::string& name,
            const AZStd::string& displayName,
            const AZStd::string& description,
            const AZStd::any& defaultValue,
            const AZStd::string& supportedDataTypeRegex,
            const DynamicNodeSettingsMap& settings);
        DynamicNodeSlotConfig() = default;
        ~DynamicNodeSlotConfig() = default;

        AZ::Crc32 ValidateDataTypes();
        AZStd::any GetDefaultValue() const;
        AZStd::string GetDefaultDataTypeName() const;
        GraphModel::DataTypePtr GetDefaultDataType() const;
        AZStd::vector<AZStd::string> GetSupportedDataTypeNames() const;
        GraphModel::DataTypeList GetSupportedDataTypes() const;

        //! Unique name or ID of a slot
        AZStd::string m_name = "untitled";
        //! Name displayed next to a slot in the node UI
        AZStd::string m_displayName = "untitled";
        //! Longer description display for tooltips and other UI
        AZStd::string m_description;
        //! The default value associated with a slot
        AZStd::any m_defaultValue;
        //! Regular expression for identifying the names of data types this slot can hold and connect to
        AZStd::string m_supportedDataTypeRegex;
        //! Name of the default data type from the set of supported data types if no value is assigned
        AZStd::string m_defaultDataType;
        //! Container of generic or application specific settings for a slot
        DynamicNodeSettingsMap m_settings;
        //! Specifies whether or not UI will be displayed for editing the slot value on the node
        bool m_supportsEditingOnNode = true;

    private:
        static const AZ::Edit::ElementData* GetDynamicEditData(const void* handlerPtr, const void* elementPtr, const AZ::Uuid& elementType);
    };
} // namespace AtomToolsFramework
