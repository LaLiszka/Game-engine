#
# Copyright (c) Contributors to the Open 3D Engine Project
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

ly_add_external_target(
    NAME glad_vulkan
    VERSION 2.0.0-beta
    3RDPARTY_ROOT_DIRECTORY ${LY_ROOT_FOLDER}/Gems/Atom/RHI/Vulkan/External/glad
    INCLUDE_DIRECTORIES include
)
