# coding:utf-8
#!/usr/bin/python
#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#
# -------------------------------------------------------------------------
"""! DccScriptingInterface:: constants.py

Commonly used global constants and default values.
"""
# -------------------------------------------------------------------------
# standard imports
import os
import sys
from pathlib import Path
import logging as _logging
# -------------------------------------------------------------------------
_MODULENAME = 'DCCsi.constants'
_LOGGER = _logging.getLogger(_MODULENAME)
_LOGGER.debug(f'Initializing: {_MODULENAME}')
_MODULE_PATH = Path(__file__) # this module should not be used as an entry
PATH_DCCSIG = _MODULE_PATH.parents[0].resolve()
sys.path.append(PATH_DCCSIG)
# -------------------------------------------------------------------------

# global constants here
# all the constants moved here, need to be removed from azpy.constants
# and then modules should be refactored to all pull from here

# ENVAR_ denotes a common key string

# name of o3de folder in user home, TAG_USER_O3DE = '.o3de'
from DccScriptingInterface import TAG_USER_O3DE

# the user home
from DccScriptingInterface import USER_HOME

# envar to get/set/override the logging level
from DccScriptingInterface import ENVAR_DCCSI_LOGLEVEL

# envar to get/set/override the engine root
from DccScriptingInterface import ENVAR_O3DE_DEV

# a str path constructor for the dccsi 3rdParty site-dir
from DccScriptingInterface import STR_DCCSI_PYTHON_LIB

# envar to get/set/override the location of the dccsi gem
from DccScriptingInterface import ENVAR_PATH_DCCSIG

# envar to get/set/override the location of DCCsi
# 3rdParty package dependencies (site-directory)
from DccScriptingInterface import ENVAR_PATH_DCCSI_PYTHON_LIB

# a path string constructor for that site-dir location
from DccScriptingInterface import STR_DCCSI_PYTHON_LIB

# envar to get/set/override project path
from DccScriptingInterface import ENVAR_PATH_O3DE_PROJECT

# envar to get/set/override project name
from DccScriptingInterface import ENVAR_O3DE_PROJECT

# envar to get/set/override the \bin executables folder
from DccScriptingInterface import ENVAR_PATH_O3DE_BIN

# the common filename.ext for local/override settings file
from DccScriptingInterface import DCCSI_SETTINGS_LOCAL_FILENAME

# common logging formatting strings
from DccScriptingInterface import FRMT_LOG_SHRT
from DccScriptingInterface import FRMT_LOG_LONG

# manifest filename, 'o3de_manifest.json'
from DccScriptingInterface import SLUG_MANIFEST_FILENAME

# # {user_home}\.o3de\registry\bootstrap.setreg
from DccScriptingInterface import SLUG_BOOTSTRAP_FILENAME

# resolves the windows program install directory
ENVAR_PROGRAMFILES_X86 = 'PROGRAMFILES(X86)'
PATH_PROGRAMFILES_X86 = os.environ[ENVAR_PROGRAMFILES_X86]
# resolves the windows program install directory
ENVAR_PROGRAMFILES_X64 = 'PROGRAMFILES'
PATH_PROGRAMFILES_X64 = os.environ[ENVAR_PROGRAMFILES_X64]

# path string constructor
PATH_USER_O3DE = f'{USER_HOME}\\{TAG_USER_O3DE}'
# user home o3se registry
SLUG_DIR_REGISTRY = 'Registry'
# path string constructor
PATH_USER_O3DE_REGISTRY = f'{PATH_USER_O3DE}\\{SLUG_DIR_REGISTRY}'

# logging into the user home o3de cache (temporarily)
SLUG_DCCSI_SHORT = 'DCCsi'
PATH_DCCSI_LOG_PATH = (f'{PATH_USER_O3DE}\\Cache\\log' +
                       f'\\{SLUG_DCCSI_SHORT}' +
                       f'\\{SLUG_DCCSI_SHORT}.log')

# envar to get/set the < dccsi>/tools folder
ENVAR_PATH_DCCSI_TOOLS = 'PATH_DCCSI_TOOLS'

# envar to get/set the < dccsi>/tools/IDE folder
ENVAR_PATH_DCCSI_TOOLS_IDE = 'PATH_DCCSI_TOOLS_IDE'

# envar to get/set the < dccsi>/tools/IDE/Wing folder
ENVAR_PATH_DCCSI_TOOLS_IDE_WING = 'PATH_DCCSI_TOOLS_IDE_WING'

# envar to get/set bool for global DCCSI_GDEBUG behavior
ENVAR_DCCSI_GDEBUG = 'DCCSI_GDEBUG'

# envar to get/set bool for developer mode (debugging)
ENVAR_DCCSI_DEV_MODE = 'DCCSI_DEV_MODE'

# envar to get/set the ide debugger str/slug (only 'WING' implemented)
ENVAR_DCCSI_GDEBUGGER = 'DCCSI_GDEBUGGER'

# envar to get/set bool for running extra local tests
ENVAR_DCCSI_TESTS = 'DCCSI_TESTS'

# a str prefix for dynamic settings
DCCSI_DYNAMIC_PREFIX = 'DYNACONF'

# utility: constants, like pretty print strings
from DccScriptingInterface import STR_CROSSBAR
STR_CROSSBAR_RL = f'{STR_CROSSBAR}\r'
STR_CROSSBAR_NL = f'{STR_CROSSBAR}\n'
# -------------------------------------------------------------------------


###########################################################################
# Main Code Block, runs this script as main (testing)
# -------------------------------------------------------------------------
if __name__ == '__main__':
    """Run as main, perform additional debug and module tests"""

    pass

