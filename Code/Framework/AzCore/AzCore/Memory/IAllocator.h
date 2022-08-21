/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/base.h>
#include <AzCore/RTTI/RTTI.h>

#define AZ_ALLOCATOR_TRAITS(VALUETYPE) \
    using value_type = VALUETYPE; \
    using pointer = VALUETYPE*; \
    using size_type = AZStd::size_t; \
    using difference_type = AZStd::ptrdiff_t; \
    using align_type = AZStd::size_t; \
    using propagate_on_container_copy_assignment = AZStd::true_type; \
    using propagate_on_container_move_assignment = AZStd::true_type; \
    using allow_memory_leaks = AZStd::false_type;

#define AZ_ALLOCATOR_DEFAULT_TRAITS AZ_ALLOCATOR_TRAITS(void)

namespace AZ
{
    namespace Debug
    {
        class AllocationRecords;
    }

    namespace AllocatorStorage
    {
        template<class Allocator>
        class StoragePolicyBase;
    }

    template<class Allocator>
    class AllocatorWrapper;

    class AllocatorManager;

    /**
     * Allocator schema interface
     */
    class IAllocatorSchema
    {
    public:
        using value_type = void;
        using pointer = void*;
        using size_type = AZStd::size_t;
        using difference_type = AZStd::ptrdiff_t;
        using align_type = AZStd::size_t;
        using propagate_on_container_move_assignment = AZStd::true_type;

        IAllocatorSchema() = default;
        virtual ~IAllocatorSchema() = default;

        virtual pointer allocate(size_type byteSize, align_type alignment = 1) = 0;
        virtual void deallocate(pointer ptr, size_type byteSize = 0, align_type alignment = 0) = 0;
        virtual pointer reallocate(pointer ptr, size_type newSize, align_type newAlignment = 1) = 0;

        // Kept for backwards-compatibility reasons
        /////////////////////////////////////////////
        pointer Allocate(
            size_type byteSize,
            size_type alignment = 1,
            [[maybe_unused]] int flags = 0,
            [[maybe_unused]] const char* name = nullptr,
            [[maybe_unused]] const char* fileName = nullptr,
            [[maybe_unused]] int lineNum = 0,
            [[maybe_unused]] unsigned int suppressStackRecord = 0)
        {
            return allocate(byteSize, alignment);
        }

        void DeAllocate(pointer ptr, size_type byteSize = 0, [[maybe_unused]] size_type alignment = 0)
        {
            deallocate(ptr, byteSize);
        }

        /// Resize an allocated memory block. Returns the new adjusted size (as close as possible or equal to the requested one) or 0 (if
        /// you don't support resize at all).
        virtual size_type Resize([[maybe_unused]] pointer ptr, [[maybe_unused]] size_type newSize) = 0;

        /// Realloc an allocate memory memory block. Similar to Resize except it will move the memory block if needed. Return NULL if
        /// realloc is not supported or run out of memory.
        pointer ReAllocate(pointer ptr, size_type newSize, size_type newAlignment)
        {
            return reallocate(ptr, newSize, newAlignment);
        }

        ///
        /// Returns allocation size for given address. 0 if the address doesn't belong to the allocator.
        virtual size_type               AllocationSize(pointer ptr) = 0;
        /**
         * Call from the system when we want allocators to free unused memory.
         * IMPORTANT: This function is/should be thread safe. We can call it from any context to free memory.
         * Freeing the actual memory is optional (if you can), thread safety is a must.
         */
        virtual void                    GarbageCollect() {}

        virtual size_type               NumAllocatedBytes() const = 0;
        /// Returns the capacity of the Allocator in bytes. If the return value is 0 the Capacity is undefined (usually depends on another allocator)
        virtual size_type               Capacity() const = 0;
        /// Returns max allocation size if possible. If not returned value is 0
        virtual size_type               GetMaxAllocationSize() const { return 0; }
        /// Returns the maximum contiguous allocation size of a single allocation
        virtual size_type               GetMaxContiguousAllocationSize() const { return 0; }
        /**
         * Returns memory allocated by the allocator and available to the user for allocations.
         * IMPORTANT: this is not the overhead memory this is just the memory that is allocated, but not used. Example: the pool allocators
         * allocate in chunks. So we might be using one elements in that chunk and the rest is free/unallocated. This is the memory
         * that will be reported.
         */
        virtual size_type               GetUnAllocatedMemory(bool isPrint = false) const { (void)isPrint; return 0; }
    };

    /**
    * Standardized debug configuration for an allocator.
    */
    struct AllocatorDebugConfig
    {
        /// Sets the number of entries to omit from the top of the callstack when recording stack traces.
        AllocatorDebugConfig& StackRecordLevels(int levels) { m_stackRecordLevels = levels; return *this; }

        /// Set to true if this allocator should not have its records recorded and analyzed.
        AllocatorDebugConfig& ExcludeFromDebugging(bool exclude = true) { m_excludeFromDebugging = exclude; return *this; }

        /// Set to true if this allocator expands allocations with guard sections to detect overruns.
        AllocatorDebugConfig& UsesMemoryGuards(bool use = true) { m_usesMemoryGuards = use; return *this; }

        /// Set to true if this allocator writes into unallocated memory so it can be detected at runtime.
        AllocatorDebugConfig& MarksUnallocatedMemory(bool marks = true) { m_marksUnallocatedMemory = marks; return *this; }

        unsigned int m_stackRecordLevels = 0;
        bool m_excludeFromDebugging = false;
        bool m_usesMemoryGuards = false;
        bool m_marksUnallocatedMemory = false;
    };

    /**
     * Interface class for all allocators.
     */
    class IAllocator : public IAllocatorSchema
    {
    public:
        AZ_RTTI(IAllocator, "{0A3C59AE-169C-45F6-9423-3B8C89245E2E}");

        IAllocator(IAllocatorSchema* schema = nullptr);
        virtual ~IAllocator();

        const char* GetName() const
        {
            return RTTI_GetTypeName();
        }

        /// Returns the schema
        AZ_FORCE_INLINE IAllocatorSchema* GetSchema() const { return m_schema; };

        /// Returns the debug configuration for this allocator.
        virtual AllocatorDebugConfig GetDebugConfig() = 0;

        /// Returns a pointer to the allocation records. They might be available or not depending on the build type. \ref Debug::AllocationRecords
        virtual Debug::AllocationRecords* GetRecords() = 0;

        /// Sets the allocation records.
        virtual void SetRecords(Debug::AllocationRecords* records) = 0;

        /// Returns true if this allocator is ready to use.
        virtual bool IsReady() const = 0;

        /// Returns true if the allocator was lazily created. Exposed primarily for testing systems that need to verify the state of allocators.
        virtual bool IsLazilyCreated() const = 0;

    private:
        /// Determines whether the allocator was lazily created, possibly at static initialization.
        /// This is primarily meant to support older allocation systems, such as those used by CryEngine.
        /// Newer systems should create and destroy their allocators deliberately at program start-up and shut-down.
        virtual void SetLazilyCreated(bool lazy) = 0;

        /// Sets whether profiling calls should be made.
        /// This is primarily a performance compromise, as the profiling calls go out on an EBus that may not exist if not activated, and will
        /// result in an expensive hash lookup if that is the case.
        virtual void SetProfilingActive(bool active) = 0;

        /// Returns true if profiling calls will be made.
        virtual bool IsProfilingActive() const = 0;

        /// All conforming allocators must call PostCreate() after their custom Create() method in order to be properly registered.
        virtual void PostCreate() = 0;

        /// All conforming allocators must call PreDestroy() before their custom Destroy() method in order to be properly deregistered.
        virtual void PreDestroy() = 0;

        /// All allocators must provide their deinitialization routine here.
        virtual void Destroy() = 0;

    protected:
        IAllocatorSchema* m_schema;

        template<class Allocator>
        friend class AllocatorStorage::StoragePolicyBase;

        friend class AllocatorManager;

        template<class Allocator>
        friend class AllocatorWrapper;
    };
}

