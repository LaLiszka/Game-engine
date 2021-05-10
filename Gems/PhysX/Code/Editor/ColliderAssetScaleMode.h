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

#pragma once

#include "ColliderSubComponentMode.h"
#include <AzToolsFramework/Manipulators/ScaleManipulators.h>

namespace PhysX
{
    /// Sub component mode for modifying the asset scale on a collider in the viewport.
    class ColliderAssetScaleMode
        : public PhysX::ColliderSubComponentMode
    {
    public:
        AZ_CLASS_ALLOCATOR_DECL

        ColliderAssetScaleMode();

        // ColliderSubComponentMode ...
        void Setup(const AZ::EntityComponentIdPair& idPair) override;
        void Refresh(const AZ::EntityComponentIdPair& idPair) override;
        void Teardown(const AZ::EntityComponentIdPair& idPair) override;
        void ResetValues(const AZ::EntityComponentIdPair& idPair) override;

    private:

        void OnManipulatorDown(const AZ::EntityComponentIdPair& idPair);
        void OnManipulatorMoved(const AZ::Vector3& scale, const AZ::EntityComponentIdPair& idPair);

        AZ::Vector3 m_initialScale;
        AzToolsFramework::ScaleManipulators m_dimensionsManipulators;
    };
} //namespace PhysX
