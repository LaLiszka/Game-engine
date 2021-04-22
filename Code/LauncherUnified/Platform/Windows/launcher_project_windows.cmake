#
# All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
# its licensors.
#
# For complete copyright and license terms please see the LICENSE at the root of this
# distribution (the "License"). All use of this software is governed by the License,
# or, if provided, by the license below or the license accompanying this file. Do not
# remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#

if (LY_MONOLITHIC_GAME) # only Atom is supported in monolithic
    set(LY_BUILD_DEPENDENCIES
        PUBLIC
            Legacy::CryRenderOther
    )
else()
    set(LY_BUILD_DEPENDENCIES
        PRIVATE
            Legacy::CryRenderD3D11
    )
endif()

set(ICON_FILE ${project_real_path}/Gem/Resources/GameSDK.ico)
if(NOT EXISTS ${ICON_FILE})
    # Try the common LauncherUnified icon instead
    set(ICON_FILE Resources/GameSDK.ico)
endif()

if(EXISTS ${ICON_FILE})
    set(target_file ${CMAKE_CURRENT_BINARY_DIR}/${project_name}.GameLauncher.rc)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/Launcher.rc.in
        ${target_file}
        @ONLY
    )
    set(LY_FILES ${target_file})
endif()
