#
# Copyright (c) Contributors to the Open 3D Engine Project
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    include/LmbrCentral/Rendering/EditorCameraCorrectionBus.h
    include/LmbrCentral/Rendering/EditorLightComponentBus.h
    include/LmbrCentral/Shape/EditorPolygonPrismShapeComponentBus.h
    include/LmbrCentral/Shape/EditorSplineComponentBus.h
    include/LmbrCentral/Shape/EditorTubeShapeComponentBus.h
    include/LmbrCentral/Component/EditorWrappedComponentBase.h
    include/LmbrCentral/Component/EditorWrappedComponentBase.inl
    Source/Audio/EditorAudioAreaEnvironmentComponent.h
    Source/Audio/EditorAudioAreaEnvironmentComponent.cpp
    Source/Audio/EditorAudioEnvironmentComponent.h
    Source/Audio/EditorAudioEnvironmentComponent.cpp
    Source/Audio/EditorAudioListenerComponent.h
    Source/Audio/EditorAudioListenerComponent.cpp
    Source/Audio/EditorAudioMultiPositionComponent.h
    Source/Audio/EditorAudioMultiPositionComponent.cpp
    Source/Audio/EditorAudioPreloadComponent.h
    Source/Audio/EditorAudioPreloadComponent.cpp
    Source/Audio/EditorAudioRtpcComponent.h
    Source/Audio/EditorAudioRtpcComponent.cpp
    Source/Audio/EditorAudioSwitchComponent.h
    Source/Audio/EditorAudioSwitchComponent.cpp
    Source/Audio/EditorAudioTriggerComponent.h
    Source/Audio/EditorAudioTriggerComponent.cpp
    Source/Builders/BenchmarkAssetBuilder/BenchmarkAssetBuilderComponent.h
    Source/Builders/BenchmarkAssetBuilder/BenchmarkAssetBuilderComponent.cpp
    Source/Builders/BenchmarkAssetBuilder/BenchmarkAssetBuilderWorker.h
    Source/Builders/BenchmarkAssetBuilder/BenchmarkAssetBuilderWorker.cpp
    Source/Scripting/EditorLookAtComponent.h
    Source/Scripting/EditorLookAtComponent.cpp
    Source/Scripting/EditorRandomTimedSpawnerComponent.cpp
    Source/Scripting/EditorRandomTimedSpawnerComponent.h
    Source/Scripting/EditorSpawnerComponent.h
    Source/Scripting/EditorSpawnerComponent.cpp
    Source/Scripting/EditorTagComponent.h
    Source/Scripting/EditorTagComponent.cpp
    Source/Shape/EditorBaseShapeComponent.h
    Source/Shape/EditorBaseShapeComponent.cpp
    Source/Shape/EditorSphereShapeComponent.h
    Source/Shape/EditorSphereShapeComponent.cpp
    Source/Shape/EditorDiskShapeComponent.h
    Source/Shape/EditorDiskShapeComponent.cpp
    Source/Shape/EditorBoxShapeComponent.h
    Source/Shape/EditorBoxShapeComponent.cpp
    Source/Shape/EditorCylinderShapeComponent.h
    Source/Shape/EditorCylinderShapeComponent.cpp
    Source/Shape/EditorCapsuleShapeComponent.h
    Source/Shape/EditorCapsuleShapeComponent.cpp
    Source/Shape/EditorCompoundShapeComponent.h
    Source/Shape/EditorCompoundShapeComponent.cpp
    Source/Shape/EditorQuadShapeComponent.h
    Source/Shape/EditorQuadShapeComponent.cpp
    Source/Shape/EditorSplineComponent.h
    Source/Shape/EditorSplineComponent.cpp
    Source/Shape/EditorSplineComponentMode.h
    Source/Shape/EditorSplineComponentMode.cpp
    Source/Shape/EditorTubeShapeComponent.h
    Source/Shape/EditorTubeShapeComponent.cpp
    Source/Shape/EditorTubeShapeComponentMode.h
    Source/Shape/EditorTubeShapeComponentMode.cpp
    Source/Shape/EditorPolygonPrismShapeComponent.h
    Source/Shape/EditorPolygonPrismShapeComponent.cpp
    Source/Shape/EditorPolygonPrismShapeComponentMode.h
    Source/Shape/EditorPolygonPrismShapeComponentMode.cpp
    Source/Shape/EditorShapeComponentConverters.h
    Source/Shape/EditorShapeComponentConverters.cpp
    Source/Ai/EditorNavigationSeedComponent.h
    Source/Ai/EditorNavigationSeedComponent.cpp
    Source/Ai/EditorNavigationAreaComponent.h
    Source/Ai/EditorNavigationAreaComponent.cpp
    Source/Ai/EditorNavigationUtil.h
    Source/Ai/EditorNavigationUtil.cpp
    Source/Editor/EditorCommentComponent.h
    Source/Editor/EditorCommentComponent.cpp
    Source/Ai/NavigationComponent.h
    Source/Ai/NavigationComponent.cpp
    Source/Scripting/SpawnerComponent.h
    Source/Scripting/SpawnerComponent.cpp
    Source/Shape/TubeShape.h
    Source/Shape/TubeShape.cpp
    Source/Builders/CopyDependencyBuilder/CopyDependencyBuilderComponent.cpp
    Source/Builders/CopyDependencyBuilder/CopyDependencyBuilderComponent.h
    Source/Builders/CopyDependencyBuilder/CopyDependencyBuilderWorker.cpp
    Source/Builders/CopyDependencyBuilder/CopyDependencyBuilderWorker.h
    Source/Builders/CopyDependencyBuilder/CfgBuilderWorker/CfgBuilderWorker.cpp
    Source/Builders/CopyDependencyBuilder/CfgBuilderWorker/CfgBuilderWorker.h
    Source/Builders/CopyDependencyBuilder/EmfxWorkspaceBuilderWorker/EmfxWorkspaceBuilderWorker.cpp
    Source/Builders/CopyDependencyBuilder/EmfxWorkspaceBuilderWorker/EmfxWorkspaceBuilderWorker.h
    Source/Builders/CopyDependencyBuilder/FontBuilderWorker/FontBuilderWorker.cpp
    Source/Builders/CopyDependencyBuilder/FontBuilderWorker/FontBuilderWorker.h
    Source/Builders/CopyDependencyBuilder/SchemaBuilderWorker/SchemaBuilderWorker.cpp
    Source/Builders/CopyDependencyBuilder/SchemaBuilderWorker/SchemaBuilderWorker.h
    Source/Builders/CopyDependencyBuilder/SchemaBuilderWorker/SchemaUtils.cpp
    Source/Builders/CopyDependencyBuilder/SchemaBuilderWorker/SchemaUtils.h
    Source/Builders/CopyDependencyBuilder/XmlBuilderWorker/XmlBuilderWorker.cpp
    Source/Builders/CopyDependencyBuilder/XmlBuilderWorker/XmlBuilderWorker.h
    Source/Builders/CopyDependencyBuilder/XmlFormattedAssetBuilderWorker.cpp
    Source/Builders/CopyDependencyBuilder/XmlFormattedAssetBuilderWorker.h
    Source/Builders/DependencyBuilder/DependencyBuilderComponent.cpp
    Source/Builders/DependencyBuilder/DependencyBuilderComponent.h
    Source/Builders/DependencyBuilder/DependencyBuilderWorker.cpp
    Source/Builders/DependencyBuilder/DependencyBuilderWorker.h
    Source/Builders/DependencyBuilder/SeedBuilderWorker/SeedBuilderWorker.cpp
    Source/Builders/DependencyBuilder/SeedBuilderWorker/SeedBuilderWorker.h
    Source/Builders/LevelBuilder/LevelBuilderComponent.cpp
    Source/Builders/LevelBuilder/LevelBuilderComponent.h
    Source/Builders/LevelBuilder/LevelBuilderWorker.cpp
    Source/Builders/LevelBuilder/LevelBuilderWorker.h
    Source/Builders/MaterialBuilder/MaterialBuilderComponent.cpp
    Source/Builders/MaterialBuilder/MaterialBuilderComponent.h
    Source/Builders/SliceBuilder/SliceBuilderComponent.cpp
    Source/Builders/SliceBuilder/SliceBuilderComponent.h
    Source/Builders/SliceBuilder/SliceBuilderWorker.cpp
    Source/Builders/SliceBuilder/SliceBuilderWorker.h
    Source/Builders/TranslationBuilder/TranslationBuilderComponent.cpp
    Source/Builders/TranslationBuilder/TranslationBuilderComponent.h
    Source/Builders/LuaBuilder/LuaBuilderComponent.h
    Source/Builders/LuaBuilder/LuaBuilderComponent.cpp
    Source/Builders/LuaBuilder/LuaBuilderWorker.cpp
    Source/Builders/LuaBuilder/LuaBuilderWorker.h
    Source/Builders/LuaBuilder/LuaHelpers.cpp
    Source/Builders/LuaBuilder/LuaHelpers.h

)
