/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <TestImpactFramework/TestImpactUtils.h>
#include <TestImpactFramework/Python/TestImpactPythonRuntime.h>

#include <TestImpactRuntimeUtils.h>
#include <Artifact/Static/TestImpactPythonTestTargetMeta.h>
#include <Artifact/Factory/TestImpactPythonTestTargetMetaMapFactory.h>
#include <Dependency/TestImpactSourceCoveringTestsSerializer.h>
#include <Dependency/TestImpactTestSelectorAndPrioritizer.h>
#include <Target/Python/TestImpactPythonProductionTarget.h>
#include <Target/Python/TestImpactPythonTargetListCompiler.h>
#include <Target/Python/TestImpactPythonTestTarget.h>
#include <TestEngine/Python/TestImpactPythonTestEngine.h>

#include <AzCore/std/string/regex.h>

namespace TestImpact
{
    PythonTestTargetMetaMap ReadPythonTestTargetMetaMapFile(SuiteType suiteFilter, const RepoPath& testTargetMetaConfigFile, const AZStd::string& buildType)
    {
        const auto masterTestListData = ReadFileContents<RuntimeException>(testTargetMetaConfigFile);
        auto testTargetMetaMap = PythonTestTargetMetaMapFactory(masterTestListData, suiteFilter);
        for (auto& [name, meta] : testTargetMetaMap)
        {
            meta.m_scriptMeta.m_testCommand = AZStd::regex_replace(meta.m_scriptMeta.m_testCommand, AZStd::regex("\\$\\<CONFIG\\>"), buildType); 
        }

        return testTargetMetaMap;
    }

    PythonRuntime::PythonRuntime(
        PythonRuntimeConfig&& config,
        [[maybe_unused]] const AZStd::optional<RepoPath>& dataFile,
        [[maybe_unused]] const AZStd::optional<RepoPath>& previousRunDataFile,
        [[maybe_unused]] const AZStd::vector<ExcludedTarget>& testsToExclude,
        [[maybe_unused]] SuiteType suiteFilter,
        [[maybe_unused]] Policy::ExecutionFailure executionFailurePolicy,
        [[maybe_unused]] Policy::FailedTestCoverage failedTestCoveragePolicy,
        [[maybe_unused]] Policy::TestFailure testFailurePolicy,
        [[maybe_unused]] Policy::IntegrityFailure integrationFailurePolicy,
        [[maybe_unused]] Policy::TargetOutputCapture targetOutputCapture)
        : m_config(AZStd::move(config))
        , m_suiteFilter(suiteFilter)
        , m_executionFailurePolicy(executionFailurePolicy)
        , m_failedTestCoveragePolicy(failedTestCoveragePolicy)
        , m_testFailurePolicy(testFailurePolicy)
        , m_integrationFailurePolicy(integrationFailurePolicy)
        , m_targetOutputCapture(targetOutputCapture)
    {
        // Construct the build targets from the build target descriptors
        auto targetDescriptors = ReadTargetDescriptorFiles(m_config.m_commonConfig.m_buildTargetDescriptor);
        auto buildTargets = CompilePythonTargetLists(
            AZStd::move(targetDescriptors),
            ReadPythonTestTargetMetaMapFile(suiteFilter, m_config.m_commonConfig.m_testTargetMeta.m_metaFile, m_config.m_commonConfig.m_meta.m_buildConfig));
        auto&& [productionTargets, testTargets] = buildTargets;
        m_buildTargets = AZStd::make_unique<BuildTargetList<ProductionTarget, TestTarget>>(
            AZStd::move(testTargets), AZStd::move(productionTargets));

        // Construct the dynamic dependency map from the build targets
        m_dynamicDependencyMap = AZStd::make_unique<DynamicDependencyMap<ProductionTarget, TestTarget>>(m_buildTargets.get());

        // Construct the test selector and prioritizer from the dependency graph data (NOTE: currently not implemented)
        m_testSelectorAndPrioritizer = AZStd::make_unique<TestSelectorAndPrioritizer<ProductionTarget, TestTarget>>(
            m_dynamicDependencyMap.get(), BuildTargetDependencyGraph{});

        // Construct the target exclude list from the exclude file if provided, otherwise use target configuration data
        if (!testsToExclude.empty())
        {
            // Construct using data from excludeTestFile
            m_testTargetExcludeList =
                ConstructTestTargetExcludeList(m_dynamicDependencyMap->GetBuildTargets()->GetTestTargetList(), testsToExclude);
        }
        else
        {
            // Construct using data from config file.
            m_testTargetExcludeList = ConstructTestTargetExcludeList(
                m_dynamicDependencyMap->GetBuildTargets()->GetTestTargetList(), m_config.m_target.m_excludedTargets);
        }

        // Construct the test engine with the workspace path and launcher binaries
        m_testEngine = AZStd::make_unique<PythonTestEngine>(
            m_config.m_commonConfig.m_repo.m_root,
            m_config.m_commonConfig.m_repo.m_build,
            m_config.m_workspace.m_temp,
            true);

        try
        {
            if (dataFile.has_value())
            {
                m_sparTiaFile = dataFile.value().String();
            }
            else
            {
                m_sparTiaFile = m_config.m_workspace.m_active.m_root / RepoPath(SuiteTypeAsString(m_suiteFilter)) /
                    m_config.m_workspace.m_active.m_sparTiaFile;
            }

            // Populate the dynamic dependency map with the existing source coverage data (if any)
            const auto tiaDataRaw = ReadFileContents<Exception>(m_sparTiaFile);
            const auto tiaData = DeserializeSourceCoveringTestsList(tiaDataRaw);
            if (tiaData.GetNumSources())
            {
                m_dynamicDependencyMap->ReplaceSourceCoverage(tiaData);
                m_hasImpactAnalysisData = true;

                // Enumerate new test targets
                // const auto testTargetsWithNoEnumeration = m_dynamicDependencyMap->GetNotCoveringTests();
                // if (!testTargetsWithNoEnumeration.empty())
                //{
                //    m_testEngine->UpdateEnumerationCache(
                //        testTargetsWithNoEnumeration,
                //        Policy::ExecutionFailure::Ignore,
                //        Policy::TestFailure::Continue,
                //        AZStd::nullopt,
                //        AZStd::nullopt,
                //        AZStd::nullopt);
                //}
            }
        }
        catch (const DependencyException& e)
        {
            if (integrationFailurePolicy == Policy::IntegrityFailure::Abort)
            {
                throw RuntimeException(e.what());
            }
        }
        catch ([[maybe_unused]] const Exception& e)
        {
            AZ_Printf(
                LogCallSite,
                AZStd::string::format(
                    "No test impact analysis data found for suite '%s' at %s\n",
                    SuiteTypeAsString(m_suiteFilter).c_str(),
                    m_sparTiaFile.c_str())
                    .c_str());
        }
    }

    PythonRuntime::~PythonRuntime() = default;

    void PythonRuntime::ClearDynamicDependencyMapAndRemoveExistingFile()
    {
        m_dynamicDependencyMap->ClearAllSourceCoverage();
        DeleteFile(m_sparTiaFile);
    }

    PolicyStateBase PythonRuntime::GeneratePolicyStateBase() const
    {
        PolicyStateBase policyState;

        policyState.m_executionFailurePolicy = m_executionFailurePolicy;
        policyState.m_failedTestCoveragePolicy = m_failedTestCoveragePolicy;
        policyState.m_integrityFailurePolicy = m_integrationFailurePolicy;
        policyState.m_targetOutputCapture = m_targetOutputCapture;
        policyState.m_testFailurePolicy = m_testFailurePolicy;
        policyState.m_testShardingPolicy = Policy::TestSharding::Never;

        return policyState;
    }

    SequencePolicyState PythonRuntime::GenerateSequencePolicyState() const
    {
        return { GeneratePolicyStateBase() };
    }

    Client::RegularSequenceReport PythonRuntime::RegularTestSequence(
        [[maybe_unused]] AZStd::optional<AZStd::chrono::milliseconds> testTargetTimeout,
        [[maybe_unused]] AZStd::optional<AZStd::chrono::milliseconds> globalTimeout,
        [[maybe_unused]] AZStd::optional<TestSequenceStartCallback> testSequenceStartCallback,
        [[maybe_unused]] AZStd::optional<TestSequenceCompleteCallback<Client::RegularSequenceReport>> testSequenceEndCallback,
        [[maybe_unused]] AZStd::optional<TestRunCompleteCallback> testCompleteCallback)
    {
        return Client::RegularSequenceReport(
            1,
            AZStd::nullopt,
            AZStd::nullopt,
            SequencePolicyState{},
            m_suiteFilter,
            Client::TestRunSelection(),
            Client::TestRunReport(
                TestSequenceResult::Success,
                AZStd::chrono::high_resolution_clock::time_point(),
                AZStd::chrono::milliseconds{ 0 },
                {},
                {},
                {},
                {},
                {}));
    }

    Client::ImpactAnalysisSequenceReport PythonRuntime::ImpactAnalysisTestSequence(
        [[maybe_unused]] const ChangeList& changeList,
        [[maybe_unused]] Policy::TestPrioritization testPrioritizationPolicy,
        [[maybe_unused]] Policy::DynamicDependencyMap dynamicDependencyMapPolicy,
        [[maybe_unused]] AZStd::optional<AZStd::chrono::milliseconds> testTargetTimeout,
        [[maybe_unused]] AZStd::optional<AZStd::chrono::milliseconds> globalTimeout,
        [[maybe_unused]] AZStd::optional<ImpactAnalysisTestSequenceStartCallback> testSequenceStartCallback,
        [[maybe_unused]] AZStd::optional<TestSequenceCompleteCallback<Client::ImpactAnalysisSequenceReport>> testSequenceEndCallback,
        [[maybe_unused]] AZStd::optional<TestRunCompleteCallback> testCompleteCallback)
    {
        return Client::ImpactAnalysisSequenceReport(
            1,
            AZStd::nullopt,
            AZStd::nullopt,
            ImpactAnalysisSequencePolicyState{},
            m_suiteFilter,
            Client::TestRunSelection(),
            {},
            {},
            Client::TestRunReport(
                TestSequenceResult::Success,
                AZStd::chrono::high_resolution_clock::time_point(),
                AZStd::chrono::milliseconds{ 0 },
                {},
                {},
                {},
                {},
                {}),
            Client::TestRunReport(
                TestSequenceResult::Success,
                AZStd::chrono::high_resolution_clock::time_point(),
                AZStd::chrono::milliseconds{ 0 },
                {},
                {},
                {},
                {},
                {}));
    }

    Client::SafeImpactAnalysisSequenceReport PythonRuntime::SafeImpactAnalysisTestSequence(
        [[maybe_unused]] const ChangeList& changeList,
        [[maybe_unused]] Policy::TestPrioritization testPrioritizationPolicy,
        [[maybe_unused]] AZStd::optional<AZStd::chrono::milliseconds> testTargetTimeout,
        [[maybe_unused]] AZStd::optional<AZStd::chrono::milliseconds> globalTimeout,
        [[maybe_unused]] AZStd::optional<SafeImpactAnalysisTestSequenceStartCallback> testSequenceStartCallback,
        [[maybe_unused]] AZStd::optional<TestSequenceCompleteCallback<Client::SafeImpactAnalysisSequenceReport>> testSequenceEndCallback,
        [[maybe_unused]] AZStd::optional<TestRunCompleteCallback> testCompleteCallback)
    {
        return Client::SafeImpactAnalysisSequenceReport(
            1,
            AZStd::nullopt,
            AZStd::nullopt,
            SafeImpactAnalysisSequencePolicyState{},
            m_suiteFilter,
            {},
            {},
            {},
            Client::TestRunReport(
                TestSequenceResult::Success,
                AZStd::chrono::high_resolution_clock::time_point(),
                AZStd::chrono::milliseconds{ 0 },
                {},
                {},
                {},
                {},
                {}),
            Client::TestRunReport(
                TestSequenceResult::Success,
                AZStd::chrono::high_resolution_clock::time_point(),
                AZStd::chrono::milliseconds{ 0 },
                {},
                {},
                {},
                {},
                {}),
            Client::TestRunReport(
                TestSequenceResult::Success,
                AZStd::chrono::high_resolution_clock::time_point(),
                AZStd::chrono::milliseconds{ 0 },
                {},
                {},
                {},
                {},
                {}));
    }

    Client::SeedSequenceReport PythonRuntime::SeededTestSequence(
        [[maybe_unused]] AZStd::optional<AZStd::chrono::milliseconds> testTargetTimeout,
        [[maybe_unused]] AZStd::optional<AZStd::chrono::milliseconds> globalTimeout,
        [[maybe_unused]] AZStd::optional<TestSequenceStartCallback> testSequenceStartCallback,
        [[maybe_unused]] AZStd::optional<TestSequenceCompleteCallback<Client::SeedSequenceReport>> testSequenceEndCallback,
        [[maybe_unused]] AZStd::optional<TestRunCompleteCallback> testCompleteCallback)
    {
        const Timer sequenceTimer;
        AZStd::vector<const TestTarget*> includedTestTargets;
        AZStd::vector<const TestTarget*> excludedTestTargets;
        
        // Separate the test targets into those that are excluded by either the test filter or exclusion list and those that are not
        for (const auto& testTarget : m_dynamicDependencyMap->GetBuildTargets()->GetTestTargetList().GetTargets())
        {
            if (m_testTargetExcludeList->IsTestTargetFullyExcluded(&testTarget))
            {
                excludedTestTargets.push_back(&testTarget);
            }
            else
            {
                includedTestTargets.push_back(&testTarget);
            }
        }
        
        // Extract the client facing representation of selected test targets
        Client::TestRunSelection selectedTests(ExtractTestTargetNames(includedTestTargets), ExtractTestTargetNames(excludedTestTargets));
        
        // Inform the client that the sequence is about to start
        if (testSequenceStartCallback.has_value())
        {
            (*testSequenceStartCallback)(m_suiteFilter, selectedTests);
        }
        
        // Run the test targets and collect the test run results
        const Timer testRunTimer;
        const auto [result, testJobs] = m_testEngine->InstrumentedRun(
            includedTestTargets,
            m_executionFailurePolicy,
            m_integrationFailurePolicy,
            m_testFailurePolicy,
            m_targetOutputCapture,
            testTargetTimeout,
            globalTimeout,
            TestRunCompleteCallbackHandler<TestTarget>(includedTestTargets.size(), testCompleteCallback));
        const auto testRunDuration = testRunTimer.GetElapsedMs();
        
        // Generate the sequence report for the client
        const auto sequenceReport = Client::SeedSequenceReport(
            1,
            testTargetTimeout,
            globalTimeout,
            GenerateSequencePolicyState(),
            m_suiteFilter,
            selectedTests,
            GenerateTestRunReport(result, testRunTimer.GetStartTimePointRelative(sequenceTimer), testRunDuration, testJobs));
        
        // Inform the client that the sequence has ended
        if (testSequenceEndCallback.has_value())
        {
            (*testSequenceEndCallback)(sequenceReport);
        }
        
        ClearDynamicDependencyMapAndRemoveExistingFile();
        
        m_hasImpactAnalysisData = UpdateAndSerializeDynamicDependencyMap(
                                      *m_dynamicDependencyMap.get(),
                                      testJobs,
                                      m_failedTestCoveragePolicy,
                                      m_integrationFailurePolicy,
                                      m_config.m_commonConfig.m_repo.m_root,
                                      m_sparTiaFile)
                                      .value_or(m_hasImpactAnalysisData);
        
        return sequenceReport;
    }

    bool PythonRuntime::HasImpactAnalysisData() const
    {
        return m_hasImpactAnalysisData;
    }
} // namespace TestImpact
