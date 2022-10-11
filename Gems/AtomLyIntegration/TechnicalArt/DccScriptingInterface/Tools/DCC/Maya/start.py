#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#
# -------------------------------------------------------------------------
"""! O3DE DCCsi DCC Maya App start module

There are severl ways this can be used:
1. From cli
    - open a cmd
    - change directory > cd c:\\path\\to\\DccScriptingInterface
    - run command > python Tools\\DCC\\Maya\\start.py

2. The O3DE editor uses this module to launch from menu and editor systems

:file: DccScriptingInterface\\Tools\\DCC\\Maya\\start.py
:Status: Prototype
:Version: 0.0.1
:Entrypoint: entrypoint, configures logging, includes cli
:Notice:
    Currently windows only (not tested on other platforms)
    Currently only tested Maya 2022/23 with Python3
"""
# -------------------------------------------------------------------------
import timeit
_MODULE_START = timeit.default_timer()  # start tracking

# standard imports
import sys
import os
import subprocess
from pathlib import Path
import logging as _logging
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# global scope
from DccScriptingInterface.Tools.DCC.Maya import _PACKAGENAME
_MODULENAME = f'{_PACKAGENAME}.start'
_MODULE_PATH = Path(__file__)

# this is an entry point, we must self bootstrap
PATH_O3DE_TECHART_GEMS = _MODULE_PATH.parents[4].resolve()
os.chdir(PATH_O3DE_TECHART_GEMS.as_posix())

#sys.path.append(PATH_O3DE_TECHART_GEMS.as_posix())
from DccScriptingInterface import add_site_dir
add_site_dir(PATH_O3DE_TECHART_GEMS)

# get the global dccsi state
from DccScriptingInterface.globals import DCCSI_GDEBUG
from DccScriptingInterface.globals import DCCSI_DEV_MODE

from azpy.constants import FRMT_LOG_LONG
_logging.basicConfig(level=_logging.DEBUG,
                     format=FRMT_LOG_LONG,
                    datefmt='%m-%d %H:%M')

_LOGGER = _logging.getLogger(_MODULENAME)

# auto-attach ide debugging at the earliest possible point in module
if DCCSI_DEV_MODE:
    if DCCSI_GDEBUGGER == 'WING':
        import DccScriptingInterface.azpy.test.entry_test
        DccScriptingInterface.azpy.test.entry_test.connect_wing()
    elif DCCSI_GDEBUGGER == 'PYCHARM':
        _LOGGER.warning(f'{DCCSI_GDEBUGGER} debugger auto-attach not yet implemented')
    else:
        _LOGGER.warning(f'{DCCSI_GDEBUGGER} not a supported debugger')

_LOGGER.debug(f'Initializing: {_MODULENAME}')
_LOGGER.debug(f'_MODULE_PATH: {_MODULE_PATH.as_posix()}')

# this should execute the core config.py first and grab settings
from DccScriptingInterface.Tools.DCC.Maya.config import maya_config
maya_config.settings.setenv() # init settings, ensure env is set

from DccScriptingInterface.azpy.config_utils import check_is_ascii

# store a copy, so we can inspect/compare later
orig_env = os.environ.copy()

# we are going to pass the system environ
maya_env = os.environ.copy()

# prunes non-string key:value envars
maya_env = {key: value for key, value in maya_env.items() if check_is_ascii(key) and check_is_ascii(value)}

# will prune QT_ envars, to be used with QT bases apps like Maya or Wing
maya_env = {key: value for key, value in maya_env.items() if not key.startswith("QT_")}

if DCCSI_GDEBUG:
    # we can see what was pruned
    pruned = {k: maya_env[k] for k in set(maya_env) - set(orig_env)}

    if len(pruned.items()):
        _LOGGER.debug(f'prune diff is ...')
        for p in pruned.items():
            _LOGGER.debug(f'{p}')
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# default launch command
# let us make sure that we are passing a windows path
_LAUNCH_EXE = Path(maya_config.settings.DCCSI_MAYA_EXE)

_LAUNCH_COMMAND = [f'{str(_LAUNCH_EXE)}']

# suggestion for future PR is to refactor this method into something like
# DccScriptingInterface.azpy.utils.start.popen()
def popen(command: list = _LAUNCH_COMMAND,
          env: dict = maya_env) -> subprocess:

    f"""Method call to start the DCC app {_PACKAGENAME}"""

    _LOGGER.info(f'Attempting to start {_PACKAGENAME} ...')
    _LOGGER.info(f'Command args: {command}')

    process = subprocess.Popen(args = command,
                               env = env,
                               shell=True,
                               stdout = subprocess.PIPE,
                               stderr = subprocess.PIPE,
                               close_fds=True)

    out, err = process.communicate()

    if process.returncode != 0:
        _LOGGER.error(f'{_PACKAGENAME} did not start ...')
        _LOGGER.error(f'{out}')
        _LOGGER.error(f'{err}')
        return None
    else:
        _LOGGER.info(f'Success: {_PACKAGENAME} started correctly!')

    return process
# -------------------------------------------------------------------------


###########################################################################
# Main Code Block, runs this script as main (testing)
# -------------------------------------------------------------------------
if __name__ == '__main__':
    """Run this file as main (external commandline)"""

    _MODULENAME = f'{_MODULENAME}.cli'

    from DccScriptingInterface.globals import *

    from DccScriptingInterface.constants import STR_CROSSBAR
    from DccScriptingInterface.constants import FRMT_LOG_LONG

    # configure basic logger
    # note: not using a common logger to reduce cyclical imports
    _logging.basicConfig(level=DCCSI_LOGLEVEL,
                         format=FRMT_LOG_LONG,
                         datefmt='%m-%d %H:%M')

    _LOGGER = _logging.getLogger(_MODULENAME)

    # log global state to cli
    _LOGGER.info(STR_CROSSBAR)
    _LOGGER.debug(f'_MODULENAME: {_MODULENAME}')
    _LOGGER.debug(f'{ENVAR_DCCSI_GDEBUG}: {DCCSI_GDEBUG}')
    _LOGGER.debug(f'{ENVAR_DCCSI_DEV_MODE}: {DCCSI_DEV_MODE}')
    _LOGGER.debug(f'{ENVAR_DCCSI_LOGLEVEL}: {DCCSI_LOGLEVEL}')

    # commandline interface
    import argparse
    parser = argparse.ArgumentParser(
        description=f'O3DE {_MODULENAME}',
        epilog=(f"Attempts to start Maya with the DCCsi and O3DE bootstrapping"))

    parser.add_argument('-gd', '--global-debug',
                        type=bool,
                        required=False,
                        default=False,
                        help='Enables global debug flag.')

    parser.add_argument('-ex', '--exit',
                        type=bool,
                        required=False,
                        default=False,
                        help='Exits python. Do not exit if you want to be in interactive interpreter after config')

    args = parser.parse_args()

    try:
        process = popen(command = _LAUNCH_COMMAND,
                        env = maya_env)
    except Exception as e:
        _LOGGER.warning(f'Could not start {_MODULENAME}')
        _LOGGER.error(f'{e} , traceback =', exc_info=True)
        if DCCSI_STRICT:
            _LOGGER.exception(f'{e} , traceback =', exc_info=True)
            raise e

    # -- DONE ----
    _LOGGER.info(STR_CROSSBAR)

    _LOGGER.debug('{0} took: {1} sec'.format(_MODULENAME, timeit.default_timer() - _MODULE_START))

    if args.exit:
        import sys
        # return
        sys.exit()
    else:
        # custom prompt
        sys.ps1 = "[{}]>>".format(_MODULENAME)
# --- END -----------------------------------------------------------------
