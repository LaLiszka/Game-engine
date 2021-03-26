"""
All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
its licensors.

For complete copyright and license terms please see the LICENSE at the root of this
distribution (the "License"). All use of this software is governed by the License,
or, if provided, by the license below or the license accompanying this file. Do not
remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
"""

# Tests a portion of the Component Property Get/Set Python API while the Editor is running

import azlmbr.bus as bus
import azlmbr.editor as editor
import azlmbr.entity as entity
import azlmbr.math as math
import azlmbr.asset as asset

# Open a level (any level should work)
editor.EditorToolsApplicationRequestBus(bus.Broadcast, 'OpenLevelNoPrompt', 'WaterSample')

def GetSetCompareTest(component, path, assetId):
    # Test Get/Set (get old value, set new value, check that new value was set correctly)
    oldObj = editor.EditorComponentAPIBus(bus.Broadcast, 'GetComponentProperty', component, path)

    if(oldObj.IsSuccess()):
        oldValue = oldObj.GetValue()

    oldValueCompared = editor.EditorComponentAPIBus(bus.Broadcast, 'CompareComponentProperty', component, path, oldValue)

    editor.EditorComponentAPIBus(bus.Broadcast, 'SetComponentProperty', component, path, assetId)
    newObj = editor.EditorComponentAPIBus(bus.Broadcast, 'GetComponentProperty', component, path)

    if(newObj.IsSuccess()):
        newValue = newObj.GetValue()

    newValueCompared = editor.EditorComponentAPIBus(bus.Broadcast, 'CompareComponentProperty', component, path, newValue)
    isOldNewValueSame = editor.EditorComponentAPIBus(bus.Broadcast, 'CompareComponentProperty', component, path, oldValue)

    if not(newValue == oldValue) and oldValueCompared and newValueCompared and not isOldNewValueSame:
        print("GetSetCompare Test " + path + ": SUCCESS")
    else:
        print("GetSetCompare Test " + path + ": FAILURE")

    # Test Clear (set an invalid AssetId, check that the field was cleared correctly)
    editor.EditorComponentAPIBus(bus.Broadcast, 'SetComponentProperty', component, path, asset.AssetId())

    clearObj = editor.EditorComponentAPIBus(bus.Broadcast, 'GetComponentProperty', component, path)

    if(clearObj.IsSuccess()):
        clearValue = clearObj.GetValue()

    clearedValueCompared = editor.EditorComponentAPIBus(bus.Broadcast, 'CompareComponentProperty', component, path, clearValue)
    isNewClearedValueSame = editor.EditorComponentAPIBus(bus.Broadcast, 'CompareComponentProperty', component, path, newValue)

    if (clearValue == asset.AssetId()) and clearedValueCompared and not isNewClearedValueSame:
        print("GetSetCompare Clear " + path + ": SUCCESS")
    else:
        print("GetSetCompare Clear " + path + ": FAILURE")


def PteTest(pte, path, value):
    # Test Get/Set (get old value, set new value, check that new value was set correctly)
    oldObj = pte.get_value(path)

    if(oldObj.IsSuccess()):
        oldValue = oldObj.GetValue()

    oldValueCompared = pte.compare_value(path, oldValue)

    pte.set_value(path, value)

    newObj = pte.get_value(path)

    if(newObj.IsSuccess()):
        newValue = newObj.GetValue()

    newValueCompared = pte.compare_value(path, newValue)
    isOldNewValueSame = pte.compare_value(path, oldValue)

    if not(newValue == oldValue) and oldValueCompared and newValueCompared and not isOldNewValueSame:
        print("PTE Test " + path + ": SUCCESS")
    else:
        print("PTE Test " + path + ": FAILURE")

    # Test Clear (set an invalid AssetId, check that the field was cleared correctly)
    pte.set_value(path, asset.AssetId())

    clearObj = pte.get_value(path)

    if(clearObj.IsSuccess()):
        clearValue = clearObj.GetValue()

    clearedValueCompared = pte.compare_value(path, clearValue)
    isNewClearedValueSame = pte.compare_value(path, newValue)

    if (clearValue == asset.AssetId()) and clearedValueCompared and not isNewClearedValueSame:
        print("PTE Clear " + path + ": SUCCESS")
    else:
        print("PTE Clear " + path + ": FAILURE")

# Create new Entity
entityId = editor.ToolsApplicationRequestBus(bus.Broadcast, 'CreateNewEntity', entity.EntityId())

if (entityId):
    print("New entity with no parent created: SUCCESS")

# Get Component Type for Mesh
typeIdsList = editor.EditorComponentAPIBus(bus.Broadcast, 'FindComponentTypeIdsByEntityType', ["Mesh"], entity.EntityType().Game)

componentOutcome = editor.EditorComponentAPIBus(bus.Broadcast, 'AddComponentsOfType', entityId, typeIdsList)

if (componentOutcome.IsSuccess()):
    print("Mesh component added to entity: SUCCESS")

components = componentOutcome.GetValue()
component = components[0]

hasComponent = editor.EditorComponentAPIBus(bus.Broadcast, 'HasComponentOfType', entityId, typeIdsList[0])

if(hasComponent):
    print("Entity has a Mesh component: SUCCESS")

# Get the PTE from the Mesh Component
pteObj = editor.EditorComponentAPIBus(bus.Broadcast, 'BuildComponentPropertyTreeEditor', component)

if(pteObj.IsSuccess()):
    pte = pteObj.GetValue()

# Tests for the Asset<> case
cubeId = asset.AssetCatalogRequestBus(bus.Broadcast, 'GetAssetIdByPath', 'objects/default/primitive_cube.cgf', math.Uuid(), False)
GetSetCompareTest(component, "MeshComponentRenderNode|Mesh asset", cubeId)
PteTest(pte, "MeshComponentRenderNode|Mesh asset", cubeId)

# Tests for the SimpleAssetReference case
materialId = asset.AssetCatalogRequestBus(bus.Broadcast, 'GetAssetIdByPath', 'engineassets/texturemsg/defaultsolids.mtl', math.Uuid(), False)
GetSetCompareTest(component, "MeshComponentRenderNode|Material override", materialId)
PteTest(pte, "MeshComponentRenderNode|Material override", materialId)

editor.EditorToolsApplicationRequestBus(bus.Broadcast, 'ExitNoPrompt')
