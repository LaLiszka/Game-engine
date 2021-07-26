/*
 * Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of this distribution.
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzFramework/StringFunc/StringFunc.h>
#include <AzFramework/IO/LocalFileIO.h>
#include <AzFramework/Network/AssetProcessorConnection.h>

#include <AzToolsFramework/AzToolsFrameworkModule.h>
#include <AzToolsFramework/API/EditorPythonConsoleBus.h>
#include <AzToolsFramework/API/EditorPythonRunnerRequestsBus.h>
#include <AzToolsFramework/UI/UICore/QWidgetSavedState.h>
#include <AzToolsFramework/UI/UICore/QTreeViewStateSaver.hxx>
#include <AzToolsFramework/AssetBrowser/AssetBrowserEntry.h>
#include <AzToolsFramework/SourceControl/PerforceComponent.h>
#include <AzToolsFramework/Asset/AssetSystemComponent.h>
#include <AzToolsFramework/AssetBrowser/AssetBrowserComponent.h>
#include <AzToolsFramework/Thumbnails/ThumbnailerComponent.h>
#include <AzToolsFramework/UI/PropertyEditor/PropertyManagerComponent.h>
#include <AzToolsFramework/SourceControl/SourceControlAPI.h>

#include <AtomToolsFramework/Util/Util.h>

#include <Atom/RPI.Edit/Common/AssetUtils.h>
#include <Atom/RPI.Public/RPISystemInterface.h>

#include <Source/ShaderManagementConsoleApplication.h>
#include <ShaderManagementConsole_Traits_Platform.h>

#include <Atom/Document/ShaderManagementConsoleDocumentModule.h>
#include <Atom/Document/ShaderManagementConsoleDocumentSystemRequestBus.h>

#include <Atom/Window/ShaderManagementConsoleWindowModule.h>
#include <Atom/Window/ShaderManagementConsoleWindowRequestBus.h>
#include <AzCore/IO/Path/Path.h>
#include <AzCore/Settings/SettingsRegistryMergeUtils.h>
#include <AzCore/Utils/Utils.h>

AZ_PUSH_DISABLE_WARNING(4251 4800, "-Wunknown-warning-option") // disable warnings spawned by QT
#include <QFileInfo>
#include <QObject>
#include <QMessageBox>
AZ_POP_DISABLE_WARNING

namespace ShaderManagementConsole
{
    AZStd::string_view GetBuildTargetName()
    {
#if !defined (LY_CMAKE_TARGET)
#error "LY_CMAKE_TARGET must be defined in order to add this source file to a CMake executable target"
#endif
        return AZStd::string_view{ LY_CMAKE_TARGET };
    }

    const char* ShaderManagementConsoleApplication::GetCurrentConfigurationName() const
    {
#if defined(_RELEASE)
        return "ReleaseShaderManagementConsole";
#elif defined(_DEBUG)
        return "DebugShaderManagementConsole";
#else
        return "ProfileShaderManagementConsole";
#endif
    }

    ShaderManagementConsoleApplication::ShaderManagementConsoleApplication(int* argc, char*** argv)
        : AtomToolsApplication(argc, argv)
    {
        QApplication::setApplicationName("O3DE Shader Management Console");
        setTargetName("ShaderManagementConsole");

        // The settings registry has been created at this point, so add the CMake target
        AZ::SettingsRegistryMergeUtils::MergeSettingsToRegistry_AddBuildSystemTargetSpecialization(
            *AZ::SettingsRegistry::Get(), GetBuildTargetName());
    }

    void ShaderManagementConsoleApplication::CreateStaticModules(AZStd::vector<AZ::Module*>& outModules)
    {
        Base::CreateStaticModules(outModules);
        outModules.push_back(aznew ShaderManagementConsoleDocumentModule);
        outModules.push_back(aznew ShaderManagementConsoleWindowModule);
    }

    void ShaderManagementConsoleApplication::OnShaderManagementConsoleWindowClosing()
    {
        ExitMainLoop();
        ShaderManagementConsoleWindowNotificationBus::Handler::BusDisconnect();
        AzToolsFramework::EditorPythonConsoleNotificationBus::Handler::BusDisconnect();
    }

    void ShaderManagementConsoleApplication::Destroy()
    {
        // before modules are unloaded, destroy UI to free up any assets it cached
        ShaderManagementConsole::ShaderManagementConsoleWindowRequestBus::Broadcast(&ShaderManagementConsole::ShaderManagementConsoleWindowRequestBus::Handler::DestroyShaderManagementConsoleWindow);

        ShaderManagementConsoleWindowNotificationBus::Handler::BusDisconnect();

        Base::Destroy();
    }

    void ShaderManagementConsoleApplication::AssetSystemAvailable()
    {
        // Try connect to AP first before try to launch it manually.
        bool connected = false;
        auto ConnectToAssetProcessorWithIdentifier = [&connected](AzFramework::AssetSystem::AssetSystemRequests* assetSystemRequests)
        {
            // When the AssetProcessor is already launched it should take less than a second to perform a connection
            // but when the AssetProcessor needs to be launch it could take up to 15 seconds to have the AssetProcessor initialize
            // and able to negotiate a connection when running a debug build
            // and to negotiate a connection

            AzFramework::AssetSystem::ConnectionSettings connectionSettings;
            AzFramework::AssetSystem::ReadConnectionSettingsFromSettingsRegistry(connectionSettings);
            connectionSettings.m_connectionDirection = AzFramework::AssetSystem::ConnectionSettings::ConnectionDirection::ConnectToAssetProcessor;
            connectionSettings.m_connectionIdentifier = "Shader Management Console";
            connectionSettings.m_loggingCallback = []([[maybe_unused]] AZStd::string_view logData)
            {
                AZ_TracePrintf("Shader Management Console", "%.*s", aznumeric_cast<int>(logData.size()), logData.data());
            };

            connected = assetSystemRequests->EstablishAssetProcessorConnection(connectionSettings);
        };
        AzFramework::AssetSystemRequestBus::Broadcast(ConnectToAssetProcessorWithIdentifier);

        // List of common asset filters for things that need to be compiled to run the material editor
        // Some of these things will not be necessary once we have proper support for queued asset loading and reloading
        const AZStd::vector<AZStd::string> assetFiltersArray = { "passes/", "config/"};

        if (connected)
        {
            CompileCriticalAssets(assetFiltersArray);
        }

        AzFramework::AssetSystemStatusBus::Handler::BusDisconnect();
    }

//    bool ShaderManagementConsoleApplication::OnPrintf(const char* window, const char* /*message*/)
//    {
//        // Suppress spam from the Source Control system
//        if (0 == strncmp(window, AzToolsFramework::SCC_WINDOW, AZ_ARRAY_SIZE(AzToolsFramework::SCC_WINDOW)))
//        {
//            return true;
//        }
//
//        return false;
//    }

    void ShaderManagementConsoleApplication::ProcessCommandLine()
    {
        // Process command line options for running one or more python scripts on startup
        const AZStd::string runPythonScriptSwitchName = "runpython";
        size_t runPythonScriptCount = m_commandLine.GetNumSwitchValues(runPythonScriptSwitchName);
        for (size_t runPythonScriptIndex = 0; runPythonScriptIndex < runPythonScriptCount; ++runPythonScriptIndex)
        {
            const AZStd::string runPythonScriptPath = m_commandLine.GetSwitchValue(runPythonScriptSwitchName, runPythonScriptIndex);
            AZStd::vector<AZStd::string_view> runPythonArgs;
            AzToolsFramework::EditorPythonRunnerRequestBus::Broadcast(
                &AzToolsFramework::EditorPythonRunnerRequestBus::Events::ExecuteByFilenameWithArgs,
                runPythonScriptPath,
                runPythonArgs);
        }

        // Process command line options for opening one or more documents on startup
        size_t openDocumentCount = m_commandLine.GetNumMiscValues();
        for (size_t openDocumentIndex = 0; openDocumentIndex < openDocumentCount; ++openDocumentIndex)
        {
            const AZStd::string openDocumentPath = m_commandLine.GetMiscValue(openDocumentIndex);
            ShaderManagementConsoleDocumentSystemRequestBus::Broadcast(&ShaderManagementConsoleDocumentSystemRequestBus::Events::OpenDocument, openDocumentPath);
        }
    }

    void ShaderManagementConsoleApplication::StartInternal()
    {
        if (WasExitMainLoopRequested())
        {
            return;
        }

        m_traceLogger.WriteStartupLog("ShaderManagementConsole.log");

        //[GFX TODO][ATOM-415] Try to factor out some of this stuff with AtomSampleViewerApplication
        AzToolsFramework::AssetDatabase::AssetDatabaseRequestsBus::Handler::BusConnect();
        AzToolsFramework::AssetBrowser::AssetDatabaseLocationNotificationBus::Broadcast(&AzToolsFramework::AssetBrowser::AssetDatabaseLocationNotifications::OnDatabaseInitialized);

        AZ::Data::AssetCatalogRequestBus::Broadcast(&AZ::Data::AssetCatalogRequestBus::Events::LoadCatalog, "@assets@/assetcatalog.xml");

        AZ::RPI::RPISystemInterface::Get()->InitializeSystemAssets();

        LoadSettings();

        LaunchDiscoveryService();

        ShaderManagementConsoleWindowNotificationBus::Handler::BusConnect();

        ShaderManagementConsole::ShaderManagementConsoleWindowRequestBus::Broadcast(&ShaderManagementConsole::ShaderManagementConsoleWindowRequestBus::Handler::CreateShaderManagementConsoleWindow);

        auto editorPythonEventsInterface = AZ::Interface<AzToolsFramework::EditorPythonEventsInterface>::Get();
        if (editorPythonEventsInterface)
        {
            // The PythonSystemComponent does not call StartPython to allow for lazy python initialization, so start it here
            // The PythonSystemComponent will call StopPython when it deactivates, so we do not need our own corresponding call to StopPython
            editorPythonEventsInterface->StartPython();
        }

        ProcessCommandLine();
    }

    bool ShaderManagementConsoleApplication::GetAssetDatabaseLocation(AZStd::string& result)
    {
        AZ::SettingsRegistryInterface* settingsRegistry = AZ::SettingsRegistry::Get();
        AZ::IO::FixedMaxPath assetDatabaseSqlitePath;
        if (settingsRegistry && settingsRegistry->Get(assetDatabaseSqlitePath.Native(), AZ::SettingsRegistryMergeUtils::FilePathKey_CacheProjectRootFolder))
        {
            assetDatabaseSqlitePath /= "assetdb.sqlite";
            result = AZStd::string_view(assetDatabaseSqlitePath.Native());
            return true;
        }

        return false;
    }
} // namespace ShaderManagementConsole
