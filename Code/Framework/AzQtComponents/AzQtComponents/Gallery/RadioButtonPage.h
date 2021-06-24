/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#if !defined(Q_MOC_RUN)
#include <QWidget>
#include <QScopedPointer>
#endif

namespace Ui {
    class RadioButtonPage;
}

class RadioButtonPage : public QWidget
{
    Q_OBJECT

public:
    explicit RadioButtonPage(QWidget* parent = nullptr);
    ~RadioButtonPage() override;

private:
    QScopedPointer<Ui::RadioButtonPage> ui;
};


