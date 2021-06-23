/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <QApplication>

class AWSCoreEditorUIFixture
{
public:

    void SetUp()
    {
        int argc = 0;
        m_testUIApplication = new QApplication(argc, nullptr);
    }

    void TearDown()
    {
        delete m_testUIApplication;
    }

private:
    QApplication* m_testUIApplication = nullptr;
};
