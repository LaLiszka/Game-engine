#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    Include/AtomLyIntegration/CommonFeatures/Material/EditorMaterialSystemComponentNotificationBus.h
    Include/AtomLyIntegration/CommonFeatures/Material/EditorMaterialSystemComponentRequestBus.h
    Include/AtomLyIntegration/CommonFeatures/ReflectionProbe/EditorReflectionProbeBus.h
    Source/Module.cpp
    Source/Animation/EditorAttachmentComponent.h
    Source/Animation/EditorAttachmentComponent.cpp
    Source/EditorCommonFeaturesSystemComponent.h
    Source/EditorCommonFeaturesSystemComponent.cpp
    Source/CoreLights/EditorAreaLightComponent.h
    Source/CoreLights/EditorAreaLightComponent.cpp
    Source/CoreLights/EditorDirectionalLightComponent.h
    Source/CoreLights/EditorDirectionalLightComponent.cpp
    Source/Decals/EditorDecalComponent.h
    Source/Decals/EditorDecalComponent.cpp
    Source/DiffuseGlobalIllumination/EditorDiffuseProbeGridComponent.h
    Source/DiffuseGlobalIllumination/EditorDiffuseProbeGridComponent.cpp
    Source/DiffuseGlobalIllumination/EditorDiffuseGlobalIlluminationComponent.h
    Source/DiffuseGlobalIllumination/EditorDiffuseGlobalIlluminationComponent.cpp
    Source/Grid/EditorGridComponent.h
    Source/Grid/EditorGridComponent.cpp
    Source/ImageBasedLights/EditorImageBasedLightComponent.h
    Source/ImageBasedLights/EditorImageBasedLightComponent.cpp
    Source/Material/EditorMaterialComponent.cpp
    Source/Material/EditorMaterialComponent.h
    Source/Material/EditorMaterialComponentUtil.cpp
    Source/Material/EditorMaterialComponentUtil.h
    Source/Material/EditorMaterialComponentSlot.cpp
    Source/Material/EditorMaterialComponentSlot.h
    Source/Material/EditorMaterialComponentExporter.cpp
    Source/Material/EditorMaterialComponentExporter.h
    Source/Material/EditorMaterialComponentInspector.cpp
    Source/Material/EditorMaterialComponentInspector.h
    Source/Material/EditorMaterialModelUvNameMapInspector.cpp
    Source/Material/EditorMaterialModelUvNameMapInspector.h
    Source/Material/EditorMaterialSystemComponent.cpp
    Source/Material/EditorMaterialSystemComponent.h
    Source/Material/MaterialBrowserInteractions.h
    Source/Material/MaterialBrowserInteractions.cpp
    Source/Mesh/EditorMeshComponent.h
    Source/Mesh/EditorMeshComponent.cpp
    Source/Mesh/EditorMeshStats.h
    Source/Mesh/EditorMeshStats.cpp
    Source/Mesh/EditorMeshSystemComponent.cpp
    Source/Mesh/EditorMeshSystemComponent.h
    Source/Mesh/EditorMeshStatsSerializer.cpp
    Source/Mesh/EditorMeshStatsSerializer.h
    Source/OcclusionCullingPlane/EditorOcclusionCullingPlaneComponent.h
    Source/OcclusionCullingPlane/EditorOcclusionCullingPlaneComponent.cpp
    Source/PostProcess/EditorPostFxLayerComponent.cpp
    Source/PostProcess/EditorPostFxLayerComponent.h
    Source/PostProcess/Bloom/EditorBloomComponent.cpp
    Source/PostProcess/Bloom/EditorBloomComponent.h
    Source/PostProcess/ColorGrading/EditorHDRColorGradingComponent.cpp
    Source/PostProcess/ColorGrading/EditorHDRColorGradingComponent.h
    Source/PostProcess/EditorModeFeedback/EditorEditorModeFeedbackComponent.cpp
    Source/PostProcess/EditorModeFeedback/EditorEditorModeFeedbackComponent.h
    Source/PostProcess/DepthOfField/EditorDepthOfFieldComponent.cpp
    Source/PostProcess/DepthOfField/EditorDepthOfFieldComponent.h
    Source/PostProcess/DisplayMapper/EditorDisplayMapperComponent.cpp
    Source/PostProcess/DisplayMapper/EditorDisplayMapperComponent.h
    Source/PostProcess/ExposureControl/EditorExposureControlComponent.cpp
    Source/PostProcess/ExposureControl/EditorExposureControlComponent.h
    Source/PostProcess/Ssao/EditorSsaoComponent.cpp
    Source/PostProcess/Ssao/EditorSsaoComponent.h
    Source/PostProcess/LookModification/EditorLookModificationComponent.cpp
    Source/PostProcess/LookModification/EditorLookModificationComponent.h
    Source/PostProcess/RadiusWeightModifier/EditorRadiusWeightModifierComponent.cpp
    Source/PostProcess/RadiusWeightModifier/EditorRadiusWeightModifierComponent.h
    Source/PostProcess/ShapeWeightModifier/EditorShapeWeightModifierComponent.cpp
    Source/PostProcess/GradientWeightModifier/EditorGradientWeightModifierComponent.h
    Source/PostProcess/GradientWeightModifier/EditorGradientWeightModifierComponent.cpp
    Source/PostProcess/ShapeWeightModifier/EditorShapeWeightModifierComponent.h
    Source/PostProcess/EditorPostFxLayerCategoriesAsset.h
    Source/PostProcess/EditorPostFxLayerCategoriesAsset.cpp
    Source/PostProcess/EditorPostFxSystemComponent.h
    Source/PostProcess/EditorPostFxSystemComponent.cpp
    Source/ScreenSpace/EditorDeferredFogComponent.h
    Source/ScreenSpace/EditorDeferredFogComponent.cpp
    Source/ReflectionProbe/EditorReflectionProbeComponent.h
    Source/ReflectionProbe/EditorReflectionProbeComponent.cpp
    Source/SkinnedMesh/SkinnedMeshDebugDisplay.h
    Source/SkinnedMesh/SkinnedMeshDebugDisplay.cpp
    Source/SkyBox/EditorHDRiSkyboxComponent.cpp
    Source/SkyBox/EditorHDRiSkyboxComponent.h
    Source/SkyBox/EditorPhysicalSkyComponent.cpp
    Source/SkyBox/EditorPhysicalSkyComponent.h
    Source/SharedPreview/SharedPreviewer.cpp
    Source/SharedPreview/SharedPreviewer.h
    Source/SharedPreview/SharedPreviewer.ui
    Source/SharedPreview/SharedPreviewerFactory.cpp
    Source/SharedPreview/SharedPreviewerFactory.h
    Source/SharedPreview/SharedPreviewContent.cpp
    Source/SharedPreview/SharedPreviewContent.h
    Source/SharedPreview/SharedPreviewUtils.cpp
    Source/SharedPreview/SharedPreviewUtils.h
    Source/SharedPreview/SharedThumbnail.cpp
    Source/SharedPreview/SharedThumbnail.h
    Source/SharedPreview/SharedThumbnailRenderer.cpp
    Source/SharedPreview/SharedThumbnailRenderer.h
    Source/Scripting/EditorEntityReferenceComponent.cpp
    Source/Scripting/EditorEntityReferenceComponent.h
    Source/SurfaceData/EditorSurfaceDataMeshComponent.cpp
    Source/SurfaceData/EditorSurfaceDataMeshComponent.h
    Resources/AtomLyIntegrationResources.qrc
)
