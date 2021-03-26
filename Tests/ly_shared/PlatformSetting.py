"""
All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
its licensors.

For complete copyright and license terms please see the LICENSE at the root of this
distribution (the "License"). All use of this software is governed by the License,
or, if provided, by the license below or the license accompanying this file. Do not
remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

Class for querying and setting a system setting/preference.

"""

import pytest
import logging
from typing import Optional, Any

import ly_test_tools.lumberyard.pipeline_utils as utils

logger = logging.getLogger(__name__)


class PlatformSetting:
    """
    Interface for managing different platforms' system variables.
    """

    class DATA_TYPE:
        """Platform-agnostic data type enums"""

        INT = 1
        STR = 2
        STR_LIST = 3

    def __init__(self, workspace: pytest.fixture, subkey: str, key: str) -> None:
        self._workspace = workspace
        self._key = key
        self._subkey = subkey

    def get_value(self, get_type: bool = False) -> object:
        """Gets the current setting's value (and optionally type as tuple) from the system. Returns None if entry DNE"""
        raise NotImplementedError("Virtual PlatformSetting not implemented. Instantiate a specific platform")

    def set_value(self, value: any) -> bool:
        """Sets the current setting's value. Creates the entry if it DNE. Returns True for success."""
        raise NotImplementedError("Virtual PlatformSetting not implemented. Instantiate a specific platform")

    def delete_entry(self) -> bool:
        """Deletes the settings entry. Returns boolean for success."""
        raise NotImplementedError("Virtual PlatformSetting not implemented. Instantiate a specific platform")

    def entry_exists(self) -> bool:
        """Checks if the settings entry exists."""
        raise NotImplementedError("Virtual PlatformSetting not implemented. Instantiate a specific platform")

    @staticmethod
    def get_system_setting(workspace: pytest.fixture, subkey: str, key: str, hive: Optional[str] = None) -> Any:
        """Factory method creates a platform-specific system setting accessor"""
        if workspace.asset_processor_platform is 'windows':
            # import WindowsSetting and return an instance
            from Tests.ly_shared.WindowsRegistrySetting import WindowsRegistrySetting

            return WindowsRegistrySetting(workspace, subkey, key, hive)
        # ########################################################
        #       Insert Mac (and Linux?) Setting implementations
        # ########################################################
        else:
            raise NotImplementedError(f"Platform: {workspace.platform} not supported yet")
