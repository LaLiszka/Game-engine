/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "AddSuccess.h"

#include "UnitTestBus.h"

namespace ScriptCanvas
{
    namespace Nodes
    {
        namespace UnitTesting
        {
            void AddSuccess::OnInputSignal([[maybe_unused]] const SlotId& slotId)
            {
                const auto report = FindDatum(GetSlotId("Report"))->GetAs<Data::StringType>();
                ScriptCanvas::UnitTesting::Bus::Event
                    ( GetOwningScriptCanvasId()
                    , &ScriptCanvas::UnitTesting::BusTraits::AddSuccess
                    , *report);

                SignalOutput(GetSlotId("Out"));
            }
        } 
    } 
} 
