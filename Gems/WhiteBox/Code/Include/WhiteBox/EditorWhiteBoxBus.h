/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/EBus/EBus.h>

namespace WhiteBox
{
    //! EditorWhiteBox system level requests.
    class EditorWhiteBoxRequests : public AZ::EBusTraits
    {
    public:
        // EBusTraits overrides ...
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

    protected:
        ~EditorWhiteBoxRequests() = default;
    };

    using EditorWhiteBoxRequestBus = AZ::EBus<EditorWhiteBoxRequests>;
} // namespace WhiteBox
