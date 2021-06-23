/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include "Descriptor.h"

#include <QJsonDocument>
#include <QJsonObject>

namespace News
{
    //! JsonDescriptor assumes Resource is a JSON file
    class JsonDescriptor
        : public Descriptor
    {
    public:
        explicit JsonDescriptor(Resource& resource);

    protected:
        QJsonDocument m_doc;
        QJsonObject m_json;
    };
}
