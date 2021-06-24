/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Module/DynamicModuleHandle.h>

namespace AZ
{
    AZStd::unique_ptr<DynamicModuleHandle> DynamicModuleHandle::Create(const char*)
    {
        AZ_Assert(false, "Dynamic modules are not supported on this platform");
        return nullptr;
    }

} // namespace AZ
