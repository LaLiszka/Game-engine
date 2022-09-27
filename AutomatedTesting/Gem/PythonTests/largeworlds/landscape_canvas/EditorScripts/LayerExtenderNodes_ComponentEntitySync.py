"""
Copyright (c) Contributors to the Open 3D Engine Project.
For complete copyright and license terms please see the LICENSE at the root of this distribution.

SPDX-License-Identifier: Apache-2.0 OR MIT
"""


class Tests:
    lc_tool_opened = (
        "Landscape Canvas tool opened",
        "Failed to open Landscape Canvas tool"
    )
    new_graph_created = (
        "Successfully created new graph",
        "Failed to create new graph"
    )
    graph_registered = (
        "Graph registered with Landscape Canvas",
        "Failed to register graph"
    )
    component_added = (
        "Expected component is present on entity",
        "Expected component was not found on entity"
    )
    component_removed = (
        "Expected component was removed from entity",
        "Component is unexpectedly still present on entity"
    )


newEntityId = None


def LayerExtenderNodes_ComponentEntitySync():
    """
    Summary:
    This test verifies that all wrapped nodes can be successfully added to/removed from parent nodes.

    Expected Behavior:
    All wrapped extender nodes can be added to/removed from appropriate parent nodes.

    Test Steps:
     1) Open a simple level
     2) Open Landscape Canvas and create a new graph
     3) Add Area Blender and Layer Spawner nodes to the graph, and add/remove each extender node to/from each

    Note:
    - This test file must be called from the Open 3D Engine Editor command terminal
    - Any passed and failed tests are written to the Editor.log file.
            Parsing the file or running a log_monitor are required to observe the test results.

    :return: None
    """

    import azlmbr.bus as bus
    import azlmbr.editor as editor
    import azlmbr.editor.graph as graph
    import azlmbr.landscapecanvas as landscapecanvas
    import azlmbr.legacy.general as general
    import azlmbr.math as math
    import azlmbr.paths

    import editor_python_test_tools.hydra_editor_utils as hydra
    from editor_python_test_tools.utils import Report

    editorId = azlmbr.globals.property.LANDSCAPE_CANVAS_EDITOR_ID

    def onEntityCreated(parameters):
        global newEntityId
        newEntityId = parameters[0]

    # Open an existing simple level
    hydra.open_base_level()

    # Open Landscape Canvas tool and verify
    general.open_pane('Landscape Canvas')
    Report.critical_result(Tests.lc_tool_opened, general.is_pane_visible('Landscape Canvas'))

    # Create a new graph in Landscape Canvas
    newGraphId = graph.AssetEditorRequestBus(bus.Event, 'CreateNewGraph', editorId)
    Report.critical_result(Tests.new_graph_created, newGraphId is not None)

    # Make sure the graph we created is in Landscape Canvas
    graph_registered = graph.AssetEditorRequestBus(bus.Event, 'ContainsGraph', editorId, newGraphId)
    Report.result(Tests.graph_registered, graph_registered)

    # Listen for entity creation notifications so we can check if the
    # proper components are added when we add nodes
    handler = editor.EditorEntityContextNotificationBusHandler()
    handler.connect()
    handler.add_callback('OnEditorEntityCreated', onEntityCreated)

    # Extender mapping with the key being the node name and the value is the
    # expected Component that should be added to the layer Entity for that wrapped node
    extenders = {
        'AltitudeFilterNode': 'Vegetation Altitude Filter',
        'DistanceBetweenFilterNode': 'Vegetation Distance Between Filter',
        'DistributionFilterNode': 'Vegetation Distribution Filter',
        'ShapeIntersectionFilterNode': 'Vegetation Shape Intersection Filter',
        'SlopeFilterNode': 'Vegetation Slope Filter',
        'SurfaceMaskDepthFilterNode': 'Vegetation Surface Mask Depth Filter',
        'SurfaceMaskFilterNode': 'Vegetation Surface Mask Filter',
        'PositionModifierNode': 'Vegetation Position Modifier',
        'RotationModifierNode': 'Vegetation Rotation Modifier',
        'ScaleModifierNode': 'Vegetation Scale Modifier',
        'SlopeAlignmentModifierNode': 'Vegetation Slope Alignment Modifier',
        'AssetWeightSelectorNode': 'Vegetation Asset Weight Selector'
    }

    # Retrieve a mapping of the TypeIds for all the components
    # we will be checking for
    componentNames = []
    for name in extenders:
        componentNames.append(extenders[name])
    componentTypeIds = hydra.get_component_type_id_map(componentNames)

    areas = [
        'AreaBlenderNode',
        'SpawnerAreaNode'
    ]

    # Add/remove all our supported extender nodes to the Layer Areas and check if the appropriate
    # Components are added/removed to the wrapper node's Entity
    newGraph = graph.GraphManagerRequestBus(bus.Broadcast, 'GetGraph', newGraphId)
    x = 10.0
    y = 10.0
    for areaName in areas:
        nodePosition = math.Vector2(x, y)
        areaNode = landscapecanvas.LandscapeCanvasNodeFactoryRequestBus(bus.Broadcast, 'CreateNodeForTypeName',
                                                                        newGraph, areaName)
        graph.GraphControllerRequestBus(bus.Event, 'AddNode', newGraphId, areaNode, nodePosition)

        success = True
        for extenderName in extenders:
            # Add the wrapped node for the extender
            extenderNode = landscapecanvas.LandscapeCanvasNodeFactoryRequestBus(bus.Broadcast,
                                                                                'CreateNodeForTypeName', newGraph,
                                                                                extenderName)
            graph.GraphControllerRequestBus(bus.Event, 'WrapNode', newGraphId, areaNode, extenderNode)

            # Check that the appropriate Component was added when the extender node was added
            extenderComponent = extenders[extenderName]
            componentTypeId = componentTypeIds[extenderComponent]
            success = success and editor.EditorComponentAPIBus(bus.Broadcast, 'HasComponentOfType', newEntityId,
                                                               componentTypeId)
            Report.info(f"Component: {extenderComponent}")
            Report.result(Tests.component_added, success)
            if not success:
                break

            # Check that the appropriate Component was removed when the extender node was removed
            graph.GraphControllerRequestBus(bus.Event, 'RemoveNode', newGraphId, extenderNode)
            success = success and not editor.EditorComponentAPIBus(bus.Broadcast, 'HasComponentOfType', newEntityId,
                                                                   componentTypeId)
            Report.info(f"Component: {extenderComponent}")
            Report.result(Tests.component_removed, success)
            if not success:
                break

        if success:
            Report.info(f"{areaName} successfully added and removed all filters/modifiers/selectors")

    # Stop listening for entity creation notifications
    handler.disconnect()


if __name__ == "__main__":

    from editor_python_test_tools.utils import Report
    Report.start_test(LayerExtenderNodes_ComponentEntitySync)
