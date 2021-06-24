/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#ifndef CRYINCLUDE_EDITOR_UTIL_IMAGEBT_H
#define CRYINCLUDE_EDITOR_UTIL_IMAGEBT_H
#pragma once

#include "Util/Image.h"

class SANDBOX_API CImageBT
{
public:
    bool Load(const QString& fileName, CFloatImage& outImage);
    bool Save(const QString& fileName, const CFloatImage& image);
};


#endif // CRYINCLUDE_EDITOR_UTIL_IMAGEBT_H
