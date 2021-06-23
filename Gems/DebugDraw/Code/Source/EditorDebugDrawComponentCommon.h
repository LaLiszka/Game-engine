/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

namespace DebugDraw
{
    class EditorDebugDrawComponentSettings
    {
    public:
        AZ_CLASS_ALLOCATOR(EditorDebugDrawComponentSettings, AZ::SystemAllocator, 0);
        AZ_TYPE_INFO(EditorDebugDrawComponentSettings, "{39FF3385-9AD8-4C3F-AAFF-3CBE1D76B767}");
        static void Reflect(AZ::ReflectContext* context);

        EditorDebugDrawComponentSettings();

        bool m_visibleInGame;
        bool m_visibleInEditor;
    };
}
