/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <TestImpactFramework/TestImpactUtils.h>
#include <TestImpactFramework/TestImpactRuntimeException.h>

#include <Artifact/Factory/TestImpactTargetDescriptorFactory.h>
#include <TestImpactRuntimeUtils.h>

#include <filesystem>

namespace TestImpact
{
    Timer::Timer()
        : m_startTime(AZStd::chrono::high_resolution_clock::now())
    {
    }

    //! Returns the time point that the timer was instantiated.
    AZStd::chrono::high_resolution_clock::time_point Timer::GetStartTimePoint() const
    {
        return m_startTime;
    }

    //! Returns the time point that the timer was instantiated relative to the specified starting time point.
    AZStd::chrono::high_resolution_clock::time_point Timer::GetStartTimePointRelative(const Timer& start) const
    {
        return AZStd::chrono::high_resolution_clock::time_point() +
            AZStd::chrono::duration_cast<AZStd::chrono::milliseconds>(m_startTime - start.GetStartTimePoint());
    }

    //! Returns the time elapsed (in milliseconds) since the timer was instantiated.
    AZStd::chrono::milliseconds Timer::GetElapsedMs() const
    {
        const auto endTime = AZStd::chrono::high_resolution_clock::now();
        return AZStd::chrono::duration_cast<AZStd::chrono::milliseconds>(endTime - m_startTime);
    }

    //! Returns the current time point relative to the time point the timer was instantiated.
    AZStd::chrono::high_resolution_clock::time_point Timer::GetElapsedTimepoint() const
    {
        const auto endTime = AZStd::chrono::high_resolution_clock::now();
        return m_startTime + AZStd::chrono::duration_cast<AZStd::chrono::milliseconds>(endTime - m_startTime);
    }

    AZStd::vector<TargetDescriptor> ReadTargetDescriptorFiles(const BuildTargetDescriptorConfig& buildTargetDescriptorConfig)
    {
        AZStd::vector<TargetDescriptor> descriptors;
        for (const auto& targetDescriptorFile :
             std::filesystem::directory_iterator(buildTargetDescriptorConfig.m_mappingDirectory.c_str()))
        {
            const auto targetDescriptorContents = ReadFileContents<RuntimeException>(targetDescriptorFile.path().string().c_str());
            auto targetDescriptor = TargetDescriptorFactory(
                targetDescriptorContents,
                buildTargetDescriptorConfig.m_staticInclusionFilters,
                buildTargetDescriptorConfig.m_inputInclusionFilters,
                buildTargetDescriptorConfig.m_inputOutputPairer);
            descriptors.emplace_back(AZStd::move(targetDescriptor));
        }

        return descriptors;
    }    
} // namespace TestImpact
