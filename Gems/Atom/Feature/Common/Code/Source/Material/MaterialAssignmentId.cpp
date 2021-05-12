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

#include <Atom/Feature/Material/MaterialAssignmentId.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Serialization/SerializeContext.h>

namespace AZ
{
    namespace Render
    {
        void MaterialAssignmentId::Reflect(ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<MaterialAssignmentId>()
                    ->Version(1)
                    ->Field("lodIndex", &MaterialAssignmentId::m_lodIndex)
                    ->Field("materialAssetId", &MaterialAssignmentId::m_materialAssetId)
                    ;
            }

            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<MaterialAssignmentId>("MaterialAssignmentId")
                    ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                    ->Attribute(AZ::Script::Attributes::Category, "render")
                    ->Attribute(AZ::Script::Attributes::Module, "render")
                    ->Constructor()
                    ->Constructor<const MaterialAssignmentId&>()
                    ->Constructor<MaterialAssignmentLodIndex, AZ::Data::AssetId>()
                    ->Method("IsDefault", &MaterialAssignmentId::IsDefault)
                    ->Method("IsAssetOnly", &MaterialAssignmentId::IsAssetOnly)
                    ->Method("IsLodAndAsset", &MaterialAssignmentId::IsLodAndAsset)
                    ->Method("ToString", &MaterialAssignmentId::ToString)
                    ->Property("lodIndex", BehaviorValueProperty(&MaterialAssignmentId::m_lodIndex))
                    ->Property("materialAssetId", BehaviorValueProperty(&MaterialAssignmentId::m_materialAssetId))
                    ;
            }
        }

        MaterialAssignmentId::MaterialAssignmentId(MaterialAssignmentLodIndex lodIndex, const AZ::Data::AssetId& materialAssetId)
            : m_lodIndex(lodIndex)
            , m_materialAssetId(materialAssetId)
        {
        }

        MaterialAssignmentId MaterialAssignmentId::CreateDefault()
        {
            return MaterialAssignmentId(NonLodIndex, AZ::Data::AssetId());
        }

        MaterialAssignmentId MaterialAssignmentId::CreateFromAssetOnly(AZ::Data::AssetId materialAssetId)
        {
            return MaterialAssignmentId(NonLodIndex, materialAssetId);
        }

        MaterialAssignmentId MaterialAssignmentId::CreateFromLodAndAsset(
            MaterialAssignmentLodIndex lodIndex, AZ::Data::AssetId materialAssetId)
        {
            return MaterialAssignmentId(lodIndex, materialAssetId);
        }

        bool MaterialAssignmentId::IsDefault() const
        {
            return m_lodIndex == NonLodIndex && !m_materialAssetId.IsValid();
        }

        bool MaterialAssignmentId::IsAssetOnly() const
        {
            return m_lodIndex == NonLodIndex && m_materialAssetId.IsValid();
        }

        bool MaterialAssignmentId::IsLodAndAsset() const
        {
            return m_lodIndex != NonLodIndex && m_materialAssetId.IsValid();
        }

        AZStd::string MaterialAssignmentId::ToString() const
        {
            AZStd::string assetPathString;
            AZ::Data::AssetCatalogRequestBus::BroadcastResult(
                assetPathString, &AZ::Data::AssetCatalogRequests::GetAssetPathById, m_materialAssetId);
            AZ::StringFunc::Path::StripPath(assetPathString);
            AZ::StringFunc::Path::StripExtension(assetPathString);
            return AZStd::string::format("%s:%llu", assetPathString.c_str(), m_lodIndex);
        }

        size_t MaterialAssignmentId::GetHash() const
        {
            size_t seed = 0;
            AZStd::hash_combine(seed, m_lodIndex);
            AZStd::hash_combine(seed, m_materialAssetId.m_subId);
            return seed;
        }

        bool MaterialAssignmentId::operator==(const MaterialAssignmentId& rhs) const
        {
            return m_lodIndex == rhs.m_lodIndex && m_materialAssetId.m_subId == rhs.m_materialAssetId.m_subId;
        }

        bool MaterialAssignmentId::operator!=(const MaterialAssignmentId& rhs) const
        {
            return m_lodIndex != rhs.m_lodIndex || m_materialAssetId.m_subId != rhs.m_materialAssetId.m_subId;
        }
    } // namespace Render
} // namespace AZ
