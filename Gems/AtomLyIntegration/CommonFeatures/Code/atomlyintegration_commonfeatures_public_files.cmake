#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    Include/AtomLyIntegration/CommonFeatures/CoreLights/AreaLightBus.h
    Include/AtomLyIntegration/CommonFeatures/CoreLights/AreaLightComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/CoreLights/CoreLightsConstants.h
    Include/AtomLyIntegration/CommonFeatures/CoreLights/DirectionalLightBus.h
    Include/AtomLyIntegration/CommonFeatures/CoreLights/DirectionalLightComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/Decals/DecalBus.h
    Include/AtomLyIntegration/CommonFeatures/Decals/DecalComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/Decals/DecalConstants.h
    Include/AtomLyIntegration/CommonFeatures/Grid/GridComponentBus.h
    Include/AtomLyIntegration/CommonFeatures/Grid/GridComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/Grid/GridComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/ImageBasedLights/ImageBasedLightComponentBus.h
    Include/AtomLyIntegration/CommonFeatures/ImageBasedLights/ImageBasedLightComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/ImageBasedLights/ImageBasedLightComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/Material/MaterialComponentBus.h
    Include/AtomLyIntegration/CommonFeatures/Material/MaterialComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/Material/MaterialComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/Mesh/MeshComponentBus.h
    Include/AtomLyIntegration/CommonFeatures/Mesh/MeshComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/PostFxLayerBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/PostFxLayerComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/PostFxLayerComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/Bloom/BloomBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/Bloom/BloomComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/DepthOfField/DepthOfFieldBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/DepthOfField/DepthOfFieldComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/DisplayMapper/DisplayMapperComponentBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/DisplayMapper/DisplayMapperComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/DisplayMapper/DisplayMapperComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/ExposureControl/ExposureControlBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/ExposureControl/ExposureControlComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/ExposureControl/ExposureControlComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/ColorGrading/HDRColorGradingBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/ColorGrading/HDRColorGradingComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/EditorModeFeedback/EditorModeFeedbackBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/Ssao/SsaoBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/Ssao/SsaoComponentConfiguration.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/LookModification/LookModificationBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/LookModification/LookModificationComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/LookModification/LookModificationComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/PostFxWeightRequestBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/PostFxLayerCategoriesProviderRequestBus.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/RadiusWeightModifier/RadiusWeightModifierComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/RadiusWeightModifier/RadiusWeightModifierComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/ShapeWeightModifier/ShapeWeightModifierComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/ShapeWeightModifier/ShapeWeightModifierComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/GradientWeightModifier/GradientWeightModifierComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/PostProcess/GradientWeightModifier/GradientWeightModifierComponentConstants.h
    Include/AtomLyIntegration/CommonFeatures/ScreenSpace/DeferredFogComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/ScreenSpace/DeferredFogBus.h
    Include/AtomLyIntegration/CommonFeatures/SkyBox/HDRiSkyboxBus.h
    Include/AtomLyIntegration/CommonFeatures/SkyBox/HDRiSkyboxComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/SkyBox/PhysicalSkyBus.h
    Include/AtomLyIntegration/CommonFeatures/SkyBox/PhysicalSkyComponentConfig.h
    Include/AtomLyIntegration/CommonFeatures/Scripting/EntityReferenceRequestBus.h
    Include/AtomLyIntegration/CommonFeatures/Scripting/EntityReferenceConstants.h
    Include/AtomLyIntegration/CommonFeatures/Scripting/EntityReferenceComponentConfig.h
)
