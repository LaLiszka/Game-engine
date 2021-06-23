/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Math/Quaternion.h>
#include <AzCore/Math/Vector3.h>
#include <Tests/Printers.h>

#include <string>
#include <ostream>

namespace AZ
{
    void PrintTo(const AZ::Vector3& vector, ::std::ostream* os)
    {
        *os << '(' << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << ')';
    }

    void PrintTo(const AZ::Quaternion& quaternion, ::std::ostream* os)
    {
        *os << '(' << quaternion.GetX() << ", " << quaternion.GetY() << ", " << quaternion.GetZ() << ", " << quaternion.GetW() << ')';
    }
} // namespace AZ

namespace AZStd
{
    void PrintTo(const string& string, ::std::ostream* os)
    {
        *os << '"' << std::string(string.data(), string.size()) << '"';
    }
} // namespace AZStd

namespace MCore
{
    void PrintTo(const Quaternion& quaternion, ::std::ostream* os)
    {
        *os << "(x: " << quaternion.x
            << ", y: " << quaternion.y
            << ", z: " << quaternion.z
            << ", w: " << quaternion.w
            << ")";
    }
} // namespace MCore

namespace EMotionFX
{
    void PrintTo(const Transform& transform, ::std::ostream* os)
    {
        *os << "(pos: ";
        PrintTo(transform.mPosition, os);
        *os << ", rot: ";
        PrintTo(transform.mRotation, os);
#if !defined(EMFX_SCALE_DISABLED)
        *os << ", scale: ";
        PrintTo(transform.mScale, os);
#endif
        *os << ")";
    }
} // namespace EMotionFX
