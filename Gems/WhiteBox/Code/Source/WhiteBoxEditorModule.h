/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include "WhiteBoxModule.h"

namespace WhiteBox
{
    class WhiteBoxEditorModule : public WhiteBoxModule
    {
    public:
        AZ_CLASS_ALLOCATOR_DECL
        AZ_RTTI(EditorWhiteBoxModule, "{DAB2F46E-29A1-4898-9D4B-EB0EA41BDA32}", WhiteBoxModule);

        WhiteBoxEditorModule();
        ~WhiteBoxEditorModule();

        // WhiteBoxModule ...
        AZ::ComponentTypeList GetRequiredSystemComponents() const override;
    };
} // namespace WhiteBox
