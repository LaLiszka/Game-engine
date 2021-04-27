/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include <AzCore/Component/ComponentBus.h>
#include <AzCore/Component/EntityId.h>
#include <Vegetation/Ebuses/AreaConfigRequestBus.h>

namespace Vegetation
{
    class AreaBlenderRequests
        : public AreaConfigRequests
    {
    public:
        /**
         * Overrides the default AZ::EBusTraits handler policy to allow one
         * listener only.
         */
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;

        virtual bool GetInheritBehavior() const = 0;
        virtual void SetInheritBehavior(bool value) = 0;

        virtual bool GetPropagateBehavior() const = 0;
        virtual void SetPropagateBehavior(bool value) = 0;

        virtual size_t GetNumAreas() const = 0;
        virtual AZ::EntityId GetAreaEntityId(int index) const = 0;
        virtual void RemoveAreaEntityId(int index) = 0;
        virtual void AddAreaEntityId(AZ::EntityId entityId) = 0;
    };

    using AreaBlenderRequestBus = AZ::EBus<AreaBlenderRequests>;
}
