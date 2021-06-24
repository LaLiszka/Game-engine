/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

// include required files
#include <AzCore/std/typetraits/integral_constant.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>
#include "StandardHeaders.h"
#include "MultiThreadManager.h"


namespace MCore
{
    /**
     * The reference counter class.
     */
    class MCORE_API MemoryObject
    {
    public:
        /**
         * The constructor.
         * Sets the initial reference count to 1.
         */
        MemoryObject();

        /**
         * The destructor.
         */
        virtual ~MemoryObject();

        /**
         * Increase the reference count by one.
         */
        void IncreaseReferenceCount();

        /**
         * Decrease the reference count.
         * The Destroy method already calls this.
         */
        void DecreaseReferenceCount();

        /**
         * Destroy the object, like you would delete it.
         * This internally decreases the reference count. It will only really delete once the reference count reaches zero.
         */
        void Destroy();

        /**
         * Get the current reference count on this object.
         * @return The reference count, which indicates how many objects reference this one.
         */
        uint32 GetReferenceCount() const;

    protected:
        virtual void Delete();

    private:
        AtomicUInt32    mReferenceCount;
    };



    /**
     * A little helper to destroy a given memory object.
     * Internally this just checks if the object is nullptr or not, and only calls Destroy on the object if it is not nullptr.
     * This does NOT set the object to nullptr afterwards!
     * @param object The object to be destroyed.
     */
    MCORE_API void Destroy(MemoryObject* object);

    template<typename T>
    using MemoryObjectUniquePtr = AZStd::unique_ptr<T, AZStd::integral_constant<decltype(&Destroy), &Destroy>>;
}   // namespace MCore
