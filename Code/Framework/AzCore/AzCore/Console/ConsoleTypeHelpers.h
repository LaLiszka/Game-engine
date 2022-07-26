/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/base.h>
#include <AzCore/Console/IConsoleTypes.h>
#include <AzCore/std/string/conversions.h>
#include <AzCore/std/string/string_view.h>

namespace AZ::ConsoleTypeHelpers
{
    //! Helper function for converting a typed value to a string representation.
    //! @param value the value instance to convert to a string
    //! @return the string representation of the value
    template <typename TYPE>
    auto ValueToString(const TYPE& value)
        -> AZStd::enable_if_t<AZStd::is_void_v<decltype(AZStd::to_string(AZStd::declval<CVarFixedString&>(), AZStd::declval<TYPE>()))>, CVarFixedString>;

    //! Helper function for converting a set of strings to a value.
    //! Must be either overloaded(preferred) or specialized for type
    //! @param outValue  the value instance to write to
    //! @param arguments the value instance to convert to a string
    //! @return boolean true on success, false if there was a conversion error
    template <typename TYPE>
    bool StringSetToValue(TYPE& outValue, const AZ::ConsoleCommandContainer& arguments) = delete;

    //! Helper function for converting a typed value to a string representation.
    //! @param outValue the value instance to write to
    //! @param string   the string to 
    //! @return boolean true on success, false if there was a conversion error
    template <typename _TYPE>
    bool StringToValue(_TYPE& outValue, AZStd::string_view string);
}

#include <AzCore/Console/ConsoleTypeHelpers.inl>
