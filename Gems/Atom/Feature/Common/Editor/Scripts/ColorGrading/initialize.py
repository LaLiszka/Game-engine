# coding:utf-8
#!/usr/bin/python
#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

# standard imports
import sys
import os
import pathlib
import site
from pathlib import Path
import logging as _logging

# local imports
from ColorGrading import env_bool
from ColorGrading import initialize_logger
from ColorGrading import DCCSI_GDEBUG
from ColorGrading import DCCSI_DEV_MODE
from ColorGrading import DCCSI_GDEBUGGER
from ColorGrading import DCCSI_LOGLEVEL
from ColorGrading import FRMT_LOG_LONG

__all__ = ['start']

# ------------------------------------------------------------------------
_PACKAGENAME = 'ColorGrading'
_MODULENAME = 'ColorGrading.initialize'

if DCCSI_GDEBUG:
    DCCSI_LOGLEVEL = int(10)

# set up logger with both console and file _logging
if DCCSI_GDEBUG:
    _LOGGER = initialize_logger(_PACKAGENAME, log_to_file=True, default_log_level=DCCSI_LOGLEVEL)
else:
    _LOGGER = initialize_logger(_PACKAGENAME, log_to_file=False, default_log_level=DCCSI_LOGLEVEL)
        
_LOGGER.debug('Initializing: {0}.'.format({_MODULENAME}))

# connect to the debugger
if DCCSI_DEV_MODE:
    APP_DATA_WING = Path('C:/Users/gallowj/AppData/Roaming/Wing Pro 7')
    APP_DATA_WING.resolve()
    site.addsitedir(pathlib.PureWindowsPath(APP_DATA_WING).as_posix())
    import wingdbstub as debugger
    try:
        debugger.Ensure()
        _LOGGER.info("Wing debugger attached")
    except Exception as e:
        _LOGGER.debug('Can not attach Wing debugger (running in IDE already?)')
# ------------------------------------------------------------------------


# ------------------------------------------------------------------------
def start():
    """set up access to OpenImageIO, within o3de or without"""
    # ------------------------------------------------------------------------
    try:
        # running in o3de
        import azlmbr
        
        _O3DE_DEV = Path(os.getenv('O3DE_DEV', Path(azlmbr.paths.engroot)))
        os.environ['O3DE_DEV'] = pathlib.PureWindowsPath(_O3DE_DEV).as_posix()
        _LOGGER.debug(_O3DE_DEV)
    
        _O3DE_BIN_PATH = Path(str(_O3DE_DEV),Path(azlmbr.paths.executableFolder))
    
        _O3DE_BIN = Path(os.getenv('O3DE_BIN', _O3DE_BIN_PATH.resolve()))
        os.environ['O3DE_BIN'] = pathlib.PureWindowsPath(_O3DE_BIN).as_posix()
    
        _LOGGER.debug(_O3DE_BIN)
    
        site.addsitedir(_O3DE_BIN)
    
    except Exception as e:
        # running external, start this module from:
        # "C:\Depot\o3de-engine\Gems\Atom\Feature\Common\Tools\ColorGrading\cmdline\CMD_ColorGradinTools.bat"
        pass
    
        try:
            _O3DE_DEV = Path(os.getenv('O3DE_DEV'))
            _O3DE_DEV = _O3DE_DEV.resolve()
            os.environ['O3DE_DEV'] = pathlib.PureWindowsPath(_O3DE_DEV).as_posix()
            _LOGGER.debug(f'O3DE_DEV is: {_O3DE_DEV}')
        except EnvironmentError as e:
            _LOGGER.error('O3DE engineroot not set or found')
            raise e
    
        try:
            _TAG_LY_BUILD_PATH = os.getenv('TAG_LY_BUILD_PATH', 'build')
            _DEFAULT_BIN_PATH = Path(str(_O3DE_DEV), _TAG_LY_BUILD_PATH, 'bin', 'profile')
            _O3DE_BIN_PATH = Path(os.getenv('O3DE_BIN_PATH', _DEFAULT_BIN_PATH))
            _O3DE_BIN_PATH = _O3DE_BIN_PATH.resolve()
            os.environ['O3DE_BIN_PATH'] = pathlib.PureWindowsPath(_O3DE_BIN_PATH).as_posix()
            _LOGGER.debug(f'O3DE_BIN_PATH is: {_O3DE_BIN_PATH}')
            site.addsitedir(pathlib.PureWindowsPath(_O3DE_BIN_PATH).as_posix())
        except EnvironmentError as e:
            _LOGGER.error('O3DE bin folder not set or found')
            raise e
# ------------------------------------------------------------------------


# ------------------------------------------------------------------------
try:
    import OpenImageIO as OpenImageIO
except ImportError as e:
    _LOGGER.error(f"invalid import: {e}")
    sys.exit(1)
# ------------------------------------------------------------------------


###########################################################################
# Main Code Block, runs this script as main (testing)
# -------------------------------------------------------------------------
if __name__ == '__main__':
    """Run this file as main"""

    start()