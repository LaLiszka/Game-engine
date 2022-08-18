/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Memory/OSAllocator.h>

namespace AZ
{
    //=========================================================================
    // OSAllocator
    // [9/2/2009]
    //=========================================================================
    OSAllocator::OSAllocator()
        : AllocatorBase(this)
        , m_custom(nullptr)
        , m_numAllocatedBytes(0)
    {
    }

    //=========================================================================
    // ~OSAllocator
    // [9/2/2009]
    //=========================================================================
    OSAllocator::~OSAllocator()
    {
    }

    //=========================================================================
    // Create
    // [9/2/2009]
    //=========================================================================
    bool OSAllocator::Create(const Descriptor& desc)
    {
        m_custom = desc.m_custom;
        m_numAllocatedBytes = 0;
        return true;
    }

    //=========================================================================
    // Destroy
    // [9/2/2009]
    //=========================================================================
    void OSAllocator::Destroy()
    {
    }

    //=========================================================================
    // GetDebugConfig
    // [10/14/2018]
    //=========================================================================
    AllocatorDebugConfig OSAllocator::GetDebugConfig()
    {
        return AllocatorDebugConfig().ExcludeFromDebugging();
    }

    //=========================================================================
    // Allocate
    // [9/2/2009]
    //=========================================================================
    OSAllocator::pointer_type
    OSAllocator::allocate(size_type byteSize, size_type alignment)
    {
        OSAllocator::pointer_type address;
        if (m_custom)
        {
            address = m_custom->allocate(byteSize, alignment);
        }
        else
        {
            address = AZ_OS_MALLOC(byteSize, alignment);
        }

        if (address == nullptr && byteSize > 0)
        {
            AZ_Printf("Memory", "======================================================\n");
            AZ_Printf("Memory", "OSAllocator run out of system memory!\nWe can't track the debug allocator, since it's used for tracking and pipes trought the OS... here are the other allocator status:\n");
            OnOutOfMemory(byteSize, alignment);
        }

        m_numAllocatedBytes += byteSize;

        return address;
    }

    //=========================================================================
    // DeAllocate
    // [9/2/2009]
    //=========================================================================
    void OSAllocator::deallocate(pointer_type ptr, size_type byteSize, size_type alignment)
    {
        (void)alignment;
        if (m_custom)
        {
            m_custom->deallocate(ptr);
        }
        else
        {
            AZ_OS_FREE(ptr);
        }

        m_numAllocatedBytes -= byteSize;
    }

}
