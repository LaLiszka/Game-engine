/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <QAbstractNativeEventFilter>

namespace EMStudio
{
    class MainWindow;

    class NativeEventFilter
        : public QAbstractNativeEventFilter
    {
    public:
        NativeEventFilter(MainWindow* mainWindow)
            : QAbstractNativeEventFilter(),
            m_MainWindow(mainWindow)
        {
        }

        virtual bool nativeEventFilter(const QByteArray& /*eventType*/, void* message, long* /*result*/) Q_DECL_OVERRIDE;

    private:
        MainWindow* m_MainWindow;
    };
}
