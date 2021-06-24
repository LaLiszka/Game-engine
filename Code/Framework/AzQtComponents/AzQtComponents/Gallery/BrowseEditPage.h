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
    class BrowseEditPage;
}

class BrowseEditPage : public QWidget
{
    Q_OBJECT

public:
    explicit BrowseEditPage(QWidget* parent = nullptr);
    ~BrowseEditPage() override;

private:
    QScopedPointer<Ui::BrowseEditPage> ui;
};


