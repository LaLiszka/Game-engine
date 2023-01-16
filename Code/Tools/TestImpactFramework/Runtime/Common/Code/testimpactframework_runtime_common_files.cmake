#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    Include/Static/Artifact/TestImpactArtifactException.h
    Include/Static/Artifact/Factory/TestImpactTestEnumerationSuiteFactory.h
    Include/Static/Artifact/Factory/TestImpactTestRunSuiteFactory.h
    Include/Static/Artifact/Factory/TestImpactModuleCoverageFactory.h
    Include/Static/Artifact/Factory/TestImpactTestTargetMetaMapFactoryUtils.h
    Include/Static/Artifact/Static/TestImpactTestSuiteMeta.h
    Include/Static/Artifact/Static/TestImpactTestTargetMeta.h
    Include/Static/Artifact/Static/TestImpactTargetDescriptor.h
    Include/Static/Artifact/Dynamic/TestImpactTestEnumerationSuite.h
    Include/Static/Artifact/Dynamic/TestImpactTestRunSuite.h
    Include/Static/Artifact/Dynamic/TestImpactTestSuite.h
    Include/Static/Artifact/Dynamic/TestImpactCoverage.h
    Include/Static/BuildTarget/Common/TestImpactBuildTargetException.h
    Include/Static/BuildTarget/Common/TestImpactBuildTargetList.h
    Include/Static/BuildTarget/Common/TestImpactBuildTarget.h
    Include/Static/BuildTarget/Common/TestImpactBuildGraph.h
    Include/Static/Process/TestImpactProcess.h
    Include/Static/Process/TestImpactProcessException.h
    Include/Static/Process/TestImpactProcessInfo.h
    Include/Static/Process/TestImpactProcessLauncher.h
    Include/Static/Process/JobRunner/TestImpactProcessJob.h
    Include/Static/Process/JobRunner/TestImpactProcessJobInfo.h
    Include/Static/Process/JobRunner/TestImpactProcessJobMeta.h
    Include/Static/Process/JobRunner/TestImpactProcessJobRunner.h
    Include/Static/Process/Scheduler/TestImpactProcessScheduler.h
    Include/Static/Dependency/TestImpactChangeDependencyList.h
    Include/Static/Dependency/TestImpactDependencyException.h
    Include/Static/Dependency/TestImpactDynamicDependencyMap.h
    Include/Static/Dependency/TestImpactSourceCoveringTestsList.h
    Include/Static/Dependency/TestImpactSourceCoveringTestsSerializer.h
    Include/Static/Dependency/TestImpactSourceDependency.h
    Include/Static/Dependency/TestImpactTestSelectorAndPrioritizer.h
    Include/Static/Target/Common/TestImpactTarget.h
    Include/Static/Target/Common/TestImpactTargetList.h
    Include/Static/Target/Common/TestImpactTargetException.h
    Include/Static/Target/Common/TestImpactTestTarget.cpp
    Include/Static/Target/Common/TestImpactTestTarget.h
    Include/Static/TestRunner/Common/TestImpactTestRunnerException.h
    Include/Static/TestRunner/Common/TestImpactTestRunnerBase.h
    Include/Static/TestRunner/Common/TestImpactTestRunner.h
    Include/Static/TestRunner/Common/TestImpactTestRunnerWithCoverage.h
    Include/Static/TestRunner/Common/TestImpactTestEnumerator.h
    Include/Static/TestRunner/Common/TestImpactTestSuiteContainer.h
    Include/Static/TestRunner/Common/Job/TestImpactTestJobInfoGenerator.h
    Include/Static/TestRunner/Common/Job/TestImpactTestRunWithCoverageJobData.h
    Include/Static/TestRunner/Common/Job/TestImpactTestEnumerationJobData.h
    Include/Static/TestRunner/Common/Job/TestImpactTestRunJobData.h
    Include/Static/TestRunner/Common/Job/TestImpactTestJobInfoUtils.h
    Include/Static/TestRunner/Common/Job/TestImpactTestJobRunner.h
    Include/Static/TestRunner/Common/Enumeration/TestImpactTestEnumeration.h
    Include/Static/TestRunner/Common/Enumeration/TestImpactTestEnumerationSerializer.h
    Include/Static/TestRunner/Common/Run/TestImpactTestCoverage.h
    Include/Static/TestRunner/Common/Run/TestImpactTestRun.h
    Include/Static/TestRunner/Common/Run/TestImpactTestRunSerializer.h
    Include/Static/TestEngine/Common/TestImpactTestEngineException.h
    Include/Static/TestEngine/Common/TestImpactTestEngine.h
    Include/Static/TestEngine/Common/Job/TestImpactTestEngineJob.h
    Include/Static/TestEngine/Common/Enumeration/TestImpactTestEngineEnumeration.h
    Include/Static/TestEngine/Common/Run/TestImpactTestEngineRegularRun.h
    Include/Static/TestEngine/Common/Run/TestImpactTestEngineInstrumentedRun.h
    Include/Static/TestImpactRuntime.h
    Include/Static/TestImpactRuntimeUtils.cpp
    Include/Static/TestImpactRuntimeUtils.h
    Include/Static/TestImpactTestTargetExclusionList.h
    Source/Artifact/Factory/TestImpactTestEnumerationSuiteFactory.cpp
    Source/Artifact/Factory/TestImpactTestRunSuiteFactory.cpp
    Source/Artifact/Factory/TestImpactModuleCoverageFactory.cpp
    Source/Artifact/Factory/TestImpactTargetDescriptorFactory.cpp
    Source/Artifact/Factory/TestImpactTestTargetMetaMapFactoryUtils.cpp
    Source/Process/TestImpactProcess.cpp
    Source/Process/TestImpactProcessInfo.cpp
    Source/Process/JobRunner/TestImpactProcessJobMeta.cpp
    Source/Process/Scheduler/TestImpactProcessScheduler.cpp
    Source/Dependency/TestImpactSourceCoveringTestsList.cpp
    Source/Dependency/TestImpactSourceCoveringTestsSerializer.cpp
    Source/Target/Common/TestImpactTarget.cpp
    Source/TestRunner/Common/Job/TestImpactTestRunWithCoverageJobData.cpp
    Source/TestRunner/Common/Job/TestImpactTestEnumerationJobData.cpp
    Source/TestRunner/Common/Job/TestImpactTestJobInfoUtils.cpp
    Source/TestRunner/Common/Job/TestImpactTestRunJobData.cpp
    Source/TestRunner/Common/Enumeration/TestImpactTestEnumerationSerializer.cpp
    Source/TestRunner/Common/Run/TestImpactTestCoverage.cpp
    Source/TestRunner/Common/Run/TestImpactTestRun.cpp
    Source/TestRunner/Common/Run/TestImpactTestRunSerializer.cpp
    Source/TestImpactException.cpp
    Source/TestImpactClientTestSelection.cpp
    Source/TestImpactClientTestRun.cpp
    Source/TestImpactClientSequenceReport.cpp
    Source/TestImpactChangeListSerializer.cpp
    Source/TestImpactClientSequenceReportSerializer.cpp
    Source/TestImpactRepoPath.cpp
    Source/TestImpactUtils.cpp
)
