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

#include <StdAfx.h>

#include <API/ToolsApplicationAPI.h>
#include <Atom/RPI.Public/Scene.h>
#include <AtomLyIntegration/CommonFeatures/Material/MaterialComponentBus.h>
#include <AtomLyIntegration/CommonFeatures/Mesh/MeshComponentBus.h>
#include <AzCore/Asset/AssetManager.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <Editor/EditorBlastMeshDataComponent.h>

namespace Blast
{
    void EditorBlastMeshDataComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("BlastMeshDataService"));
    }

    void EditorBlastMeshDataComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC("TransformService", 0x8ee22c50));
    }

    void EditorBlastMeshDataComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        dependent.push_back(AZ_CRC("EditorVisibilityService", 0x90888caf));
    }

    void EditorBlastMeshDataComponent::GetIncompatibleServices(
        AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("BlastMeshDataService"));
    }

    void EditorBlastMeshDataComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<EditorBlastMeshDataComponent, AzToolsFramework::Components::EditorComponentBase>()
                ->Version(4)
                ->Field("Show Mesh Assets", &EditorBlastMeshDataComponent::m_showMeshAssets)
                ->Field("Mesh Assets", &EditorBlastMeshDataComponent::m_meshAssets)
                ->Field("Blast Slice", &EditorBlastMeshDataComponent::m_blastSliceAsset);

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<EditorBlastMeshDataComponent>(
                      "Blast Family Mesh Data", "Used to keep track of mesh assets for a Blast family")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "Destruction")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Editor/Icons/Components/Box.png")
                    ->Attribute(AZ::Edit::Attributes::ViewportIcon, "Editor/Icons/Components/Viewport/Box.png")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game", 0x232b318c))
                    ->Attribute(
                        AZ::Edit::Attributes::HelpPageURL,
                        "https://docs.aws.amazon.com/lumberyard/latest/userguide/component-blast-actor.html")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(
                        AZ::Edit::UIHandlers::CheckBox, &EditorBlastMeshDataComponent::m_showMeshAssets,
                        "Show mesh assets", "Allows manual editing of mesh assets")
                    ->Attribute(
                        AZ::Edit::Attributes::ChangeNotify,
                        &EditorBlastMeshDataComponent::OnMeshAssetsVisibilityChanged)
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default, &EditorBlastMeshDataComponent::m_meshAssets, "Mesh assets",
                        "Mesh assets needed for each Blast chunk")
                    ->Attribute(
                        AZ::Edit::Attributes::Visibility, &EditorBlastMeshDataComponent::GetMeshAssetsVisibility)
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, false)
                    ->Attribute(AZ::Edit::Attributes::ChangeNotify, &EditorBlastMeshDataComponent::OnMeshAssetsChanged)
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default, &EditorBlastMeshDataComponent::m_blastSliceAsset, "Blast Slice",
                        "Slice override to fill out meshes and material")
                    ->Attribute(AZ::Edit::Attributes::ChangeNotify, &EditorBlastMeshDataComponent::OnSliceAssetChanged);
            }
        }
    }

    void EditorBlastMeshDataComponent::Activate()
    {
        AZ_PROFILE_FUNCTION(AZ::Debug::ProfileCategory::System);
        OnMeshAssetsChanged();

        m_meshFeatureProcessor =
            AZ::RPI::Scene::GetFeatureProcessorForEntity<AZ::Render::MeshFeatureProcessorInterface>(GetEntityId());
        RegisterModel();

        AZ::TransformNotificationBus::Handler::BusConnect(GetEntityId());
        AZ::Render::MaterialComponentNotificationBus::Handler::BusConnect(GetEntityId());
        EditorComponentBase::Activate();
    }

    void EditorBlastMeshDataComponent::Deactivate()
    {
        AZ_PROFILE_FUNCTION(AZ::Debug::ProfileCategory::System);
        EditorComponentBase::Deactivate();
        AZ::Render::MaterialComponentNotificationBus::Handler::BusDisconnect(GetEntityId());
        AZ::TransformNotificationBus::Handler::BusDisconnect(GetEntityId());
        UnregisterModel();
    }

    void EditorBlastMeshDataComponent::OnSliceAssetChanged()
    {
        if (!m_blastSliceAsset.GetId().IsValid())
        {
            return;
        }

        using namespace AZ::Data;

        const AssetId blastAssetId = m_blastSliceAsset.GetId();
        m_blastSliceAsset =
            AssetManager::Instance().GetAsset<BlastSliceAsset>(blastAssetId, AssetLoadBehavior::QueueLoad);
        m_blastSliceAsset.BlockUntilLoadComplete();

        // load up the new mesh list
        m_meshAssets.clear();
        for (const auto& meshId : m_blastSliceAsset.Get()->GetMeshIdList())
        {
            auto meshAsset = AssetManager::Instance().GetAsset<AZ::RPI::ModelAsset>(meshId, AssetLoadBehavior::QueueLoad);
            if (meshAsset)
            {
                m_meshAssets.push_back(meshAsset);
            }
        }

        UnregisterModel();
        RegisterModel();

        AzToolsFramework::ToolsApplicationEvents::Bus::Broadcast(
            &AzToolsFramework::ToolsApplicationEvents::InvalidatePropertyDisplay, AzToolsFramework::Refresh_EntireTree);
    }

    void EditorBlastMeshDataComponent::OnMeshAssetsChanged()
    {
        for (auto& meshAsset : m_meshAssets)
        {
            meshAsset.SetAutoLoadBehavior(AZ::Data::AssetLoadBehavior::QueueLoad);
        }
        UnregisterModel();
        RegisterModel();
    }

    AZ::Crc32 EditorBlastMeshDataComponent::GetMeshAssetsVisibility() const
    {
        return m_showMeshAssets ? AZ::Edit::PropertyVisibility::Show : AZ::Edit::PropertyVisibility::Hide;
    }

    void EditorBlastMeshDataComponent::OnMeshAssetsVisibilityChanged()
    {
        AzToolsFramework::ToolsApplicationEvents::Bus::Broadcast(
            &AzToolsFramework::ToolsApplicationEvents::InvalidatePropertyDisplay, AzToolsFramework::Refresh_EntireTree);
    }

    void EditorBlastMeshDataComponent::HandleModelChange(AZ::Data::Instance<AZ::RPI::Model> model)
    {
        if (model)
        {
            AZ::Render::MeshComponentNotificationBus::Event(
                GetEntityId(), &AZ::Render::MeshComponentNotificationBus::Events::OnModelReady, model->GetModelAsset(),
                model);
            AZ::Render::MaterialReceiverNotificationBus::Event(
                GetEntityId(), &AZ::Render::MaterialReceiverNotificationBus::Events::OnMaterialAssignmentsChanged);
        }
    }

    void EditorBlastMeshDataComponent::RegisterModel()
    {
        if (m_meshFeatureProcessor && !m_meshAssets.empty() && m_meshAssets[0].GetId().IsValid())
        {
            AZ::Render::MaterialAssignmentMap materials;
            AZ::Render::MaterialComponentRequestBus::EventResult(
                materials, GetEntityId(), &AZ::Render::MaterialComponentRequests::GetMaterialOverrides);

            m_meshFeatureProcessor->ReleaseMesh(m_meshHandle);
            m_meshHandle = m_meshFeatureProcessor->AcquireMesh(m_meshAssets[0], materials);
            m_meshFeatureProcessor->ConnectModelChangeEventHandler(m_meshHandle, m_changeEventHandler);

            HandleModelChange(m_meshFeatureProcessor->GetModel(m_meshHandle));

            AZ::Transform transform = AZ::Transform::Identity();
            AZ::TransformBus::EventResult(transform, GetEntityId(), &AZ::TransformInterface::GetWorldTM);
            m_meshFeatureProcessor->SetMatrix3x4(m_meshHandle, AZ::Matrix3x4::CreateFromTransform(transform));
        }
    }

    void EditorBlastMeshDataComponent::UnregisterModel()
    {
        if (m_meshFeatureProcessor)
        {
            m_meshFeatureProcessor->ReleaseMesh(m_meshHandle);
        }
    }

    void EditorBlastMeshDataComponent::BuildGameEntity([[maybe_unused]] AZ::Entity* gameEntity)
    {
        gameEntity->CreateComponent<BlastMeshDataComponent>(m_meshAssets);
    }

    const AZ::Data::Asset<BlastSliceAsset>& EditorBlastMeshDataComponent::GetBlastSliceAsset() const
    {
        return m_blastSliceAsset;
    }

    const AZStd::vector<AZ::Data::Asset<AZ::RPI::ModelAsset>>& EditorBlastMeshDataComponent::GetMeshAssets() const
    {
        return m_meshAssets;
    }

    void EditorBlastMeshDataComponent::OnMaterialsUpdated([
        [maybe_unused]] const AZ::Render::MaterialAssignmentMap& materials)
    {
        UnregisterModel();
        RegisterModel();
    }

    void EditorBlastMeshDataComponent::OnTransformChanged(
        [[maybe_unused]] const AZ::Transform& local, const AZ::Transform& world)
    {
        if (m_meshFeatureProcessor)
        {
            m_meshFeatureProcessor->SetMatrix3x4(m_meshHandle, AZ::Matrix3x4::CreateFromTransform(world));
        }
    }
} // namespace Blast
