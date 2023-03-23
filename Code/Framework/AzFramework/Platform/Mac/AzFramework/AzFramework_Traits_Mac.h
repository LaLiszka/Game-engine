/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#define AZ_TRAIT_AZFRAMEWORK_AWS_ENABLE_TCP_KEEP_ALIVE_SUPPORTED (true)
#define AZ_TRAIT_AZFRAMEWORK_BOOTSTRAP_CFG_CURRENT_PLATFORM "osx"
#define AZ_TRAIT_AZFRAMEWORK_USE_C11_LOCALTIME_S 0
#define AZ_TRAIT_AZFRAMEWORK_USE_ERRNO_T_TYPEDEF 0
#define AZ_TRAIT_AZFRAMEWORK_USE_POSIX_LOCALTIME_R 1
#define AZ_TRAIT_AZFRAMEWORK_PYTHON_SHELL "python.sh"
#define AZ_TRAIT_AZFRAMEWORK_USE_PROJECT_MANAGER 1
#define AZ_TRAIT_AZFRAMEWORK_PROCESSLAUNCH_DEFAULT 0

// Not tested on MacOS, but for now will leave as disabled.
// On Windows it is left as disabled too, but on Linux it is necessary
// to enable, otherwise the Mouse Cursor disappears and the whole
// OS becomes unuable when debugging Lua code.
#define AZ_TRAIT_AZFRAMEWORK_SHOW_MOUSE_ON_LUA_BREAKPOINT 0
