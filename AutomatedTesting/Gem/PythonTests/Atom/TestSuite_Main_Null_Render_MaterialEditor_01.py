"""
Copyright (c) Contributors to the Open 3D Engine Project.
For complete copyright and license terms please see the LICENSE at the root of this distribution.

SPDX-License-Identifier: Apache-2.0 OR MIT
"""
import logging
import pytest

from ly_test_tools.o3de.atom_tools_test import AtomToolsBatchedTest, AtomToolsTestSuite

logger = logging.getLogger(__name__)


@pytest.mark.parametrize("project", ["AutomatedTesting"])
@pytest.mark.parametrize("launcher_platform", ['windows_material_editor'])
class TestMaterialEditor(AtomToolsTestSuite):

    class MaterialEditor_Atom_LaunchMaterialEditor_1(AtomToolsBatchedTest):

        from Atom.tests import MaterialEditor_Atom_LaunchMaterialEditor as test_module

    class MaterialEditor_Atom_LaunchMaterialEditor_2(AtomToolsBatchedTest):

        from Atom.tests import MaterialEditor_Atom_LaunchMaterialEditor as test_module
