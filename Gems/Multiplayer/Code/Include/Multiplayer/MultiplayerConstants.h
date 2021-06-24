/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/EBus/Event.h>
#include <AzCore/Name/Name.h>
#include <AzCore/RTTI/TypeSafeIntegral.h>
#include <AzCore/std/string/fixed_string.h>
#include <AzNetworking/Serialization/ISerializer.h>
#include <AzNetworking/ConnectionLayer/ConnectionEnums.h>

namespace Multiplayer
{
    constexpr AZStd::string_view MPNetworkInterfaceName("MultiplayerNetworkInterface");
    constexpr AZStd::string_view MPEditorInterfaceName("MultiplayerEditorNetworkInterface");

    constexpr AZStd::string_view LocalHost("127.0.0.1");
    constexpr uint16_t DefaultServerPort = 30090;
    constexpr uint16_t DefaultServerEditorPort = 30091;

}

