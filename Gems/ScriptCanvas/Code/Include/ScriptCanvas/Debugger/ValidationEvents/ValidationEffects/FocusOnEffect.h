/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/RTTI/RTTI.h>
#include <AzCore/Component/EntityId.h>

#include <ScriptCanvas/Variable/VariableCore.h>

namespace ScriptCanvas
{
    class FocusOnEntityEffect
    {
    public:
        AZ_RTTI(FocusOnEntityEffect, "{583D7B85-6088-4C44-A254-70B04F294BB4}");
        AZ_CLASS_ALLOCATOR(FocusOnEntityEffect, AZ::SystemAllocator, 0);

        FocusOnEntityEffect() = default;
        virtual ~FocusOnEntityEffect() = default;

        virtual AZ::EntityId GetFocusTarget() const = 0;
    };
}
