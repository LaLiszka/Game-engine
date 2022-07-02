"""
Copyright (c) Contributors to the Open 3D Engine Project.
For complete copyright and license terms please see the LICENSE at the root of this distribution.

SPDX-License-Identifier: Apache-2.0 OR MIT
"""
# Simplified O3DE test-writing utilities.
#
# Supports different options for running tests using this framework ("instance" refers to the executable under test).
#
# SingleTest: A single test that runs 1 test in 1 instance.
# SharedTest: Multiple tests that run multiple tests in multiple instances.
# BatchedTest: Multiple tests that run 1 instance with multiple tests in that 1 instance.
# ParallelTest: Multiple tests that run multiple instances with 1 test in each instance.

from __future__ import annotations
__test__ = False  # Avoid pytest collection & warnings since this module is for test functions, but not a test itself.

import abc
import functools
import json
import inspect
import math
import os
import re
import types
import warnings

import pytest
import _pytest.python
import _pytest.outcomes
from _pytest.skipping import pytest_runtest_setup as skipping_pytest_runtest_setup

import ly_test_tools.environment.process_utils as process_utils
import ly_test_tools.o3de.editor_test_utils as editor_utils
from ly_test_tools._internal.managers.workspace import AbstractWorkspaceManager
from ly_test_tools.o3de.asset_processor import AssetProcessor


class AbstractTestBase(abc.ABC):
    """
    Abstract base Test class
    """
    # Maximum time for run, in seconds.
    timeout = 180
    # Test file that this test will run.
    test_module = None
    # Attach debugger when running the test, useful for debugging crashes. This should never be True on production.
    # It's also recommended to switch to SingleTest for debugging in isolation.
    attach_debugger = False
    # Wait until a debugger is attached at the startup of the test, this is another way of debugging.
    wait_for_debugger = False


class SingleTest(AbstractTestBase):
    """
    Test that will be run alone in one instance, with no parallel or serially batched instances.
    This should only be used if SharedTest, ParallelTest, or BatchedTest cannot be utilized for the test steps.
    It may also be used for debugging test issues in isolation.
    """
    def __init__(self):
        # Extra cmdline arguments to supply to the instance for the test.
        self.extra_cmdline_args = []
        # Whether to use null renderer, this will override use_null_renderer for the BaseTestSuite if not None.
        self.use_null_renderer = None

    def setup(self, **args):
        """
        User-overrideable setup function, which will run before the test
        """
        pass

    def wrap_run(self, **args):
        """
        User-overrideable wrapper function, which will run before and after test.
        Any code before the 'yield' statement will run before the test. With code after yield run after the test.
        """
        yield

    def teardown(self, **args):
        """
        User-overrideable teardown function, which will run after the test
        """
        pass


class SharedTest(AbstractTestBase):
    """
    Runs both of the following test types:
    1. Tests that will be run in parallel with tests in multiple instances.
    2. Tests that will be run as serially batched with other tests in a single instance.

    Minimizes total test run duration by reducing repeated overhead from starting the instance.
    Does not support per test setup/teardown to avoid creating race conditions.
    """
    # Specifies if the test can be batched in the same instance.
    is_batchable = True
    # Specifies if the test can be run in multiple instances in parallel.
    is_parallelizable = True


class ParallelTest(SharedTest):
    """Test that will be run in parallel with tests in multiple instances."""
    is_batchable = False
    is_parallelizable = True


class BatchedTest(SharedTest):
    """Test that will be run as serially batched with other tests in a single instance."""
    is_batchable = True
    is_parallelizable = False


class AbstractTestSuite(object):
    """
    Main object used to run the tests.
    The new test suite class you create for your tests should inherit from this base AbstractTestSuite class.
    """
    # When this object is inherited, add any custom attributes as needed.
    # Test class that functions as the pytest test collector
    pytest_custom_makeitem_class = AbstractTestClass
    # Test class to use for single test collection
    single_test_class = SingleTest
    # Test class to use for shared test collection
    shared_test_class = SharedTest

    @classmethod
    def get_instance_log_str(cls):
        # type () -> str
        """
        Checks if a given instance's log attribute exists and returns it.
        :return: Either the object attribute matching "instance_log_attribute_name" or None.
        """
        log = getattr(cls, "instance_log_attribute_name", None)
        if log:
            return log
        else:
            return "-- No test log found --"

    @classmethod
    def get_output_str(cls):
        # type () -> str
        """
        Checks if the output attribute exists and returns it.
        :return: Output string from running a test, or a no output message.
        """
        output = getattr(cls, "output", None)
        if output:
            return output
        else:
            return "-- No output --"

    @classmethod
    def pytest_custom_makeitem(cls, collector, name, obj):
        return cls.pytest_custom_makeitem_class(name, collector)

    @staticmethod
    def get_number_parallel_instances():
        """
        Number of program instances to run in parallel, this method can be overridden by the user.
        Note: Some CLI options (i.e. '--editors-parallel') takes precedence over class settings.
        See ly_test_tools._internal.pytest_plugin.editor_test.py for full list of CLI options.
        :return: count of parallel program instances to run
        """
        count = 1
        found_processors = os.cpu_count()
        if found_processors:
            # only schedule on half the cores since the application will also run multithreaded
            # also compensates for hyperthreaded/clustered/virtual cores inflating this count
            count = math.floor(found_processors / 2)
            if count < 1:
                count = 1

        return count

    class TestData:
        __test__ = False  # Avoid pytest collection & warnings since "test" is in the class name.

        def __init__(self):
            self.results = {}  # Dict of str(test_spec.__name__) -> Result
            self.asset_processor = None

    @pytest.fixture(scope="class")
    def collected_test_data(self, request: _pytest.fixtures.FixtureRequest) -> AbstractTestSuite.TestData:
        """
        Yields a per-testsuite structure to store the data of each test result and an AssetProcessor object that will be
        re-used on the whole suite
        :request: The Pytest request object
        :yield: The TestData object
        """
        yield from self._collected_test_data(request)

    def _collected_test_data(self, request: _pytest.fixtures.FixtureRequest) -> AbstractTestSuite.TestData:
        """
        A wrapped implementation to simplify unit testing pytest fixtures. Users should not call this directly.
        :request: The Pytest request object (unused, but always passed by pytest)
        :yield: The TestData object
        """
        test_data = AbstractTestSuite.TestData()
        yield test_data  # yield to pytest while test-class executes
        # resumed by pytest after each test-class finishes
        if test_data.asset_processor:  # was assigned an AP to manage
            test_data.asset_processor.teardown()
            test_data.asset_processor = None
            editor_utils.kill_all_ly_processes(include_asset_processor=True)
        else:  # do not interfere as a preexisting AssetProcessor may be owned by something else
            editor_utils.kill_all_ly_processes(include_asset_processor=False)

    @classmethod
    def get_single_tests(cls) -> list[single_test_class]:
        """
        Grabs all of the single_test_class subclassed tests from the AbstractTestSuite class.
        Usage example:
           class MyTestSuite(AbstractTestSuite):
               class MyFirstTest(SingleTest):
                   from . import script_to_be_run_as_single_test as test_module
        :return: The list of single tests
        """
        single_tests = [
            c[1] for c in cls.__dict__.items() if inspect.isclass(c[1]) and issubclass(c[1], cls.single_test_class)]
        return single_tests

    @classmethod
    def get_shared_tests(cls) -> list[shared_test_class]:
        """
        Grabs all of the shared_test_class from the AbstractTestSuite
        Usage example:
           class MyTestSuite(AbstractTestSuite):
               class MyFirstTest(SharedTest):
                   from . import test_script_to_be_run_1 as test_module
               class MyFirstTest(SharedTest):
                   from . import test_script_to_be_run_2 as test_module
        :return: The list of shared tests
        """
        shared_tests = [
            c[1] for c in cls.__dict__.items() if inspect.isclass(c[1]) and issubclass(c[1], cls.shared_test_class)]
        return shared_tests

    @classmethod
    def get_session_shared_tests(cls, session: _pytest.main.Session) -> list[shared_test_class]:
        """
        Filters and returns all of the shared tests in a given session.
        :session: The test session
        :return: The list of tests
        """
        shared_tests = cls.get_shared_tests()
        return cls.filter_session_shared_tests(session, shared_tests)

    @staticmethod
    def filter_session_shared_tests(session_items: list[_pytest.python.Function(shared_test_class)],
                                    shared_tests: list[shared_test_class]) -> list[shared_test_class]:
        """
        Retrieve the test sub-set that was collected this can be less than the original set if were overridden via -k
        argument or similar
        :session_items: The tests in a session to run
        :shared_tests: All of the shared tests
        :return: The list of filtered tests
        """

        def will_run(item):
            try:
                skipping_pytest_runtest_setup(item)
                return True
            except (Warning, Exception, _pytest.outcomes.OutcomeException) as ex:
                # intentionally broad to avoid events other than system interrupts
                warnings.warn(f"Test deselected from execution queue due to {ex}")
                return False

        session_items_by_name = {item.originalname: item for item in session_items}
        selected_shared_tests = [test for test in shared_tests if test.__name__ in session_items_by_name.keys() and
                                 will_run(session_items_by_name[test.__name__])]
        return selected_shared_tests

    @staticmethod
    def filter_shared_tests(shared_tests: list[shared_test_class],
                            is_batchable: bool = False,
                            is_parallelizable: bool = False) -> list[shared_test_class]:
        """
        Filters and returns all tests based off of if they are batched and/or parallel
        :shared_tests: All shared tests
        :is_batchable: Filter to batched tests
        :is_parallelizable: Filter to parallel tests
        :return: The list of filtered tests
        """
        return [
            t for t in shared_tests if (
                    getattr(t, "is_batchable", None) is is_batchable
                    and
                    getattr(t, "is_parallelizable", None) is is_parallelizable
            )
        ]

    def _prepare_asset_processor(self,
                                 workspace: ly_test_tools._internal.managers.workspace.AbstractWorkspaceManager,
                                 collected_test_data: TestData) -> None:
        """
        Prepares the asset processor for the test depending on whether or not the process is open and if the current
        test owns it.
        :workspace: The workspace object in case an AssetProcessor object needs to be created
        :editor_test_data: The test data from calling editor_test_data()
        :return: None
        """
        try:
            # Start-up an asset processor if we are not already managing one
            if collected_test_data.asset_processor is None:
                if not process_utils.process_exists("AssetProcessor", ignore_extensions=True):
                    editor_utils.kill_all_ly_processes(include_asset_processor=True)
                    collected_test_data.asset_processor = AssetProcessor(workspace)
                    collected_test_data.asset_processor.start()
                else:  # If another AP process already exists, do not kill it as we do not manage it
                    editor_utils.kill_all_ly_processes(include_asset_processor=False)
            else:  # Make sure existing asset processor wasn't closed by accident
                collected_test_data.asset_processor.start()
        except Exception as ex:
            collected_test_data.asset_processor = None
            raise ex

    @staticmethod
    def _get_results_using_output(test_spec_list: list[AbstractTestBase],
                                  output: str,
                                  test_log_content: str) -> dict[any, [Result.Unknown, Result.Pass, Result.Fail]]:
        """
        Utility function for parsing the output information from the test. It deserializes the JSON content printed in
        the output for every test and returns that information.
        :test_spec_list: The list of tests inheriting from AbstractTestBase
        :output: The output str to parse results from
        :test_log_content: The contents of the test log as a string
        :return: A dict of the tests and their respective Result objects
        """
        results = {}
        pattern = re.compile(r"JSON_START\((.+?)\)JSON_END")
        out_matches = pattern.finditer(output)
        found_jsons = {}
        for m in out_matches:
            try:
                elem = json.loads(m.groups()[0])
                found_jsons[elem["name"]] = elem
            except Exception:  # Intentionally broad to avoid failing if the output data is corrupt
                continue

        # Try to find the element in the log, this is used for cutting the log contents later
        log_matches = pattern.finditer(test_log_content)
        for m in log_matches:
            try:
                elem = json.loads(m.groups()[0])
                if elem["name"] in found_jsons:
                    found_jsons[elem["name"]]["log_match"] = m
            except Exception:  # Intentionally broad, to avoid failing if the log data is corrupt
                continue

        log_start = 0
        for test_spec in test_spec_list:
            name = editor_utils.get_module_filename(test_spec.test_module)
            if name not in found_jsons.keys():
                results[test_spec.__name__] = Result.Unknown(
                    test_spec, output,
                    f"Found no test run information on stdout for {name} in the test log",
                    test_log_content)
            else:
                result = None
                json_result = found_jsons[name]
                json_output = json_result["output"]

                # Cut the editor log so it only has the output for this run
                if "log_match" in json_result:
                    m = json_result["log_match"]
                    end = m.end() if test_spec != test_spec_list[-1] else -1
                else:
                    end = -1
                cur_log = test_log_content[log_start: end]
                log_start = end

                if json_result["success"]:
                    result = Result.Pass(test_spec, json_output, cur_log)
                else:
                    result = Result.Fail(test_spec, json_output, cur_log)
                results[test_spec.__name__] = result

        return results

    @staticmethod
    def _report_result(name: str, result: Result) -> None:
        """
        Fails the test if the test result is not a PASS, specifying the information
        :name: Name of the test
        :result: The Result object which denotes if the test passed or not
        :return: None
        """
        if isinstance(result, Result.Pass):
            output_str = f"Test {name}:\n{str(result)}"
            print(output_str)
        else:
            error_str = f"Test {name}:\n{str(result)}"
            pytest.fail(error_str)

    def _setup_test_run(self,
                        workspace: AbstractWorkspaceManager,
                        collected_test_data: AbstractTestSuite.TestData) -> None:
        """
        Sets up a test run by preparing the Asset Processor and killing all other O3DE processes relevant to tests.
        :workspace: The test Workspace object
        :collected_test_data: The TestData from calling collected_test_data()
        :return: None
        """
        self._prepare_asset_processor(workspace, collected_test_data)
        editor_utils.kill_all_ly_processes(include_asset_processor=False)

