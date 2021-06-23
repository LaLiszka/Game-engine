/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

// Description : Utility for dismissing every modal windows
#pragma once

#include <QObject>

class QDialog;

class ModalWindowDismisser
    : public QObject
{
public:
    ModalWindowDismisser();
    ~ModalWindowDismisser();

private:
    void DismissWindows();
    bool eventFilter(QObject* object, QEvent* event) override;

    std::vector<QDialog*> m_windows;
    bool m_dissmiss = false;
};
