/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Serialization/SerializeContext.h> // Needs to be on top due to missing include in AssetSerializer.h
#include <AzCore/Asset/AssetSerializer.h>
#include <AzCore/Casting/numeric_cast.h>
#include <AzCore/Debug/Trace.h>
#include <AzCore/IO/FileIO.h>
#include <AzCore/IO/SystemFile.h>
#include <AzCore/Module/Module.h>
#include <AzCore/Module/ModuleManagerBus.h>
#include <AzCore/Serialization/Json/JsonSerialization.h>
#include <AzCore/Serialization/Json/RegistrationContext.h>
#include <AzCore/Settings/CommandLine.h>
#include <AzCore/Settings/SettingsRegistryMergeUtils.h>
#include <AzCore/std/containers/queue.h>
#include <AzCore/std/functional.h>
#include <AzCore/std/string/wildcard.h>
#include <AzCore/StringFunc/StringFunc.h>
#include <Application.h>
#include <Utilities.h>

namespace AZ::SerializeContextTools
{
    AZStd::string Utilities::ReadOutputTargetFromCommandLine(Application& application, const char* defaultFileOrFolder)
    {
        AZ::IO::Path sourceGameFolder;
        if (auto settingsRegistry = AZ::SettingsRegistry::Get(); settingsRegistry != nullptr)
        {
            settingsRegistry->Get(sourceGameFolder.Native(), AZ::SettingsRegistryMergeUtils::FilePathKey_ProjectPath);
        }

        AZ::IO::Path outputPath;
        if (application.GetAzCommandLine()->HasSwitch("output"))
        {
            outputPath.Native() = application.GetAzCommandLine()->GetSwitchValue("output", 0);
            if (outputPath.IsRelative())
            {
                outputPath = sourceGameFolder / outputPath;
            }
        }
        else
        {
            outputPath = sourceGameFolder / defaultFileOrFolder;
        }
        return outputPath.Native();
    }

    AZStd::vector<AZStd::string> Utilities::ReadFileListFromCommandLine(Application& application, AZStd::string_view switchName)
    {
        AZStd::vector<AZStd::string> result;

        const AZ::CommandLine* commandLine = application.GetAzCommandLine();
        if (!commandLine)
        {
            AZ_Error("SerializeContextTools", false, "Command line not available.");
            return result;
        }

        if (!commandLine->HasSwitch(switchName))
        {
            AZ_Error("SerializeContextTools", false, "Missing command line argument '-%*s' which should contain the requested files.",
                aznumeric_cast<int>(switchName.size()), switchName.data());
            return result;
        }

        AZ::IO::Path sourceGameFolder;
        if (auto settingsRegistry = AZ::SettingsRegistry::Get(); settingsRegistry != nullptr)
        {
            settingsRegistry->Get(sourceGameFolder.Native(), AZ::SettingsRegistryMergeUtils::FilePathKey_ProjectPath);
        }

        AZStd::vector<AZStd::string_view> fileList;
        auto AppendFileList = [&fileList](AZStd::string_view filename)
        {
            fileList.emplace_back(filename);
        };
        for (size_t switchIndex{}; switchIndex < commandLine->GetNumSwitchValues(switchName); ++switchIndex)
        {
            AZ::StringFunc::TokenizeVisitor(commandLine->GetSwitchValue(switchName, switchIndex), AppendFileList, ";");
        }
        return Utilities::ExpandFileList(sourceGameFolder.c_str(), fileList);
    }

    AZStd::vector<AZStd::string> Utilities::ExpandFileList(const char* root, const AZStd::vector<AZStd::string_view>& fileList)
    {
        AZStd::vector<AZStd::string> result;
        result.reserve(fileList.size());

        for (const AZStd::string_view& file : fileList)
        {
            if (HasWildCard(file))
            {
                AZ::IO::FixedMaxPath filterPath{ file };

                AZ::IO::FixedMaxPath parentPath{ filterPath.ParentPath() };
                if (filterPath.IsRelative())
                {
                    parentPath = AZ::IO::FixedMaxPath(root) / parentPath;
                }

                AZ::IO::PathView filterFilename = filterPath.Filename();
                if (filterFilename.empty())
                {
                    AZ_Error("SerializeContextTools", false, "Unable to get folder path for '%.*s'.",
                        aznumeric_cast<int>(filterFilename.Native().size()), filterFilename.Native().data());
                    continue;
                }

                AZStd::queue<AZ::IO::FixedMaxPath> pendingFolders;
                pendingFolders.push(AZStd::move(parentPath));
                while (!pendingFolders.empty())
                {
                    const AZ::IO::FixedMaxPath& filterFolder = pendingFolders.front();

                    auto callback = [&pendingFolders, &filterFolder, &filterFilename, &result](AZ::IO::PathView item, bool isFile) -> bool
                    {
                        if (item == "." || item == "..")
                        {
                            return true;
                        }

                        AZ::IO::FixedMaxPath fullPath = filterFolder / item;
                        if (isFile)
                        {
                            if (AZStd::wildcard_match(filterFilename.Native(), item.Native()))
                            {
                                result.emplace_back(fullPath.c_str(), fullPath.Native().size());
                            }
                        }
                        else
                        {
                            pendingFolders.push(AZStd::move(fullPath));
                        }
                        return true;
                    };
                    AZ::IO::SystemFile::FindFiles((filterFolder / "*").c_str(), callback);
                    pendingFolders.pop();
                }
            }
            else
            {
                AZ::IO::FixedMaxPath filePath{ file };
                if (filePath.IsRelative())
                {
                    filePath = AZ::IO::FixedMaxPath(root) / filePath;
                }
                result.emplace_back(filePath.c_str(), filePath.Native().size());
            }
        }

        return result;
    }

    bool Utilities::HasWildCard(AZStd::string_view string)
    {
        // Wild cards vary between platforms, but these are the most common ones.
        return string.find_first_of("*?[]!@#", 0) != AZStd::string_view::npos;
    }

    void Utilities::SanitizeFilePath(AZStd::string& filePath)
    {
        auto invalidCharacters = [](char letter)
        {
            return
                letter == ':' || letter == '"' || letter == '\'' ||
                letter == '{' || letter == '}' ||
                letter == '<' || letter == '>';
        };
        AZStd::replace_if(filePath.begin(), filePath.end(), invalidCharacters, '_');
    }

    bool Utilities::IsSerializationPrimitive(const AZ::Uuid& classId)
    {
        JsonRegistrationContext* registrationContext;
        AZ::ComponentApplicationBus::BroadcastResult(registrationContext, &AZ::ComponentApplicationBus::Events::GetJsonRegistrationContext);
        if (!registrationContext)
        {
            AZ_Error("SerializeContextTools", false, "Failed to retrieve json registration context.");
            return false;
        }
        return registrationContext->GetSerializerForType(classId) != nullptr;
    }

    AZStd::vector<AZ::Uuid> Utilities::GetSystemComponents(const Application& application)
    {
        AZStd::vector<AZ::Uuid> result = application.GetRequiredSystemComponents();
        auto getModuleSystemComponentsCB = [&result](const ModuleData& moduleData) -> bool
        {
            if (AZ::Module* module = moduleData.GetModule())
            {
                AZ::ComponentTypeList moduleRequiredComponents = module->GetRequiredSystemComponents();
                result.reserve(result.size() + moduleRequiredComponents.size());
                result.insert(result.end(), moduleRequiredComponents.begin(), moduleRequiredComponents.end());
            }
            return true;
        };
        ModuleManagerRequestBus::Broadcast(&ModuleManagerRequests::EnumerateModules, getModuleSystemComponentsCB);

        return result;
    }

    bool Utilities::InspectSerializedFile(
        const char* filePath,
        SerializeContext* sc,
        const ObjectStream::ClassReadyCB& classCallback,
        Data::AssetFilterCB assetFilterCallback)
    {
        if (!AZ::IO::FileIOBase::GetInstance()->Exists(filePath))
        {
            AZ_Error("Verify", false, "Unable to open file '%s' as it doesn't exist.", filePath);
            return false;
        }

        AZ::IO::HandleType fileHandle;
        auto openResult = AZ::IO::FileIOBase::GetInstance()->Open(filePath, AZ::IO::OpenMode::ModeRead, fileHandle);
        if (!openResult)
        {
            AZ_Error("Verify", false, "File '%s' could not be opened.", filePath);
            return false;
        }

        u64 fileLength = 0;
        auto sizeResult = AZ::IO::FileIOBase::GetInstance()->Size(fileHandle, fileLength);
        if (!sizeResult || (fileLength == 0))
        {
            AZ_Error("Verify", false, "File '%s' doesn't have content.", filePath);
            return false;
        }

        AZStd::vector<u8> data;
        data.resize_no_construct(fileLength);
        u64 bytesRead = 0;
        auto readResult = AZ::IO::FileIOBase::GetInstance()->Read(fileHandle, data.data(), fileLength, true, &bytesRead);
        if (!readResult || (bytesRead != fileLength))
        {
            AZ_Error("Verify", false, "Unable to read file '%s'.", filePath);
            return false;
        }

        AZ::IO::FileIOBase::GetInstance()->Close(fileHandle);

        AZ::IO::MemoryStream stream(data.data(), fileLength);

        ObjectStream::FilterDescriptor filter;
        // By default, never load dependencies. That's another file that would need to be processed
        // separately from this one.
        filter.m_assetCB = assetFilterCallback;
        if (!ObjectStream::LoadBlocking(&stream, *sc, classCallback, filter))
        {
            AZ_Printf("Verify", "Failed to deserialize '%s'\n", filePath);
            return false;
        }
        return true;
    }
} // namespace AZ::SerializeContextTools
