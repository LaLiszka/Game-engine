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

#include <Multiplayer/Components/NetworkTransformComponent.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/EBus/IEventScheduler.h>
#include <AzFramework/Components/TransformComponent.h>

namespace Multiplayer
{
    void NetworkTransformComponent::NetworkTransformComponent::Reflect(AZ::ReflectContext* context)
    {
        AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
        if (serializeContext)
        {
            serializeContext->Class<NetworkTransformComponent, NetworkTransformComponentBase>()
                ->Version(1);
        }
        NetworkTransformComponentBase::Reflect(context);
    }

    NetworkTransformComponent::NetworkTransformComponent()
        : m_rotationEventHandler([this](const AZ::Quaternion& rotation) { OnRotationChangedEvent(rotation); })
        , m_translationEventHandler([this](const AZ::Vector3& translation) { OnTranslationChangedEvent(translation); })
        , m_scaleEventHandler([this](float scale) { OnScaleChangedEvent(scale); })
        , m_resetCountEventHandler([this](const uint8_t&) { OnResetCountChangedEvent(); })
        , m_entityPreRenderEventHandler([this](float deltaTime, float blendFactor) { OnPreRender(deltaTime, blendFactor); })
    {
        ;
    }

    void NetworkTransformComponent::OnInit()
    {
        ;
    }

    void NetworkTransformComponent::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        RotationAddEvent(m_rotationEventHandler);
        TranslationAddEvent(m_translationEventHandler);
        ScaleAddEvent(m_scaleEventHandler);
        ResetCountAddEvent(m_resetCountEventHandler);
        GetNetBindComponent()->AddEntityPreRenderEventHandler(m_entityPreRenderEventHandler);

        // When coming into relevance, reset all blending factors so we don't interpolate to our start position
        OnResetCountChangedEvent();
    }

    void NetworkTransformComponent::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        ;
    }

    void NetworkTransformComponent::OnRotationChangedEvent(const AZ::Quaternion& rotation)
    {
        m_previousTransform.SetRotation(m_targetTransform.GetRotation());
        m_targetTransform.SetRotation(rotation);
    }

    void NetworkTransformComponent::OnTranslationChangedEvent(const AZ::Vector3& translation)
    {
        m_previousTransform.SetTranslation(m_targetTransform.GetTranslation());
        m_targetTransform.SetTranslation(translation);
    }

    void NetworkTransformComponent::OnScaleChangedEvent(float scale)
    {
        m_previousTransform.SetUniformScale(m_targetTransform.GetUniformScale());
        m_targetTransform.SetUniformScale(scale);
    }

    void NetworkTransformComponent::OnResetCountChangedEvent()
    {
        m_targetTransform.SetRotation(GetRotation());
        m_targetTransform.SetTranslation(GetTranslation());
        m_targetTransform.SetUniformScale(GetScale());
        m_previousTransform = m_targetTransform;
    }

    void NetworkTransformComponent::OnPreRender([[maybe_unused]] float deltaTime, float blendFactor)
    {
        if (!HasController())
        {
            AZ::Transform blendTransform;
            blendTransform.SetRotation(m_previousTransform.GetRotation().Slerp(m_targetTransform.GetRotation(), blendFactor));
            blendTransform.SetTranslation(m_previousTransform.GetTranslation().Lerp(m_targetTransform.GetTranslation(), blendFactor));
            blendTransform.SetScale(m_previousTransform.GetScale().Lerp(m_targetTransform.GetScale(), blendFactor));
            GetTransformComponent()->SetWorldTM(blendTransform);

            //AZLOG
            //(
            //    NET_Movement,
            //    "Blending entity to position %f x %f x %f",
            //    blendTransform.GetTranslation().GetX(),
            //    blendTransform.GetTranslation().GetY(),
            //    blendTransform.GetTranslation().GetZ()
            //);
        }
    }


    NetworkTransformComponentController::NetworkTransformComponentController(NetworkTransformComponent& parent)
        : NetworkTransformComponentControllerBase(parent)
        , m_transformChangedHandler([this](const AZ::Transform&, const AZ::Transform& worldTm) { OnTransformChangedEvent(worldTm); })
    {
        ;
    }

    void NetworkTransformComponentController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        GetParent().GetTransformComponent()->BindTransformChangedEventHandler(m_transformChangedHandler);
        OnTransformChangedEvent(GetParent().GetTransformComponent()->GetWorldTM());
    }

    void NetworkTransformComponentController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        ;
    }

    void NetworkTransformComponentController::OnTransformChangedEvent(const AZ::Transform& worldTm)
    {
        SetRotation(worldTm.GetRotation());
        SetTranslation(worldTm.GetTranslation());
        SetScale(worldTm.GetUniformScale());
    }
}
