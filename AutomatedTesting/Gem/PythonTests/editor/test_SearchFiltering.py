"""
All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
its licensors.

For complete copyright and license terms please see the LICENSE at the root of this
distribution (the "License"). All use of this software is governed by the License,
or, if provided, by the license below or the license accompanying this file. Do not
remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
"""

"""
C13660194 : Asset Browser - Filtering
"""

import os
import pytest
# Bail on the test if ly_test_tools doesn't exist.
pytest.importorskip('ly_test_tools')
import ly_test_tools.environment.file_system as file_system
import automatedtesting_shared.hydra_test_utils as hydra

test_directory = os.path.join(os.path.dirname(__file__), "EditorScripts")
log_monitor_timeout = 90


@pytest.mark.parametrize('project', ['AutomatedTesting'])
@pytest.mark.parametrize('level', ['tmp_level'])
@pytest.mark.usefixtures("automatic_process_killer")
@pytest.mark.parametrize("launcher_platform", ['windows_editor'])
class TestSearchFiltering(object):

    @pytest.fixture(autouse=True)
    def setup_teardown(self, request, workspace, project, level):
        def teardown():
            file_system.delete([os.path.join(workspace.paths.dev(), project, "Levels", level)], True, True)

        request.addfinalizer(teardown)

        file_system.delete([os.path.join(workspace.paths.dev(), project, "Levels", level)], True, True)

    @pytest.mark.test_case_id("C13660194")
    @pytest.mark.SUITE_periodic
    def test_SearchFiltering_Asset_Browser_Filtering(self, request, editor, level, launcher_platform):
        expected_lines = [
            "cedar.fbx asset is filtered in Asset Browser",
            "Animation file type(s) is present in the file tree: True",
            "FileTag file type(s) and Animation file type(s) is present in the file tree: True",
            "FileTag file type(s) is present in the file tree after removing Animation filter: True",
        ]

        unexpected_lines = [
            "Asset Browser opened: False",
            "Animation file type(s) is present in the file tree: False",
            "FileTag file type(s) and Animation file type(s) is present in the file tree: False",
            "FileTag file type(s) is present in the file tree after removing Animation filter: False",
        ]
        
        hydra.launch_and_validate_results(
            request,
            test_directory,
            editor,
            "SearchFiltering_Asset_Browser_Filtering.py",
            expected_lines,
            unexpected_lines=unexpected_lines,
            cfg_args=[level],
            auto_test_mode=False,
            run_python="--runpython",
            timeout=log_monitor_timeout,
        )
