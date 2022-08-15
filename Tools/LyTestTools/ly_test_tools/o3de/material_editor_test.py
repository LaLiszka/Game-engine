"""
Copyright (c) Contributors to the Open 3D Engine Project.
For complete copyright and license terms please see the LICENSE at the root of this distribution.

SPDX-License-Identifier: Apache-2.0 OR MIT

Test-writing utilities that simplify creating O3DE MaterialEditor tests in Python.

Test writers should subclass a test suite from MaterialEditorSuite to hold the specification of python test scripts
for the MaterialEditor to load and run.
Tests can be parallelized (run in multiple MaterialEditor instances at once) and/or
batched (multiple tests run in the same MaterialEditor instance), with collated results and crash detection.
Tests retain the ability to be run as a single test in a single MaterialEditor instance as well.

Usage example:
   class MyTestSuite(MaterialEditorSuite):

       class MyFirstTest(MaterialEditorSingleTest):
           from . import script_to_be_run_by_material_editor as test_module

       class MyTestInParallel_1(MaterialEditorBatchedTest):
           from . import another_script_to_be_run_by_material_editor as test_module

       class MyTestInParallel_2(MaterialEditorParallelTest):
           from . import yet_another_script_to_be_run_by_material_editor as test_module
"""

from __future__ import annotations
__test__ = False  # Avoid pytest collection & warnings since this module is for test functions, but not a test itself.

import logging

import pytest
import _pytest.python
import _pytest.outcomes

from ly_test_tools._internal.managers.workspace import AbstractWorkspaceManager
from ly_test_tools.launchers import launcher_helper
from ly_test_tools.o3de.multi_test_framework import AbstractTestBase, AbstractTestSuite

logger = logging.getLogger(__name__)


class MaterialEditorSingleTest(AbstractTestBase):
    """
    Test that will run alone in one MaterialEditor with no parallel MaterialEditors,
    limiting environmental side-effects at the expense of redundant isolated work
    """

    def __init__(self):
        # Extra cmdline arguments to supply to the MaterialEditor for the test
        self.extra_cmdline_args = []
        # Whether to use null renderer, this will override use_null_renderer for the Suite if not None
        self.use_null_renderer = None

    @staticmethod
    def setup(instance: MaterialEditorTestSuite.AbstractTestClass,
              request: _pytest.fixtures.FixtureRequest,
              workspace: AbstractWorkspaceManager,
              material_editor_test_results: AbstractTestSuite.TestData,
              launcher_platform: str) -> None:
        """
        User-overrideable setup function, which will run before the test.
        :param instance: Parent MaterialEditorTestSuite.AbstractTestClass instance executing the test
        :param request: PyTest request object
        :param workspace: LyTestTools workspace manager
        :param material_editor_test_results: Currently recorded MaterialEditor test results
        :param launcher_platform: user-parameterized string for LyTestTools
        """
        pass

    @staticmethod
    def wrap_run(instance: MaterialEditorTestSuite.AbstractTestClass,
                 request: _pytest.fixtures.FixtureRequest,
                 workspace: AbstractWorkspaceManager,
                 material_editor_test_results: AbstractTestSuite.TestData,
                 launcher_platform: str) -> None:
        """
        User-overrideable wrapper function, which will run both before and after test.
        Any code before the 'yield' statement will run before the test. With code after yield run after the test.
        Setup will run before wrap_run starts. Teardown will run after it completes.
        :param instance: Parent MaterialEditorTestSuite.AbstractTestClass instance executing the test
        :param request: PyTest request object
        :param workspace: LyTestTools workspace manager
        :param material_editor_test_results: Currently recorded MaterialEditor test results
        :param launcher_platform: user-parameterized string for LyTestTools
        """
        yield

    @staticmethod
    def teardown(instance: MaterialEditorTestSuite.AbstractTestClass,
                 request: _pytest.fixtures.FixtureRequest,
                 workspace: AbstractWorkspaceManager,
                 material_editor_test_results: AbstractTestSuite.TestData,
                 launcher_platform: str) -> None:
        """
        User-overrideable teardown function, which will run after the test
        :param instance: Parent MaterialEditorTestSuite.AbstractTestClass instance executing the test
        :param request: PyTest request object
        :param workspace: LyTestTools workspace manager
        :param material_editor_test_results: Currently recorded MaterialEditor test results
        :param launcher_platform: user-parameterized string for LyTestTools
        """
        pass


class MaterialEditorSharedTest(AbstractTestBase):
    """
    Test that will run in parallel with tests in different MaterialEditor instances, as well as serially batching
    with other tests in each MaterialEditor instance. Minimizes total test run duration.

    Does not support per test setup/teardown to avoid creating race conditions
    """
    # Specifies if the test can be batched in the same MaterialEditor
    is_batchable = True
    # Specifies if the test can be run in multiple MaterialEditors in parallel
    is_parallelizable = True


class MaterialEditorParallelTest(MaterialEditorSharedTest):
    """
    Test that will run in parallel with tests in different MaterialEditor instances,
    though not serially batched with other tests in each MaterialEditor instance.
    Reduces total test run duration, while limiting side-effects between tests.

    Does not support per test setup/teardown to avoid creating race conditions
    """
    is_batchable = False
    is_parallelizable = True


class MaterialEditorBatchedTest(MaterialEditorSharedTest):
    """
    Test that will run serially batched with the tests in the same MaterialEditor instance,
    though not executed in parallel with other MaterialEditor instances.
    Reduces overhead from starting the MaterialEditor, while limiting side-effects between MaterialEditors.

    Does not support per test setup/teardown to avoid creating race conditions
    """
    is_batchable = True
    is_parallelizable = False


class MaterialEditorTestSuite(AbstractTestSuite):
    """
    This class defines the values needed in order to execute a batched, parallel, or single MaterialEditor test.
    Any new test cases written that inherit from this class can override these values for their newly created class.
    """
    # Extra cmdline arguments to supply for every MaterialEditor for this test suite.
    global_extra_cmdline_args = ["-BatchMode", "-autotest_mode"]
    # Tests usually run with no renderer, however some tests require a renderer and will disable this.
    use_null_renderer = True
    # Maximum time in seconds for a single MaterialEditor to stay open across the set of shared tests.
    timeout_shared_test = 300
    # Maximum time (seconds) for waiting for a crash file to finish being dumped to disk.
    _timeout_crash_log = 20
    # Return code for test failure.
    _test_fail_retcode = 0xF
    # Test class to use for single test collection.
    _single_test_class = MaterialEditorSingleTest
    # Test class to use for shared test collection.
    _shared_test_class = MaterialEditorSharedTest
    # Log attribute value used in python to find the MaterialEditor's log file location.
    _log_attribute = "material_editor_log"
    # Name of the executable's log file.
    _log_name = "material_editor_test.log"
    # Executable function to call when launching MaterialEditor.
    _executable_function = launcher_helper.create_material_editor

    @pytest.mark.parametrize("crash_log_watchdog", [("raise_on_crash", False)])
    def pytest_multitest_makeitem(
            collector: _pytest.python.Module, name: str, obj: object) -> MaterialEditorTestSuite.AbstractTestClass:
        """
        Enables ly_test_tools._internal.pytest_plugin.multi_testing.pytest_pycollect_makeitem to collect the tests
        defined by this suite.
        This is required for any test suite that inherits from the AbstractTestSuite class else the tests won't be
        collected for that suite when using the ly_test_tools.o3de.multi_test_framework module.
        :param collector: Module that serves as the pytest test class collector
        :param name: Name of the parent test class
        :param obj: Module of the test to be run
        :return: MaterialEditorTestSuite.AbstractTestClass
        """
        return MaterialEditorTestSuite.AbstractTestClass(name, collector)
