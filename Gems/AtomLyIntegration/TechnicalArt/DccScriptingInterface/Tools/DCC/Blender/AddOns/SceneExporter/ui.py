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
from multiprocessing import context
import bpy
from pathlib import Path
import webbrowser
import re
from bpy_extras.io_utils import ExportHelper, ImportHelper
from bpy.types import Panel, Operator, PropertyGroup, AddonPreferences
from bpy.props import EnumProperty, StringProperty, BoolProperty, PointerProperty
from . import constants
from . import fbx_exporter
from . import o3de_utils
from . import utils
import addon_utils


def message_box(message = "", title = "Message Box", icon = 'LIGHT'):
    """!
    This function will show a messagebox to inform user.
    @param message This is the message box main string message
    @param title This is the title of the message box string
    @param icon This is the Blender icon used in the message box gui
    """
    def draw(self, context):
        """!
        This function draws this gui element in Blender UI
        """
        self.layout.label(text = message)
    bpy.context.window_manager.popup_menu(draw, title = title, icon = icon)

class MessageBox(bpy.types.Operator):
    """!
    This Class is for the UI Message Box Pop-Up
    """
    bl_idname = "message.popup"
    bl_label = "O3DE Scene Exporter"

    def invoke(self, context, event):
        """!
        This function will invoke the blender windowe manager
        """
        window_manager = context.window_manager
        return window_manager.invoke_props_dialog(self)

    def draw(self, context):
        """!
        This function draws this gui element in Blender UI
        """
        layout = self.layout
        layout.label(text=bpy.types.Scene.pop_up_notes)
        
    def execute(self, context):
        """!
        This will update the UI with the current o3de Project Title.
        """
        return {'FINISHED'}

class MessageBoxConfirm(bpy.types.Operator):
    """!
    This Class is for the UI Message Box Pop-Up but with extra properties that can be added.
    """
    bl_idname = "message_confirm.popup"
    bl_label = "O3DE Scene Exporter"
    bl_options = {'REGISTER', 'INTERNAL'}
    
    question_one: bpy.props.BoolProperty()

    @classmethod
    def poll(cls, context):
        return True

    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)

    def draw(self, context):

        layout = self.layout
        layout.label(text=bpy.types.Scene.pop_up_confirm_label)
        layout.prop(self, "question_one", text=bpy.types.Scene.pop_up_question_label)
        bpy.types.Scene.pop_up_question_bool = self.question_one
    
    def execute(self, context):
        """!
        This will update the UI with the current o3de Project Title.
        """
        utils.create_udp()
        self.report({'INFO'}, "OKAY")
        return {'FINISHED'}

class WikiButton(bpy.types.Operator):
    """!
    This Class is for the UI Wiki Button
    """
    bl_idname = "vin.wiki"
    bl_label = "O3DE Github Wiki"

    def execute(self, context):
        """!
        This function will open a web browser window.
        """
        webbrowser.open(constants.WIKI_URL)
        return{'FINISHED'}
class CustomProjectPath(bpy.types.Operator, ImportHelper):
    """!
    This Class is for setting a custom project path
    """
    bl_idname = "project.open_filebrowser"
    bl_label = "Project Assets Folder"
    bl_options = {'PRESET', 'UNDO'}

    filter_glob: StringProperty(
        default="//",
        options={'HIDDEN'},
        subtype='NONE',
        maxlen=255,  # Max internal buffer length, longer would be clamped.
        )

    def execute(self, context):
        # Look at current project list, if path not in list add it
        real_path =  Path(self.filepath)
        if real_path.is_dir():
            bpy.types.Scene.selected_o3de_project_path = str(Path(self.filepath))
        else:
            bpy.types.Scene.selected_o3de_project_path = str(Path(self.filepath).parent)
        if bpy.types.Scene.selected_o3de_project_path not in context.scene.o3de_projects_list:
            o3de_utils.save_project_list_json(str(bpy.types.Scene.selected_o3de_project_path))
            # Refesh the addon
            addon_utils.enable('SceneExporter')
            # Rebuild the project list
            o3de_utils.build_projects_list() 
        return {'FINISHED'}

class AddColliderMesh(bpy.types.Operator):
    """!
    This Class is for the UI Wiki Button
    """
    bl_idname = "vin.collider"
    bl_label = "Add a PhysX Collider mesh to selected."

    def execute(self, context):
        """!
        This function will create the collision mesh.
        """
        # Create a Pop-Up confirm window
        bpy.types.Scene.pop_up_confirm_label = 'Adding UDP Type: o3de_atom_phys to mesh.'
        bpy.types.Scene.pop_up_question_label = 'Add UDP to a Duplicate mesh?'
        bpy.types.Scene.udp_type = constants.UDP.get('o3de_atom_phys')
        bpy.ops.message_confirm.popup('INVOKE_DEFAULT')
        return{'FINISHED'}

class AddLODMesh(bpy.types.Operator):
    """!
    This Class is for the UI Wiki Button
    """
    bl_idname = "vin.lod"
    bl_label = "Add a LOD mesh to selected."

    def execute(self, context):
        """!
        This function will create the LOD mesh
        """
        # Create a Pop-Up confirm window
        bpy.types.Scene.pop_up_confirm_label = 'Adding UDP Type: o3de_atom_lod to mesh.'
        bpy.types.Scene.pop_up_question_label = 'Add UDP to a Duplicate mesh?'
        bpy.types.Scene.udp_type = constants.UDP.get('o3de_atom_lod')
        bpy.ops.message_confirm.popup('INVOKE_DEFAULT')
        return{'FINISHED'}

class ExportFiles(bpy.types.Operator):
    """!
    This function will send to selected mesh to an O3DE Project Path.
    """
    bl_idname = "vin.o3defilexport"
    bl_label = "SENDFILES"

    def export_files(self, file_name):
        """!
        This function will export the selected as an .fbx to the current project path.
        @param file_name is the file name selected or string in export_file_name_o3de
        """
        # Add file ext
        file_name = f'{file_name}.fbx'
        fbx_exporter.fbx_file_exporter('', file_name)

    def execute(self, context):
        """!
        This function will check the current selected count and multi_file_export_o3de bool is True or False.
        If multi_file_export_o3de is True it will export each selected object as an .fbx file, if False it will
        export all objects selected as one .fbx.
        @param context defualt for this blender class
        """
        # Validate a selection
        valid_selection, selected_name = utils.check_selected()
        # Check if there are multi selections
        if len(selected_name) > 1:
            if bpy.types.Scene.multi_file_export_o3de:
                for obj_name in selected_name:
                    # Deselect all or will just keep adding to selection
                    bpy.ops.object.select_all(action='DESELECT')
                    # Select a mesh in the loop
                    bpy.data.objects[obj_name].select_set(True)
                    # Remove some nasty invalid char
                    file_name = re.sub(r'\W+', '', obj_name)
                    # Export file
                    self.export_files(file_name)
            else:
                # Remove some nasty invalid char
                file_name = re.sub(r'\W+', '', bpy.context.scene.export_file_name_o3de)
                # Export file
                self.export_files(file_name)
        else:
            # Remove some nasty invalid char
            file_name = re.sub(r'\W+', '', bpy.context.scene.export_file_name_o3de)
            # Export file
            self.export_files(file_name)
        return{'FINISHED'}

class ProjectsListDropDown(bpy.types.Operator):
    """!
    This Class is for the O3DE Projects UI List Drop Down.
    """
    bl_label = "Project List Dropdown"
    bl_idname = "wm.projectlist"

    def invoke(self, context, event):
        """!
        This function will invoke the blender windowe manager
        """
        window_manager = context.window_manager
        return window_manager.invoke_props_dialog(self)

    def draw(self, context):
        """!
        This function draws this gui element in Blender UI
        """
        layout = self.layout
        layout.prop(context.scene, 'o3de_projects_list')
        
    def execute(self, context):
        """!
        This will update the UI with the current o3de Project Title.
        """
        bpy.types.Scene.selected_o3de_project_path = context.scene.o3de_projects_list
        return {'FINISHED'}

class SceneExporterFileMenu(Operator, ExportHelper):
    """!
    This Class will export the 3d model as well
    as textures in the user selected path.
    """
    bl_idname = "O3DE_FileExport"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_idname = "export_model.mesh_data"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export to O3DE"

    # ExportHelper mixin class uses this
    filename_ext = ".fbx"

    filter_glob: StringProperty(
        default="*.fbx",
        options={'HIDDEN'},
        maxlen=255,  # Max internal buffer length, longer would be clamped.
    )
    # Extra options
    export_textures_folder : BoolProperty(
        name="Export Textures in a textures folder",
        description="Export Textures in textures folder",
        default=True,
    )
    export_mesh_as_triangles : BoolProperty(
        name="Export Mesh as Triangles",
        description="Export Mesh as Triangles",
        #default=bpy.types.WindowManager.mesh_triangle_export_toggle,
    )
    # Add animation to export
    export_animation : BoolProperty(
        name="Keyframe Animation",
        description="Export with Keyframe Animation",
        default=False,
    )

    def execute(self, context):
        """!
        This function will select the Export Texture Option
        """
        #window_manager = context.window_manager
        bpy.types.Scene.export_textures_folder = self.export_textures_folder
        bpy.types.Scene.file_menu_animation_export = self.export_animation
        print(f"We are exporting as Trianges: {self.export_mesh_as_triangles}")
        bpy.types.Scene.convert_mesh_to_triangles = self.export_mesh_as_triangles
        if self.export_animation:
            bpy.types.Scene.animation_export = constants.KEY_FRAME_ANIMATION
            utils.valid_animation_selection()
        fbx_exporter.fbx_file_exporter(self.filepath, Path(self.filepath).stem)
        return{'FINISHED'}

class ExportOptionsListDropDown(bpy.types.Operator):
    """!
    This Class is for the O3DE Export Options UI List Drop Down
    """
    bl_label = "Texture Export Folder"
    bl_idname = "wm.exportoptions"

    def invoke(self, context, event):
        """!
        This function will invoke the blender windowe manager
        """
        window_manager = context.window_manager
        return window_manager.invoke_props_dialog(self)
        
    def draw(self, context):
        """!
        This function draws this gui element in Blender UI
        """
        layout = self.layout
        layout.prop(context.scene, 'texture_options_list')
        
    def execute(self, context):
        """!
        This function will Update Export Option Bool
        """
        if context.scene.texture_options_list == '0':
            bpy.types.Scene.export_textures_folder = True
        elif context.scene.texture_options_list == '1':
            bpy.types.Scene.export_textures_folder = False
        else:
            bpy.types.Scene.export_textures_folder = None
        return {'FINISHED'}

class AnimationOptionsListDropDown(bpy.types.Operator):
    """!
    This Class is for the O3DE Export Animations UI List Drop Down
    """
    bl_label = "Animation Export Options"
    bl_idname = "wm.animationoptions"

    def invoke(self, context, event):
        """!
        This function will invoke the blender windowe manager
        """
        window_manager = context.window_manager
        return window_manager.invoke_props_dialog(self)
        
    def draw(self, context):
        """!
        This function draws this gui element in Blender UI
        """
        layout = self.layout
        layout.prop(context.scene, 'animation_options_list')
        
    def execute(self, context):
        """!
        This function will Update Export Option Bool
        """
        if context.scene.animation_options_list == '0':
            bpy.types.Scene.animation_export = constants.NO_ANIMATION
        elif context.scene.animation_options_list == '1':
            bpy.types.Scene.animation_export = constants.KEY_FRAME_ANIMATION
            utils.valid_animation_selection()
        elif context.scene.animation_options_list == '2':
            bpy.types.Scene.animation_export = constants.MESH_AND_RIG
            utils.valid_animation_selection()
        elif context.scene.animation_options_list == '3':
            bpy.types.Scene.animation_export = constants.SKIN_ATTACHMENT
            utils.valid_animation_selection()
        return {'FINISHED'}

def file_export_menu_add(self, context):
    """!
    This Function will add the Export to O3DE to the file menu Export
    """
    self.layout.operator(SceneExporterFileMenu.bl_idname, text="Export to O3DE")
class O3deTools(Panel):
    """!
    This is the Blender UI Panel O3DE Tools Tab
    """
    bl_idname = "O3DE_TOOLS_PT_Panel"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_label = f'O3DE Tools v{constants.PLUGIN_VERSION}'
    bl_context = 'objectmode'
    bl_category = 'O3DE'

    def draw(self, context):
        """!
        This function draws this gui element in Blender UI. We will look at the Look at the
        o3de engine manifest to see if o3de is currently install and gather the project paths
        in a list drop down.
        """
        layout = self.layout
        selected_objects = context.object
        row = layout.row()
        wm = context.window_manager
        # Look at the o3de Engine Manifest
        o3de_projects, engine_is_installed = o3de_utils.look_at_engine_manifest()
        
        # Validate a selection
        valid_selection, selected_name = utils.check_selected()
        
        # Validate selection bone names if any
        invalid_bone_names, bone_are_in_selected = utils.check_selected_bone_names()

        name_selections = [obj.name for obj in bpy.context.selected_objects]

        if engine_is_installed: # Checks to see if O3DE is installed
            row.operator("vin.wiki", text='O3DE Tools Wiki', icon="WORLD_DATA")
            # Let user choose a custom project path
            local_project_path = layout.row()
            local_project_path.operator("project.open_filebrowser", text="Add Custom Project Path", icon="OUTLINER_OB_GROUP_INSTANCE")
            # Heads up of current selected objects and options
            current_selected_options_row = layout.row()
            current_selected_options_row.label(text="CURRENT SELECTED", icon="OUTLINER_DATA_GP_LAYER")
            # Let user know how many objects are selected
            installed_lable = layout.row()
            
            # Check if there are any selections
            if len(name_selections) == 0: 
                installed_lable.label(text='SELECTED: None')
            else:
                installed_lable.label(text=f'({len(selected_name)}) Selected: {selected_objects.name}')

            # Check to see which Animation Action is active
            action_name, action_count = utils.check_for_animation_actions()
            
            # If more than one object is selected, let user choose export options
            if len(name_selections) > 1:
                multi_file_export_label = "Export Multi-Files" if wm.multi_file_export_toggle else "Export a Single File"
                multi_file_export_button = layout.row()
                multi_file_export_button.prop(wm, "multi_file_export_toggle", text=multi_file_export_label, toggle=True)
                if wm.multi_file_export_toggle:
                    bpy.types.Scene.multi_file_export_o3de = True
                else:
                    bpy.types.Scene.multi_file_export_o3de = False
            else:
                wm.multi_file_export_toggle = False
                bpy.types.Scene.multi_file_export_o3de = False
            
            project_path_lable = layout.row()
            if not bpy.types.Scene.selected_o3de_project_path == '':
                project = Path(bpy.types.Scene.selected_o3de_project_path).name
                project_path_lable.label(text=f'Project: {project}')
            else:
                project_path_lable.label(text='Project: None')
            
            # Let user choose animation export options
            if bone_are_in_selected:
                animation_action_lable = layout.row()
                animation_export_lable = layout.row()
                if bpy.types.Scene.animation_export == constants.NO_ANIMATION:
                    animation_action_lable.label(text=f'Action: ')
                    animation_export_lable.label(text=f'Animation: {bpy.types.Scene.animation_export}')
                else:
                    animation_action_lable.label(text=f'Action: {action_name} ({action_count})')
                    animation_export_lable.label(text=f'Animation: {bpy.types.Scene.animation_export}')
            else:
                bpy.types.Scene.animation_export = constants.NO_ANIMATION

            # This is the UI Export Texture Option Label
            texture_export_option_label = layout.row()
            if bpy.types.Scene.export_textures_folder:
                texture_export_option_label.label(text='Texture Export: Textures Folder')
            elif bpy.types.Scene.export_textures_folder is False:
                texture_export_option_label.label(text='Texture Export: With Model')
            elif bpy.types.Scene.export_textures_folder is None:
                texture_export_option_label.label(text='Texture Export: Off')
            
            # User can add UDP
            user_defined_properties_row = layout.row()
            user_defined_properties_row.label(text="USER DEFINED (UDP)", icon="NODETREE")
            
            # Let user create a O3DE Collider Mesh for Physx
            create_collider_button = layout.row()
            create_collider_button.operator("vin.collider", text='Create PhysX Collider', icon="SNAP_VOLUME")

            # Let user create a O3DE LOD Mesh
            create_lod_button = layout.row()
            create_lod_button.operator("vin.lod", text='Create LOD', icon="MOD_REMESH")

            # User selects projects folder path
            o3de_projects_row = layout.row()
            o3de_projects_row.label(text="PROJECTS", icon="OUTLINER")

            # This is the UI Porjects List
            o3de_projects_panel = layout.row()
            o3de_projects_panel.operator('wm.projectlist', text='O3DE Projects', icon="OUTLINER")
            
            # User selected export options
            o3de_projects_row = layout.row()
            o3de_projects_row.label(text="EXPORT OPTIONS", icon="ZOOM_ALL")

            # This is the UI Texture Export Options List
            texture_export_options_panel = layout.row()
            texture_export_options_panel.operator('wm.exportoptions', text='Texture Export Options', icon="OUTPUT")
            
            # This is the UI Animation Export Options List
            animation_export_options_panel = layout.row()
            animation_export_options_panel.operator('wm.animationoptions', text='Animation Export Options', icon="POSE_HLT")
            
            # This checks to see if we should enable the export button
            export_row = layout.row()
            export_row.label(text="EXPORT FILE", icon="TEXT")
            # Let user choose a custom file name
            file_name_lable = layout.row()
            if not wm.multi_file_export_toggle:
                file_name_lable.label(text='Export File Name')
                file_name_export_input = self.layout.column(align = True)
                file_name_export_input.prop(context.scene, "export_file_name_o3de")
            # Export GUI Rows
            export_files_row = layout.row()
            export_ready_row = layout.row()
            # Enable Rows on and off
            if bpy.types.Scene.selected_o3de_project_path == '':
                export_files_row.enabled = False
                bpy.types.Scene.export_option_gui = False
                export_ready_row.label(text='No Project Selected.')
            elif not utils.check_if_valid_path(bpy.types.Scene.selected_o3de_project_path):
                export_files_row.enabled = False
                bpy.types.Scene.export_option_gui = False
                export_ready_row.label(text='Project Path Not Found.')
            elif not bpy.types.Scene.export_good_o3de:
                export_files_row.enabled = False
                bpy.types.Scene.export_option_gui = False
                export_ready_row.label(text='Not Ready for Export.')
            elif not valid_selection:
                export_files_row.enabled = False
                bpy.types.Scene.export_option_gui = False
                export_ready_row.label(text='Nothing Selected.')
            elif invalid_bone_names == False:
                export_files_row.enabled = False
                bpy.types.Scene.export_option_gui = False
                export_ready_row.label(text='Invalid Char in Bone Names.')
            else:
                export_files_row.enabled = True
                bpy.types.Scene.export_option_gui = True
            # This is the export button
            export_files_row.operator('vin.o3defilexport', text='EXPORT TO O3DE', icon="BLENDER")
            # Export mesh options
            if bpy.types.Scene.export_option_gui:
                export_mesh_triangles_quads_label = "Exporting as Triangles" if wm.mesh_triangle_export_toggle else "Exporting as Quads"
                export_mesh_triangles_quads_button = layout.row()
                export_mesh_triangles_quads_button.prop(wm, "mesh_triangle_export_toggle", text=export_mesh_triangles_quads_label, toggle=True)
                if wm.mesh_triangle_export_toggle:
                    bpy.types.Scene.convert_mesh_to_triangles = True
                else:
                    bpy.types.Scene.convert_mesh_to_triangles = False
        else:
            # If O3DE is not installed we tell the user
            row.operator("vin.wiki", text='O3DE Tools Wiki', icon="WORLD_DATA")
            not_installed = layout.row()
            not_installed.label(text='O3DE Needs to be installed')
            

