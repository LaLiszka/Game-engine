/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */


#ifndef CRYINCLUDE_CRYCOMMON_MAESTRO_TYPES_ANIMVALUE_H
#define CRYINCLUDE_CRYCOMMON_MAESTRO_TYPES_ANIMVALUE_H
#pragma once

// **NOTE**: Do not include into the precompiled header hierarchy!

//! Values that animation track can hold.
// Do not change values! they are serialized
//
// Attention: This should only be expanded if you add a completely new value type that tracks can control!
// If you just want to control a new parameter of an entity etc. extend EParamType
//
// Note: If the param type of a track is known and valid these can be derived from the node.
//       These are serialized in case the parameter got invalid (for example for material nodes)
//
enum class AnimValue
{
    Float = 0,
    Vector = 1,
    Quat = 2,
    Bool = 3,
    Select = 5,
    Vector4 = 15,
    DiscreteFloat = 16,
    RGB = 20,
    CharacterAnim = 21,

    Unknown = static_cast<int>(0xFFFFFFFF)
};


#endif CRYINCLUDE_CRYCOMMON_MAESTRO_TYPES_ANIMVALUE_H
