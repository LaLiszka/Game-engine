/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/IO/FileIO.h>
#include <AzCore/IO/Path/Path.h>
#include <AzCore/Serialization/Json/JsonUtils.h>
#include <AzCore/std/any.h>

#include "Metadata.h"

namespace AzToolsFramework
{
    struct IMetadataRequests
    {
        AZ_RTTI(IMetadataRequests, "{88EB4C71-F2A5-48C6-A08B-0D6A8EB08A74}");

        virtual ~IMetadataRequests() = default;

        virtual AZStd::any Get(AZ::IO::PathView file, AZStd::string_view key) = 0;
        virtual bool Set(AZ::IO::PathView file, AZStd::string_view key, AZStd::any value) = 0;
    };

    class MetadataManager :
        public AZ ::Component,
        public AZ::Interface<IMetadataRequests>::Registrar
    {
    public:
        AZ_COMPONENT(MetadataManager, "{CB738803-3B6C-4B62-9DC2-1980D340F288}", IMetadataRequests);

        static inline constexpr const char* MetadataFileExtension = ".metadata";

        static void Reflect(AZ::ReflectContext* context)
        {
            Metadata::Reflect(context);
        }

    protected:
        void Activate() override{}
        void Deactivate() override{}

    public:
        AZStd::any Get(AZ::IO::PathView file, AZStd::string_view key) override
        {
            auto metadata = LoadFile(ToMetadataPath(file));

            if(!metadata)
            {
                return {};
            }

            return metadata->Get(key);
        }

        bool Set(AZ::IO::PathView file, AZStd::string_view key, AZStd::any value) override
        {
            auto path = ToMetadataPath(file);
            auto metadata = LoadFile(path);

            if (!metadata)
            {
                metadata = Metadata();
            }

            metadata->Set(key, value);

            //Metadata defaultClass;
            //AZ::JsonSerializerSettings settings;
            //settings.m_reporting = [](AZStd::string_view message, AZ::JsonSerializationResult::ResultCode result, AZStd::string_view /*path*/)
            //{
            //    AZ_TracePrintf("MetadataManager", AZ_STRING_FORMAT, AZ_STRING_ARG(message));

            //    return result;
            //};

            auto outcome = AZ::Utils::SaveObjectToFile(path.Native(), AZ::DataStream::ST_JSON, metadata.operator->());

            if(!outcome)
            {
                //AZ_Error("MetadataManager", false, "%s", outcome.GetError().c_str());
                return false;
            }

            return true;
        }

    private:
        AZ::IO::Path ToMetadataPath(AZ::IO::PathView file)
        {
            AZ::IO::Path path = file;

            if(path.Extension() != MetadataFileExtension)
            {
                path.ReplaceExtension(AZ::IO::PathView(AZStd::string(path.Extension().Native()) + AZStd::string(MetadataFileExtension)));
            }

            return path;
        }

        AZStd::optional<Metadata> LoadFile(AZ::IO::PathView file) const
        {
            AZ::IO::FileIOStream stream;

            if(!stream.Open(file.FixedMaxPathString().c_str(), AZ::IO::OpenMode::ModeRead))
            {
                return {};
            }

            Metadata metadata;
            bool result = AZ::Utils::LoadObjectFromStreamInPlace(stream, metadata);

            if(!result)
            {
                return {};
            }

            return metadata;
        }
    };
} // namespace AzToolsFramework
