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
#include "Atom_RHI_Vulkan_precompiled.h"
#include <RHI/SignalEvent.h>

namespace AZ
{
    namespace Vulkan
    {
        void SignalEvent::SetValue(bool ready)
        {
            AZStd::unique_lock<AZStd::mutex> lock(m_eventMutex);
            m_ready = ready;
        }

        void SignalEvent::Signal()
        {
            AZStd::unique_lock<AZStd::mutex> lock(m_eventMutex);
            m_ready = true;
            m_eventSignal.notify_all();
        }

        void SignalEvent::Wait() const
        {
            AZStd::unique_lock<AZStd::mutex> lock(m_eventMutex);
            m_eventSignal.wait(lock, [&]() { return m_ready; });
        }
    }
}
