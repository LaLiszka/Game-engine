/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/std/string/string.h>
#include <AssetBuilderSDK/AssetBuilderBusses.h>
#include <AssetBuilderSDK/AssetBuilderSDK.h>
#include <AzToolsFramework/Application/ToolsApplication.h>
#include "AssetBuilderInfo.h"
#include <QCoreApplication>

struct IBuilderApplication
{
    AZ_RTTI(IBuilderApplication, "{FEDD188E-D5FF-4852-B945-F82F7CC1CA5F}");

    IBuilderApplication() = default;
    virtual ~IBuilderApplication() = default;

    virtual void InitializeBuilderComponents() = 0;

    AZ_DISABLE_COPY_MOVE(IBuilderApplication);
};

class AssetBuilderApplication
    : public AzToolsFramework::ToolsApplication
    , public IBuilderApplication
{
public:
    AssetBuilderApplication(int* argc, char*** argv);
    ~AssetBuilderApplication();

    AZ::ComponentTypeList GetRequiredSystemComponents() const override;
    void RegisterCoreComponents() override;
    void StartCommon(AZ::Entity* systemEntity) override;

    bool IsInDebugMode() const;

    void InitializeBuilderComponents() override;

private:
    void InstallCtrlHandler();

    QCoreApplication m_qtApplication;
};
