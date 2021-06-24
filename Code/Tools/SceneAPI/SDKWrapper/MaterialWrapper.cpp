/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <SceneAPI/SDKWrapper/MaterialWrapper.h>

namespace AZ
{
    namespace SDKMaterial
    {
        MaterialWrapper::MaterialWrapper(fbxsdk::FbxSurfaceMaterial* fbxMaterial)
            :m_fbxMaterial(fbxMaterial)
            , m_assImpMaterial(nullptr)
        {
        }

        MaterialWrapper::MaterialWrapper(aiMaterial* assImpMaterial)
            :m_fbxMaterial(nullptr)
            , m_assImpMaterial(assImpMaterial)
        {
        }

        MaterialWrapper::~MaterialWrapper()
        {
            m_fbxMaterial = nullptr;
            m_assImpMaterial = nullptr;
        }

        fbxsdk::FbxSurfaceMaterial* MaterialWrapper::GetFbxMaterial()
        {
            return m_fbxMaterial;
        }

        aiMaterial* MaterialWrapper::GetAssImpMaterial()
        {
            return m_assImpMaterial;
        }

        AZStd::string MaterialWrapper::GetName() const
        {
            return AZStd::string();
        }

        AZ::u64 MaterialWrapper::GetUniqueId() const
        {
            return uint64_t();
        }

        AZ::Vector3 MaterialWrapper::GetDiffuseColor() const
        {
            return {};
        }

        AZ::Vector3 MaterialWrapper::GetSpecularColor() const
        {
            return {};
        }

        AZ::Vector3 MaterialWrapper::GetEmissiveColor() const
        {
            return {};
        }

        float MaterialWrapper::GetOpacity() const
        {
            return {};
        }
        float MaterialWrapper::GetShininess() const
        {
            return {};
        }

        AZStd::string MaterialWrapper::GetTextureFileName([[maybe_unused]]MaterialMapType textureType) const
        {
            return AZStd::string();
        }

    }// namespace SDKMaterial
}//namespace AZ
