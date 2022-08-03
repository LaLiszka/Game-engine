"""
Copyright (c) Contributors to the Open 3D Engine Project.
For complete copyright and license terms please see the LICENSE at the root of this distribution.

SPDX-License-Identifier: Apache-2.0 OR MIT
"""


def Menus_EditMenuOptions_Work():
    """
    Summary:
    Interact with Edit Menu options and verify if all the options are working.

    Expected Behavior:
    The Edit menu functions normally.

    Test Steps:
     1) Open an existing level
     2) Interact with Edit Menu options

    Note:
    - This test file must be called from the O3DE Editor command terminal
    - Any passed and failed tests are written to the Editor.log file.
            Parsing the file or running a log_monitor are required to observe the test results.

    :return: None
    """

    import editor_python_test_tools.hydra_editor_utils as hydra
    import pyside_utils
    from editor_python_test_tools.utils import Report

    edit_menu_options = [
        ("Undo",),
        ("Redo",),
        ("Duplicate",),
        ("Delete",),
        ("Select All",),
        ("Invert Selection",),
        ("Toggle Pivot Location",),
        ("Reset Entity Transform",),
        ("Reset Manipulator",),
        ("Hide Selection",),
        ("Show All",),
        ("Lock Selection",),
        ("Unlock All Entities",),
        ("Modify", "Snap", "Angle snapping"),
        ("Modify", "Snap", "Grid snapping"),
        ("Modify", "Transform Mode", "Move"),
        ("Modify", "Transform Mode", "Rotate"),
        ("Modify", "Transform Mode", "Scale"),
        ("Editor Settings", "Global Preferences"),
        ("Editor Settings", "Editor Settings Manager"),
        ("Editor Settings", "Keyboard Customization", "Customize Keyboard"),
        # The following menu options are temporarily disabled due to https://github.com/o3de/o3de/issues/6746
        #("Editor Settings", "Keyboard Customization", "Export Keyboard Settings"),
        #("Editor Settings", "Keyboard Customization", "Import Keyboard Settings"),
    ]

    # 1) Open an existing simple level
    hydra.open_base_level()

    # 2) Interact with Edit Menu options
    editor_window = pyside_utils.get_editor_main_window()
    for option in edit_menu_options:
        try:
            action = pyside_utils.get_action_for_menu_path(editor_window, "Edit", *option)
            Report.info(f"Triggering {action.iconText()}")
            action.trigger()
            action_triggered = True
        except Exception as e:
            action_triggered = False
            print(e)
        menu_action_triggered = (
            f"{action.iconText()} action triggered successfully",
            f"Failed to trigger {action.iconText()} action"
        )
        Report.result(menu_action_triggered, action_triggered)


if __name__ == "__main__":

    from editor_python_test_tools.utils import Report
    Report.start_test(Menus_EditMenuOptions_Work)
