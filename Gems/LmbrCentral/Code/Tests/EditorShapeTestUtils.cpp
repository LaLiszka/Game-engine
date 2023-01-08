/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <EditorShapeTestUtils.h>
#include <AzToolsFramework/Entity/EditorEntityHelpers.h>
#include <LmbrCentral/Shape/ShapeComponentBus.h>
#include <Shape/EditorSphereShapeComponent.h>

namespace LmbrCentral
{
    // use a large tolerance for manipulator tests, because accuracy is limited by viewport resolution
    static constexpr float ManipulatorTolerance = 0.1f;

    void DragMouse(
        const AzFramework::CameraState& cameraState,
        AzManipulatorTestFramework::ImmediateModeActionDispatcher* actionDispatcher,
        const AZ::Vector3& worldStart,
        const AZ::Vector3& worldEnd,
        const AzToolsFramework::ViewportInteraction::KeyboardModifier keyboardModifier)
    {
        const auto screenStart = AzFramework::WorldToScreen(worldStart, cameraState);
        const auto screenEnd = AzFramework::WorldToScreen(worldEnd, cameraState);

        actionDispatcher
            ->CameraState(cameraState)
            ->MousePosition(screenStart)
            ->KeyboardModifierDown(keyboardModifier)
            ->MouseLButtonDown()
            ->MousePosition(screenEnd)
            ->MouseLButtonUp();
    }

    void EnterComponentMode(AZ::Entity* entity, const AZ::Uuid& componentType)
    {
        AzToolsFramework::SelectEntity(entity->GetId());
        AzToolsFramework::ComponentModeFramework::ComponentModeSystemRequestBus::Broadcast(
            &AzToolsFramework::ComponentModeFramework::ComponentModeSystemRequestBus::Events::AddSelectedComponentModesOfType,
            componentType);
    }
} // namespace LmbrCentral
