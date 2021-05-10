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

#include <PhysX_precompiled.h>

#include <AzCore/Interface/Interface.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Physics/NameConstants.h>
#include <AzFramework/Physics/Common/PhysicsSimulatedBody.h>
#include <Source/EditorRigidBodyComponent.h>
#include <Source/EditorColliderComponent.h>
#include <Source/EditorShapeColliderComponent.h>
#include <Editor/Source/Components/EditorSystemComponent.h>
#include <Source/RigidBodyComponent.h>
#include <Editor/InertiaPropertyHandler.h>
#include <Editor/EditorClassConverters.h>
#include <Source/NameConstants.h>
#include <Source/Utils.h>

namespace PhysX
{
    namespace Internal
    {
        AZStd::vector<AZStd::shared_ptr<Physics::Shape>> GetCollisionShapes(AZ::Entity* entity)
        {
            AZStd::vector<AZStd::shared_ptr<Physics::Shape>> allShapes;

            const bool hasNonUniformScaleComponent = (AZ::NonUniformScaleRequestBus::FindFirstHandler(entity->GetId()) != nullptr);

            const AZStd::vector<EditorColliderComponent*> colliders = entity->FindComponents<EditorColliderComponent>();
            for (const EditorColliderComponent* collider : colliders)
            {
                const EditorProxyShapeConfig& shapeConfigurationProxy = collider->GetShapeConfiguration();
                if (shapeConfigurationProxy.IsAssetConfig() && !shapeConfigurationProxy.m_physicsAsset.m_configuration.m_asset.IsReady())
                {
                    continue;
                }

                const Physics::ColliderConfiguration colliderConfigurationScaled = collider->GetColliderConfigurationScaled();
                const Physics::ColliderConfiguration colliderConfigurationUnscaled = collider->GetColliderConfiguration();

                if (shapeConfigurationProxy.IsAssetConfig())
                {
                    AZStd::vector<AZStd::shared_ptr<Physics::Shape>> shapes;
                    Utils::GetShapesFromAsset(shapeConfigurationProxy.m_physicsAsset.m_configuration,
                        colliderConfigurationUnscaled, hasNonUniformScaleComponent, shapeConfigurationProxy.m_subdivisionLevel, shapes);

                    for (const auto& shape : shapes)
                    {
                        AZ_Assert(shape, "CreateEditorWorldRigidBody: Shape must not be null!");
                        allShapes.emplace_back(shape);
                    }
                }
                else
                {
                    const Physics::ShapeConfiguration& shapeConfiguration = shapeConfigurationProxy.GetCurrent();
                    if (!hasNonUniformScaleComponent)
                    {
                        AZStd::shared_ptr<Physics::Shape> shape = AZ::Interface<Physics::System>::Get()->CreateShape(
                            colliderConfigurationScaled, shapeConfiguration);
                        AZ_Assert(shape, "CreateEditorWorldRigidBody: Shape must not be null!");
                        if (shape)
                        {
                            allShapes.emplace_back(shape);
                        }
                    }
                    else
                    {
                        auto convexConfig = Utils::CreateConvexFromPrimitive(colliderConfigurationUnscaled, shapeConfiguration,
                            shapeConfigurationProxy.m_subdivisionLevel, shapeConfiguration.m_scale);
                        auto colliderConfigurationNoOffset = colliderConfigurationUnscaled;
                        colliderConfigurationNoOffset.m_rotation = AZ::Quaternion::CreateIdentity();
                        colliderConfigurationNoOffset.m_position = AZ::Vector3::CreateZero();

                        if (convexConfig.has_value())
                        {
                            AZStd::shared_ptr<Physics::Shape> shape = AZ::Interface<Physics::System>::Get()->CreateShape(
                                colliderConfigurationNoOffset, convexConfig.value());
                            allShapes.emplace_back(shape);
                        }
                    }
                }
            }

            const AZStd::vector<EditorShapeColliderComponent*> shapeColliders = entity->FindComponents<EditorShapeColliderComponent>();
            for (const EditorShapeColliderComponent* shapeCollider : shapeColliders)
            {
                const Physics::ColliderConfiguration& colliderConfig = shapeCollider->GetColliderConfiguration();
                const AZStd::vector<AZStd::shared_ptr<Physics::ShapeConfiguration>>& shapeConfigs =
                    shapeCollider->GetShapeConfigurations();
                for (const auto& shapeConfig : shapeConfigs)
                {
                    AZStd::shared_ptr<Physics::Shape> shape = AZ::Interface<Physics::System>::Get()->CreateShape(colliderConfig, *shapeConfig);
                    AZ_Assert(shape, "CreateEditorWorldRigidBody: Shape must not be null!");
                    allShapes.emplace_back(shape);
                }
            }

            return allShapes;
        }
    } // namespace Internal


    void EditorRigidBodyConfiguration::Reflect(AZ::ReflectContext* context)
    {
        auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
        if (serializeContext)
        {
            serializeContext->Class<EditorRigidBodyConfiguration, AzPhysics::RigidBodyConfiguration>()
                ->Version(2, &ClassConverters::EditorRigidBodyConfigVersionConverter)
                ->Field("Debug Draw Center of Mass", &EditorRigidBodyConfiguration::m_centerOfMassDebugDraw)
            ;

            AZ::EditContext* editContext = serializeContext->GetEditContext();
            if (editContext)
            {
                editContext->Class<AzPhysics::RigidBodyConfiguration>(
                    "PhysX Rigid Body Configuration", "")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::Category, "PhysX")
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_initialLinearVelocity,
                        "Initial linear velocity", "Initial linear velocity")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetInitialVelocitiesVisibility)
                        ->Attribute(AZ::Edit::Attributes::Suffix, " " + Physics::NameConstants::GetSpeedUnit())
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_initialAngularVelocity,
                        "Initial angular velocity", "Initial angular velocity (limited by maximum angular velocity)")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetInitialVelocitiesVisibility)
                        ->Attribute(AZ::Edit::Attributes::Suffix, " " + Physics::NameConstants::GetAngularVelocityUnit())

                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_linearDamping,
                        "Linear damping", "Linear damping (must be non-negative)")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetDampingVisibility)
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_angularDamping,
                        "Angular damping", "Angular damping (must be non-negative)")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetDampingVisibility)
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_sleepMinEnergy,
                        "Sleep threshold", "Kinetic energy per unit mass below which body can go to sleep (must be non-negative)")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetSleepOptionsVisibility)
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Suffix, " " + Physics::NameConstants::GetSleepThresholdUnit())
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_startAsleep,
                        "Start asleep", "The rigid body will be asleep when spawned")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetSleepOptionsVisibility)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_interpolateMotion,
                        "Interpolate motion", "Makes object motion look smoother")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetInterpolationVisibility)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_gravityEnabled,
                        "Gravity enabled", "Rigid body will be affected by gravity")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetGravityVisibility)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_kinematic,
                        "Kinematic", "Rigid body is kinematic")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetKinematicVisibility)
                    ->ClassElement(AZ::Edit::ClassElements::Group, "Continuous Collision Detection")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetCCDVisibility)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_ccdEnabled,
                        "CCD enabled", "Whether continuous collision detection is enabled for this body")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetCCDVisibility)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, AZ::Edit::PropertyRefreshLevels::EntireTree)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_ccdMinAdvanceCoefficient,
                        "Min advance coefficient", "Lower values reduce clipping but can affect simulation smoothness")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.01f)
                        ->Attribute(AZ::Edit::Attributes::Step, 0.01f)
                        ->Attribute(AZ::Edit::Attributes::Max, 0.99f)
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::IsCCDEnabled)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_ccdFrictionEnabled,
                        "CCD friction", "Whether friction is applied when CCD collisions are resolved")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::IsCCDEnabled)
                    ->ClassElement(AZ::Edit::ClassElements::Group, "") // end previous group by starting new unnamed expanded group
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_maxAngularVelocity,
                        "Maximum angular velocity", "The PhysX solver will clamp angular velocities with magnitude exceeding this value")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetMaxVelocitiesVisibility)
                        ->Attribute(AZ::Edit::Attributes::Suffix, " " + Physics::NameConstants::GetAngularVelocityUnit())

                    // Mass properties
                    ->DataElement(AZ::Edit::UIHandlers::Default, &RigidBodyConfiguration::m_computeCenterOfMass,
                        "Compute COM", "Whether to automatically compute the center of mass")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetInertiaSettingsVisibility)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, AZ::Edit::PropertyRefreshLevels::EntireTree)

                    ->DataElement(AZ::Edit::UIHandlers::Default, &RigidBodyConfiguration::m_centerOfMassOffset,
                        "COM offset", "Center of mass offset in local frame")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetCoMVisibility)
                        ->Attribute(AZ::Edit::Attributes::Suffix, " " + Physics::NameConstants::GetLengthUnit())

                    ->DataElement(AZ::Edit::UIHandlers::Default, &RigidBodyConfiguration::m_computeMass,
                        "Compute Mass", "Whether to automatically compute the mass")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetInertiaSettingsVisibility)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, AZ::Edit::PropertyRefreshLevels::EntireTree)

                    ->DataElement(AZ::Edit::UIHandlers::Default, &AzPhysics::RigidBodyConfiguration::m_mass,
                        "Mass", "The mass of the object (must be non-negative, with a value of zero treated as infinite)")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Suffix, " " + Physics::NameConstants::GetMassUnit())
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetMassVisibility)

                    ->DataElement(AZ::Edit::UIHandlers::Default, &RigidBodyConfiguration::m_computeInertiaTensor,
                        "Compute inertia", "Whether to automatically compute the inertia values based on the mass and shape of the rigid body")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetInertiaSettingsVisibility)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, AZ::Edit::PropertyRefreshLevels::EntireTree)

                    ->DataElement(Editor::InertiaHandler, &AzPhysics::RigidBodyConfiguration::m_inertiaTensor,
                        "Inertia diagonal", "Diagonal elements of the inertia tensor")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetInertiaVisibility)
                        ->Attribute(AZ::Edit::Attributes::Suffix, " " + Physics::NameConstants::GetInertiaUnit())

                    ->DataElement(AZ::Edit::UIHandlers::Default, &RigidBodyConfiguration::m_includeAllShapesInMassCalculation,
                        "Include non-simulated shapes in Mass", "If set, non-simulated shapes will also be included in the center of mass, inertia and mass calculations.")
                        ->Attribute(AZ::Edit::Attributes::Visibility, &AzPhysics::RigidBodyConfiguration::GetInertiaSettingsVisibility)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, AZ::Edit::PropertyRefreshLevels::EntireTree)
                    ;

                editContext->Class<EditorRigidBodyConfiguration>(
                    "PhysX Rigid Body Configuration", "")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::Category, "PhysX")
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &EditorRigidBodyConfiguration::m_centerOfMassDebugDraw,
                        "Debug draw COM", "Whether to debug draw the center of mass for this body")
                ;
            }
        }
    }

    void EditorRigidBodyComponent::Activate()
    {
        AzToolsFramework::Components::EditorComponentBase::Activate();
        AzFramework::EntityDebugDisplayEventBus::Handler::BusConnect(GetEntityId());
        AZ::TransformNotificationBus::Handler::BusConnect(GetEntityId());
        Physics::ColliderComponentEventBus::Handler::BusConnect(GetEntityId());
        if (auto* sceneInterface = AZ::Interface<AzPhysics::SceneInterface>::Get())
        {
            AzPhysics::SceneHandle editorSceneHandle = sceneInterface->GetSceneHandle(AzPhysics::EditorPhysicsSceneName);
            sceneInterface->RegisterSceneSimulationStartHandler(editorSceneHandle, m_sceneStartSimHandler);
        }

        m_nonUniformScaleChangedHandler = AZ::NonUniformScaleChangedEvent::Handler(
            [this](const AZ::Vector3& scale) {OnNonUniformScaleChanged(scale); });
        AZ::NonUniformScaleRequestBus::Event(GetEntityId(), &AZ::NonUniformScaleRequests::RegisterScaleChangedEvent,
            m_nonUniformScaleChangedHandler);

        if (auto* physXDebug = AZ::Interface<Debug::PhysXDebugInterface>::Get())
        {
            m_debugDisplayDataChangeHandler = Debug::DebugDisplayDataChangedEvent::Handler(
                [this](const Debug::DebugDisplayData& data)
                {
                    this->UpdateDebugDrawSettings(data);
                });
            physXDebug->RegisterDebugDisplayDataChangedEvent(m_debugDisplayDataChangeHandler);
            UpdateDebugDrawSettings(physXDebug->GetDebugDisplayData());
        }
        CreateEditorWorldRigidBody();

        AzPhysics::SimulatedBodyComponentRequestsBus::Handler::BusConnect(GetEntityId());
    }

    void EditorRigidBodyComponent::Deactivate()
    {
        m_debugDisplayDataChangeHandler.Disconnect();

        AzPhysics::SimulatedBodyComponentRequestsBus::Handler::BusDisconnect();
        m_nonUniformScaleChangedHandler.Disconnect();
        m_sceneStartSimHandler.Disconnect();
        Physics::ColliderComponentEventBus::Handler::BusDisconnect();
        AZ::TransformNotificationBus::Handler::BusDisconnect();
        AzFramework::EntityDebugDisplayEventBus::Handler::BusDisconnect();
        AzToolsFramework::Components::EditorComponentBase::Deactivate();

        if (auto* sceneInterface = AZ::Interface<AzPhysics::SceneInterface>::Get())
        {
            sceneInterface->RemoveSimulatedBody(m_editorSceneHandle, m_rigidBodyHandle);
            m_rigidBodyHandle = AzPhysics::InvalidSimulatedBodyHandle;
            m_editorBody = nullptr;
        }
    }

    void EditorRigidBodyComponent::Reflect(AZ::ReflectContext* context)
    {
        EditorRigidBodyConfiguration::Reflect(context);

        auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
        if (serializeContext)
        {
            serializeContext->Class<EditorRigidBodyComponent, AzToolsFramework::Components::EditorComponentBase>()
                ->Field("Configuration", &EditorRigidBodyComponent::m_config)
                ->Version(1)
            ;

            AZ::EditContext* editContext = serializeContext->GetEditContext();
            if (editContext)
            {
                editContext->Class<EditorRigidBodyComponent>(
                    "PhysX Rigid Body", "The entity behaves as a movable rigid object in PhysX.")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::Category, "PhysX")
                        ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/PhysXRigidBody.svg")
                        ->Attribute(AZ::Edit::Attributes::ViewportIcon, "Icons/Components/PhysXRigidBody.svg")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game", 0x232b318c))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::HelpPageURL, "https://docs.aws.amazon.com/console/lumberyard/components/physx/rigid-body")
                    ->DataElement(0, &EditorRigidBodyComponent::m_config, "Configuration", "Configuration for rigid body physics.")
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, &EditorRigidBodyComponent::CreateEditorWorldRigidBody)
                ;
            }
        }
    }

    EditorRigidBodyComponent::EditorRigidBodyComponent()
    {
        InitPhysicsTickHandler();
    }

    EditorRigidBodyComponent::EditorRigidBodyComponent(const EditorRigidBodyConfiguration& config)
        : m_config(config)
    {
        InitPhysicsTickHandler();
    }

    void EditorRigidBodyComponent::BuildGameEntity(AZ::Entity* gameEntity)
    {
        // for now use Invalid scene which will fall back on default scene when entity is activated.
        // update to correct scene once multi-scene is fully supported.
        gameEntity->CreateComponent<RigidBodyComponent>(m_config, AzPhysics::InvalidSceneHandle);
    }

    void EditorRigidBodyComponent::DisplayEntityViewport(
        [[maybe_unused]] const AzFramework::ViewportInfo& viewportInfo,
        AzFramework::DebugDisplayRequests& debugDisplay)
    {
        if (m_editorBody && m_config.m_centerOfMassDebugDraw)
        {
            debugDisplay.DepthTestOff();
            debugDisplay.SetColor(m_centerOfMassDebugColor);
            debugDisplay.DrawBall(m_editorBody->GetCenterOfMassWorld(), m_centerOfMassDebugSize);
            debugDisplay.DepthTestOn();
        }
    }

    void EditorRigidBodyComponent::CreateEditorWorldRigidBody()
    {
        if (auto* sceneInterface = AZ::Interface<AzPhysics::SceneInterface>::Get())
        {
            m_editorSceneHandle = sceneInterface->GetSceneHandle(AzPhysics::EditorPhysicsSceneName);
            if (m_editorSceneHandle == AzPhysics::InvalidSceneHandle)
            {
                AZ_Assert(false, "Attempting to create an edit time rigid body without an editor scene.");
                return;
            }
        }
        
        AZ::Transform colliderTransform = GetWorldTM();
        colliderTransform.ExtractScale();

        AzPhysics::RigidBodyConfiguration configuration;
        configuration.m_orientation = colliderTransform.GetRotation();
        configuration.m_position = colliderTransform.GetTranslation();
        configuration.m_entityId = GetEntityId();
        configuration.m_debugName = GetEntity()->GetName();
        configuration.m_centerOfMassOffset = m_config.m_centerOfMassOffset;
        configuration.m_computeCenterOfMass = m_config.m_computeCenterOfMass;
        configuration.m_computeInertiaTensor = m_config.m_computeInertiaTensor;
        configuration.m_inertiaTensor = m_config.m_inertiaTensor;
        configuration.m_simulated = false;
        configuration.m_kinematic = m_config.m_kinematic;
        configuration.m_colliderAndShapeData = Internal::GetCollisionShapes(GetEntity());

        if (auto* sceneInterface = AZ::Interface<AzPhysics::SceneInterface>::Get())
        {
            m_rigidBodyHandle = sceneInterface->AddSimulatedBody(m_editorSceneHandle, &configuration);
            m_editorBody = azdynamic_cast<AzPhysics::RigidBody*>(sceneInterface->GetSimulatedBodyFromHandle(m_editorSceneHandle, m_rigidBodyHandle));
        }

        m_editorBody->UpdateMassProperties(m_config.GetMassComputeFlags(), &m_config.m_centerOfMassOffset, &m_config.m_inertiaTensor, &m_config.m_mass);
        m_config.m_mass = m_editorBody->GetMass();
        m_config.m_centerOfMassOffset = m_editorBody->GetCenterOfMassLocal();
        m_config.m_inertiaTensor = m_editorBody->GetInverseInertiaLocal();
    }

    void EditorRigidBodyComponent::OnColliderChanged()
    {
        //recreate the rigid body when collider changes
        SetShouldBeRecreated();
    }

    void EditorRigidBodyComponent::OnTransformChanged([[maybe_unused]]const AZ::Transform& local, [[maybe_unused]]const AZ::Transform& world)
    {
        SetShouldBeRecreated();
    }

    void EditorRigidBodyComponent::OnNonUniformScaleChanged([[maybe_unused]] const AZ::Vector3& scale)
    {
        SetShouldBeRecreated();
    }

    void EditorRigidBodyComponent::InitPhysicsTickHandler()
    {
        m_sceneStartSimHandler = AzPhysics::SceneEvents::OnSceneSimulationStartHandler([this](
            [[maybe_unused]] AzPhysics::SceneHandle sceneHandle,
            [[maybe_unused]] float fixedDeltatime
            )
            {
                this->PrePhysicsTick();
            }, aznumeric_cast<int32_t>(AzPhysics::SceneEvents::PhysicsStartFinishSimulationPriority::Components));
    }

    void EditorRigidBodyComponent::PrePhysicsTick()
    {
        if (m_shouldBeRecreated)
        {
            if (auto* sceneInterface = AZ::Interface<AzPhysics::SceneInterface>::Get())
            {
                sceneInterface->RemoveSimulatedBody(m_editorSceneHandle, m_rigidBodyHandle);
                m_rigidBodyHandle = AzPhysics::InvalidSimulatedBodyHandle;
                m_editorBody = nullptr;

                CreateEditorWorldRigidBody();
            }
            m_shouldBeRecreated = false;
        }
    }

    void EditorRigidBodyComponent::EnablePhysics()
    {
        if (!IsPhysicsEnabled())
        {
            m_editorBody->SetSimulationEnabled(true);
        }
    }

    void EditorRigidBodyComponent::DisablePhysics()
    {
        m_editorBody->SetSimulationEnabled(false);
    }

    bool EditorRigidBodyComponent::IsPhysicsEnabled() const
    {
        return m_editorBody && m_editorBody->m_simulating;
    }

    AZ::Aabb EditorRigidBodyComponent::GetAabb() const
    {
        if (m_editorBody)
        {
            return m_editorBody->GetAabb();
        }
        return AZ::Aabb::CreateNull();
    }

    AzPhysics::SimulatedBody* EditorRigidBodyComponent::GetSimulatedBody()
    {
        return m_editorBody;
    }

    AzPhysics::SimulatedBodyHandle EditorRigidBodyComponent::GetSimulatedBodyHandle() const
    {
        return m_rigidBodyHandle;
    }

    AzPhysics::SceneQueryHit EditorRigidBodyComponent::RayCast(const AzPhysics::RayCastRequest& request)
    {
        if (m_editorBody)
        {
            return m_editorBody->RayCast(request);
        }
        return AzPhysics::SceneQueryHit();
    }

    void EditorRigidBodyComponent::UpdateDebugDrawSettings(const Debug::DebugDisplayData& data)
    {
        m_centerOfMassDebugColor = data.m_centerOfMassDebugColor;
        m_centerOfMassDebugSize = data.m_centerOfMassDebugSize;
    }

    const AzPhysics::RigidBody* EditorRigidBodyComponent::GetRigidBody() const
    {
        return m_editorBody;
    }

    void EditorRigidBodyComponent::SetShouldBeRecreated()
    {
        if (!m_shouldBeRecreated)
        {
            m_shouldBeRecreated = true;
        }
    }
} // namespace PhysX
