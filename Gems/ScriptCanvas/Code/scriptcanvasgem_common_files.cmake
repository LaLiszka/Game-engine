#
# Copyright (c) Contributors to the Open 3D Engine Project
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    Include/ScriptCanvas/SystemComponent.h
    Source/SystemComponent.cpp
    Source/ScriptCanvasCommonGem.cpp
    Source/PerformanceStatistician.cpp
    Source/PerformanceTracker.cpp
    Include/ScriptCanvas/ScriptCanvasGem.h
    Include/ScriptCanvas/Asset/AssetDescription.h
    Include/ScriptCanvas/Asset/AssetRegistry.cpp
    Include/ScriptCanvas/Asset/AssetRegistry.h
    Include/ScriptCanvas/Asset/AssetRegistryBus.h
    Include/ScriptCanvas/Asset/ExecutionLogAsset.cpp
    Include/ScriptCanvas/Asset/ExecutionLogAsset.h
    Include/ScriptCanvas/Asset/ExecutionLogAssetBus.h
    Include/ScriptCanvas/Asset/RuntimeAsset.cpp
    Include/ScriptCanvas/Asset/RuntimeAsset.h
    Include/ScriptCanvas/Asset/RuntimeAssetHandler.cpp
    Include/ScriptCanvas/Asset/RuntimeAssetHandler.h
    Include/ScriptCanvas/Asset/ScriptCanvasAssetBase.h
    Include/ScriptCanvas/Asset/ScriptCanvasAssetData.h
    Include/ScriptCanvas/Asset/Functions/ScriptCanvasFunctionAsset.h
    Include/ScriptCanvas/Asset/Functions/RuntimeFunctionAssetHandler.cpp
    Include/ScriptCanvas/Asset/Functions/RuntimeFunctionAssetHandler.h
    Include/ScriptCanvas/Core/ScriptCanvasBus.h
    Include/ScriptCanvas/Core/ExecutionNotificationsBus.cpp
    Include/ScriptCanvas/Core/ExecutionNotificationsBus.h
    Include/ScriptCanvas/Core/GraphBus.h
    Include/ScriptCanvas/Core/NodeBus.h
    Include/ScriptCanvas/Core/EBusNodeBus.h
    Include/ScriptCanvas/Core/NodelingBus.h
    Include/ScriptCanvas/Core/SignalBus.h
    Include/ScriptCanvas/Core/ContractBus.h
    Include/ScriptCanvas/Core/Attributes.h
    Include/ScriptCanvas/Core/Connection.cpp
    Include/ScriptCanvas/Core/Connection.h
    Include/ScriptCanvas/Core/ConnectionBus.h
    Include/ScriptCanvas/Core/Contract.cpp
    Include/ScriptCanvas/Core/Contract.h
    Include/ScriptCanvas/Core/Contracts.h
    Include/ScriptCanvas/Core/Contracts/MethodOverloadContract.h
    Include/ScriptCanvas/Core/Contracts/MethodOverloadContract.cpp
    Include/ScriptCanvas/Core/Contracts/RestrictedNodeContract.h
    Include/ScriptCanvas/Core/Contracts/RestrictedNodeContract.cpp
    Include/ScriptCanvas/Core/Core.cpp
    Include/ScriptCanvas/Core/Core.h
    Include/ScriptCanvas/Core/Datum.cpp
    Include/ScriptCanvas/Core/Datum.h
    Include/ScriptCanvas/Core/DatumBus.h
    Include/ScriptCanvas/Core/EBusHandler.h
    Include/ScriptCanvas/Core/EBusHandler.cpp
    Include/ScriptCanvas/Core/Endpoint.cpp
    Include/ScriptCanvas/Core/Endpoint.h
    Include/ScriptCanvas/Core/Graph.cpp
    Include/ScriptCanvas/Core/Graph.h
    Include/ScriptCanvas/Core/GraphData.h
    Include/ScriptCanvas/Core/GraphData.cpp
    Include/ScriptCanvas/Core/GraphScopedTypes.h
    Include/ScriptCanvas/Core/MethodConfiguration.h
    Include/ScriptCanvas/Core/MethodConfiguration.cpp
    Include/ScriptCanvas/Core/ModifiableDatumView.cpp
    Include/ScriptCanvas/Core/ModifiableDatumView.h
    Include/ScriptCanvas/Core/NativeDatumNode.h
    Include/ScriptCanvas/Core/Node.cpp
    Include/ScriptCanvas/Core/Node.h
    Include/ScriptCanvas/Core/Nodeable.cpp
    Include/ScriptCanvas/Core/Nodeable.h
    Include/ScriptCanvas/Core/NodeableNode.cpp
    Include/ScriptCanvas/Core/NodeableNode.h
    Include/ScriptCanvas/Core/NodeableNodeOverloaded.cpp
    Include/ScriptCanvas/Core/NodeableNodeOverloaded.h
    Include/ScriptCanvas/Core/NodeFunctionGeneric.h
    Include/ScriptCanvas/Core/PureData.cpp
    Include/ScriptCanvas/Core/PureData.h
    Include/ScriptCanvas/Core/Slot.cpp
    Include/ScriptCanvas/Core/Slot.h
    Include/ScriptCanvas/Core/SlotConfigurationDefaults.h
    Include/ScriptCanvas/Core/SlotConfigurations.cpp
    Include/ScriptCanvas/Core/SlotConfigurations.h
    Include/ScriptCanvas/Core/SlotExecutionMap.cpp
    Include/ScriptCanvas/Core/SlotExecutionMap.h
    Include/ScriptCanvas/Core/SlotMetadata.cpp
    Include/ScriptCanvas/Core/SlotMetadata.h
    Include/ScriptCanvas/Core/SlotNames.h
    Include/ScriptCanvas/Core/SubgraphInterface.h
    Include/ScriptCanvas/Core/SubgraphInterface.cpp
    Include/ScriptCanvas/Core/SubgraphInterfaceUtility.h
    Include/ScriptCanvas/Core/SubgraphInterfaceUtility.cpp
    Include/ScriptCanvas/Translation/AbstractModelTranslator.h
    Include/ScriptCanvas/Translation/Configuration.h
    Include/ScriptCanvas/Translation/GraphToCPlusPlus.cpp
    Include/ScriptCanvas/Translation/GraphToCPlusPlus.h
    Include/ScriptCanvas/Translation/GraphToLua.h
    Include/ScriptCanvas/Translation/GraphToLua.cpp
    Include/ScriptCanvas/Translation/GraphToLuaUtility.h
    Include/ScriptCanvas/Translation/GraphToLuaUtility.cpp
    Include/ScriptCanvas/Translation/GraphToX.h
    Include/ScriptCanvas/Translation/GraphToX.cpp
    Include/ScriptCanvas/Translation/Translation.h
    Include/ScriptCanvas/Translation/Translation.cpp
    Include/ScriptCanvas/Translation/TranslationContext.h
    Include/ScriptCanvas/Translation/TranslationContext.cpp
    Include/ScriptCanvas/Translation/TranslationContextBus.h
    Include/ScriptCanvas/Translation/TranslationResult.h
    Include/ScriptCanvas/Translation/TranslationResult.cpp
    Include/ScriptCanvas/Translation/TranslationUtilities.h
    Include/ScriptCanvas/Translation/TranslationUtilities.cpp
    Include/ScriptCanvas/PerformanceStatistician.h
    Include/ScriptCanvas/PerformanceStatisticsBus.h
    Include/ScriptCanvas/PerformanceTracker.h
    Include/ScriptCanvas/AutoGen/ScriptCanvas_Macros.jinja
    Include/ScriptCanvas/AutoGen/ScriptCanvas_Nodeable_Macros.jinja
    Include/ScriptCanvas/AutoGen/ScriptCanvasGrammar_Header.jinja
    Include/ScriptCanvas/AutoGen/ScriptCanvasGrammar_Source.jinja
    Include/ScriptCanvas/AutoGen/ScriptCanvasNodeable_Header.jinja
    Include/ScriptCanvas/AutoGen/ScriptCanvasNodeable_Source.jinja
    Include/ScriptCanvas/CodeGen/NodeableCodegen.h
    Include/ScriptCanvas/Core/Contracts/ConnectionLimitContract.cpp
    Include/ScriptCanvas/Core/Contracts/ConnectionLimitContract.h
    Include/ScriptCanvas/Core/Contracts/ContractRTTI.cpp
    Include/ScriptCanvas/Core/Contracts/ContractRTTI.h
    Include/ScriptCanvas/Core/Contracts/DisallowReentrantExecutionContract.cpp
    Include/ScriptCanvas/Core/Contracts/DisallowReentrantExecutionContract.h
    Include/ScriptCanvas/Core/Contracts/DisplayGroupConnectedSlotLimitContract.cpp
    Include/ScriptCanvas/Core/Contracts/DisplayGroupConnectedSlotLimitContract.h
    Include/ScriptCanvas/Core/Contracts/DynamicTypeContract.cpp
    Include/ScriptCanvas/Core/Contracts/DynamicTypeContract.h
    Include/ScriptCanvas/Core/Contracts/ExclusivePureDataContract.cpp
    Include/ScriptCanvas/Core/Contracts/ExclusivePureDataContract.h
    Include/ScriptCanvas/Core/Contracts/IsReferenceTypeContract.cpp
    Include/ScriptCanvas/Core/Contracts/IsReferenceTypeContract.h
    Include/ScriptCanvas/Core/Contracts/MathOperatorContract.cpp
    Include/ScriptCanvas/Core/Contracts/MathOperatorContract.h
    Include/ScriptCanvas/Core/Contracts/SlotTypeContract.cpp
    Include/ScriptCanvas/Core/Contracts/SlotTypeContract.h
    Include/ScriptCanvas/Core/Contracts/SupportsMethodContract.cpp
    Include/ScriptCanvas/Core/Contracts/SupportsMethodContract.h
    Include/ScriptCanvas/Core/Contracts/TypeContract.cpp
    Include/ScriptCanvas/Core/Contracts/TypeContract.h
    Include/ScriptCanvas/Data/BehaviorContextObject.cpp
    Include/ScriptCanvas/Data/BehaviorContextObject.h
    Include/ScriptCanvas/Data/BehaviorContextObjectPtr.cpp
    Include/ScriptCanvas/Data/BehaviorContextObjectPtr.h
    Include/ScriptCanvas/Data/Data.cpp
    Include/ScriptCanvas/Data/Data.h
    Include/ScriptCanvas/Data/DataMacros.h
    Include/ScriptCanvas/Data/DataRegistry.cpp
    Include/ScriptCanvas/Data/DataRegistry.h
    Include/ScriptCanvas/Data/NumericData.h
    Include/ScriptCanvas/Deprecated/VariableDatumBase.h
    Include/ScriptCanvas/Deprecated/VariableDatumBase.cpp
    Include/ScriptCanvas/Deprecated/VariableDatum.h
    Include/ScriptCanvas/Deprecated/VariableDatum.cpp
    Include/ScriptCanvas/Deprecated/VariableHelpers.h
    Include/ScriptCanvas/Deprecated/VariableHelpers.cpp
    Include/ScriptCanvas/Execution/ErrorBus.h
    Include/ScriptCanvas/Execution/ExecutionBus.h
    Include/ScriptCanvas/Execution/ExecutionContext.h
    Include/ScriptCanvas/Execution/ExecutionContext.cpp
    Include/ScriptCanvas/Execution/ExecutionObjectCloning.h
    Include/ScriptCanvas/Execution/ExecutionObjectCloning.cpp
    Include/ScriptCanvas/Execution/ExecutionPerformanceTimer.h
    Include/ScriptCanvas/Execution/ExecutionPerformanceTimer.cpp
    Include/ScriptCanvas/Execution/ExecutionState.h
    Include/ScriptCanvas/Execution/ExecutionState.cpp
    Include/ScriptCanvas/Execution/ExecutionStateDeclarations.h
    Include/ScriptCanvas/Execution/NativeHostDeclarations.h
    Include/ScriptCanvas/Execution/NativeHostDeclarations.cpp
    Include/ScriptCanvas/Execution/NativeHostDefinitions.h
    Include/ScriptCanvas/Execution/NativeHostDefinitions.cpp
    Include/ScriptCanvas/Execution/RuntimeBus.h
    Include/ScriptCanvas/Execution/RuntimeComponent.h
    Include/ScriptCanvas/Execution/RuntimeComponent.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedAPI.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedCloningAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedCloningAPI.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedDebugAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedDebugAPI.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedEBusAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedEBusAPI.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedOut.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedOut.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpreted.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpreted.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedPerActivation.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedPerActivation.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedPure.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedPure.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedSingleton.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedSingleton.cpp
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedUtility.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedUtility.cpp
    Include/ScriptCanvas/Execution/NodeableOut/NodeableOutNative.h
    Include/ScriptCanvas/Grammar/AbstractCodeModel.h
    Include/ScriptCanvas/Grammar/AbstractCodeModel.cpp
    Include/ScriptCanvas/Grammar/DebugMap.h
    Include/ScriptCanvas/Grammar/DebugMap.cpp
    Include/ScriptCanvas/Grammar/ExecutionTraversalListeners.h
    Include/ScriptCanvas/Grammar/ExecutionTraversalListeners.cpp
    Include/ScriptCanvas/Grammar/FunctionsLegacySupport.h
    Include/ScriptCanvas/Grammar/FunctionsLegacySupport.cpp
    Include/ScriptCanvas/Grammar/GrammarContext.h
    Include/ScriptCanvas/Grammar/GrammarContext.cpp
    Include/ScriptCanvas/Grammar/GrammarContextBus.h
    Include/ScriptCanvas/Grammar/ParsingMetaData.h
    Include/ScriptCanvas/Grammar/ParsingMetaData.cpp
    Include/ScriptCanvas/Grammar/ParsingUtilities.h
    Include/ScriptCanvas/Grammar/ParsingUtilities.cpp
    Include/ScriptCanvas/Grammar/Primitives.h
    Include/ScriptCanvas/Grammar/Primitives.cpp
    Include/ScriptCanvas/Grammar/PrimitivesDeclarations.h
    Include/ScriptCanvas/Grammar/PrimitivesDeclarations.cpp
    Include/ScriptCanvas/Grammar/PrimitivesExecution.cpp
    Include/ScriptCanvas/Grammar/PrimitivesExecution.h
    Include/ScriptCanvas/Grammar/SymbolNames.h
    Include/ScriptCanvas/Execution/ErrorBus.h
    Include/ScriptCanvas/Execution/ExecutionContext.cpp
    Include/ScriptCanvas/Execution/ExecutionContext.h
    Include/ScriptCanvas/Execution/ExecutionBus.h
    Include/ScriptCanvas/Execution/NativeHostDeclarations.cpp
    Include/ScriptCanvas/Execution/NativeHostDeclarations.h
    Include/ScriptCanvas/Execution/NativeHostDefinitions.cpp
    Include/ScriptCanvas/Execution/NativeHostDefinitions.h
    Include/ScriptCanvas/Execution/RuntimeBus.h
    Include/ScriptCanvas/Execution/RuntimeComponent.cpp
    Include/ScriptCanvas/Execution/RuntimeComponent.h
    Include/ScriptCanvas/Internal/Nodeables/BaseTimer.cpp
    Include/ScriptCanvas/Internal/Nodeables/BaseTimer.h
    Include/ScriptCanvas/Internal/Nodeables/BaseTimer.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Internal/Nodes/BaseTimerNode.cpp
    Include/ScriptCanvas/Internal/Nodes/BaseTimerNode.h
    Include/ScriptCanvas/Internal/Nodes/BaseTimerNode.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Internal/Nodes/ExpressionNodeBase.cpp
    Include/ScriptCanvas/Internal/Nodes/ExpressionNodeBase.h
    Include/ScriptCanvas/Internal/Nodes/ExpressionNodeBase.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Internal/Nodes/StringFormatted.cpp
    Include/ScriptCanvas/Internal/Nodes/StringFormatted.h
    Include/ScriptCanvas/Internal/Nodes/StringFormatted.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Grammar/AbstractCodeModel.cpp
    Include/ScriptCanvas/Grammar/AbstractCodeModel.h
    Include/ScriptCanvas/Libraries/Libraries.h
    Include/ScriptCanvas/Libraries/Libraries.cpp
    Include/ScriptCanvas/Libraries/Core/AzEventHandler.cpp
    Include/ScriptCanvas/Libraries/Core/AzEventHandler.h
    Include/ScriptCanvas/Libraries/Core/AzEventHandler.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/BehaviorContextObjectNode.cpp
    Include/ScriptCanvas/Libraries/Core/BehaviorContextObjectNode.h
    Include/ScriptCanvas/Libraries/Core/BinaryOperator.cpp
    Include/ScriptCanvas/Libraries/Core/BinaryOperator.h
    Include/ScriptCanvas/Libraries/Core/CoreNodes.cpp
    Include/ScriptCanvas/Libraries/Core/CoreNodes.h
    Include/ScriptCanvas/Libraries/Core/ContainerTypeReflection.h
    Include/ScriptCanvas/Libraries/Core/EBusEventHandler.cpp
    Include/ScriptCanvas/Libraries/Core/EBusEventHandler.h
    Include/ScriptCanvas/Libraries/Core/EBusEventHandler.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/ExtractProperty.cpp
    Include/ScriptCanvas/Libraries/Core/ExtractProperty.h
    Include/ScriptCanvas/Libraries/Core/ExtractProperty.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/EventHandlerTranslationUtility.h
    Include/ScriptCanvas/Libraries/Core/EventHandlerTranslationUtility.cpp
    Include/ScriptCanvas/Libraries/Core/Error.cpp
    Include/ScriptCanvas/Libraries/Core/Error.h
    Include/ScriptCanvas/Libraries/Core/ErrorHandler.cpp
    Include/ScriptCanvas/Libraries/Core/ErrorHandler.h
    Include/ScriptCanvas/Libraries/Core/ForEach.cpp
    Include/ScriptCanvas/Libraries/Core/ForEach.h
    Include/ScriptCanvas/Libraries/Core/ForEach.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/FunctionBus.h
    Include/ScriptCanvas/Libraries/Core/FunctionCallNode.cpp
    Include/ScriptCanvas/Libraries/Core/FunctionCallNode.h
    Include/ScriptCanvas/Libraries/Core/FunctionCallNode.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/FunctionCallNodeIsOutOfDate.h
    Include/ScriptCanvas/Libraries/Core/FunctionCallNodeIsOutOfDate.cpp
    Include/ScriptCanvas/Libraries/Core/FunctionDefinitionNode.cpp
    Include/ScriptCanvas/Libraries/Core/FunctionDefinitionNode.h
    Include/ScriptCanvas/Libraries/Core/FunctionDefinitionNode.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/GetVariable.cpp
    Include/ScriptCanvas/Libraries/Core/GetVariable.h
    Include/ScriptCanvas/Libraries/Core/GetVariable.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/Method.cpp
    Include/ScriptCanvas/Libraries/Core/Method.h
    Include/ScriptCanvas/Libraries/Core/MethodOverloaded.cpp
    Include/ScriptCanvas/Libraries/Core/MethodOverloaded.h
    Include/ScriptCanvas/Libraries/Core/MethodUtility.cpp
    Include/ScriptCanvas/Libraries/Core/MethodUtility.h
    Include/ScriptCanvas/Libraries/Core/Nodeling.cpp
    Include/ScriptCanvas/Libraries/Core/Nodeling.h
    Include/ScriptCanvas/Libraries/Core/Nodeling.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/ReceiveScriptEvent.cpp
    Include/ScriptCanvas/Libraries/Core/ReceiveScriptEvent.h
    Include/ScriptCanvas/Libraries/Core/ReceiveScriptEvent.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/Repeater.cpp
    Include/ScriptCanvas/Libraries/Core/Repeater.h
    Include/ScriptCanvas/Libraries/Core/Repeater.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/RepeaterNodeable.h
    Include/ScriptCanvas/Libraries/Core/RepeaterNodeable.cpp
    Include/ScriptCanvas/Libraries/Core/RepeaterNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Core/ScriptEventBase.cpp
    Include/ScriptCanvas/Libraries/Core/ScriptEventBase.h
    Include/ScriptCanvas/Libraries/Core/ScriptEventBase.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/SendScriptEvent.cpp
    Include/ScriptCanvas/Libraries/Core/SendScriptEvent.h
    Include/ScriptCanvas/Libraries/Core/SendScriptEvent.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/SetVariable.cpp
    Include/ScriptCanvas/Libraries/Core/SetVariable.h
    Include/ScriptCanvas/Libraries/Core/SetVariable.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/Start.cpp
    Include/ScriptCanvas/Libraries/Core/Start.h
    Include/ScriptCanvas/Libraries/Core/Start.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/String.h
    Include/ScriptCanvas/Libraries/Core/UnaryOperator.cpp
    Include/ScriptCanvas/Libraries/Core/UnaryOperator.h
    Include/ScriptCanvas/Libraries/Entity/Entity.cpp
    Include/ScriptCanvas/Libraries/Entity/Entity.h
    Include/ScriptCanvas/Libraries/Entity/EntityIDNode.h
    Include/ScriptCanvas/Libraries/Entity/EntityIDNodes.h
    Include/ScriptCanvas/Libraries/Entity/EntityNodes.h
    Include/ScriptCanvas/Libraries/Entity/EntityRef.h
    Include/ScriptCanvas/Libraries/Entity/Rotate.cpp
    Include/ScriptCanvas/Libraries/Entity/Rotate.h
    Include/ScriptCanvas/Libraries/Entity/Rotate.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Entity/RotateMethod.cpp
    Include/ScriptCanvas/Libraries/Entity/RotateMethod.h
    Include/ScriptCanvas/Libraries/Logic/And.h
    Include/ScriptCanvas/Libraries/Logic/Any.cpp
    Include/ScriptCanvas/Libraries/Logic/Any.h
    Include/ScriptCanvas/Libraries/Logic/Any.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Boolean.h
    Include/ScriptCanvas/Libraries/Logic/Break.h
    Include/ScriptCanvas/Libraries/Logic/Break.cpp
    Include/ScriptCanvas/Libraries/Logic/Break.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Cycle.cpp
    Include/ScriptCanvas/Libraries/Logic/Cycle.h
    Include/ScriptCanvas/Libraries/Logic/Cycle.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Gate.cpp
    Include/ScriptCanvas/Libraries/Logic/Gate.h
    Include/ScriptCanvas/Libraries/Logic/Gate.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Indexer.cpp
    Include/ScriptCanvas/Libraries/Logic/Indexer.h
    Include/ScriptCanvas/Libraries/Logic/Indexer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/IsNull.cpp
    Include/ScriptCanvas/Libraries/Logic/IsNull.h
    Include/ScriptCanvas/Libraries/Logic/IsNull.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Logic.cpp
    Include/ScriptCanvas/Libraries/Logic/Logic.h
    Include/ScriptCanvas/Libraries/Logic/Multiplexer.cpp
    Include/ScriptCanvas/Libraries/Logic/Multiplexer.h
    Include/ScriptCanvas/Libraries/Logic/Multiplexer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Not.h
    Include/ScriptCanvas/Libraries/Logic/Once.cpp
    Include/ScriptCanvas/Libraries/Logic/Once.h
    Include/ScriptCanvas/Libraries/Logic/Once.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Or.h
    Include/ScriptCanvas/Libraries/Logic/OrderedSequencer.cpp
    Include/ScriptCanvas/Libraries/Logic/OrderedSequencer.h
    Include/ScriptCanvas/Libraries/Logic/OrderedSequencer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Sequencer.cpp
    Include/ScriptCanvas/Libraries/Logic/Sequencer.h
    Include/ScriptCanvas/Libraries/Logic/Sequencer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/TargetedSequencer.cpp
    Include/ScriptCanvas/Libraries/Logic/TargetedSequencer.h
    Include/ScriptCanvas/Libraries/Logic/TargetedSequencer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/WeightedRandomSequencer.cpp
    Include/ScriptCanvas/Libraries/Logic/WeightedRandomSequencer.h
    Include/ScriptCanvas/Libraries/Logic/WeightedRandomSequencer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/While.cpp
    Include/ScriptCanvas/Libraries/Logic/While.h
    Include/ScriptCanvas/Libraries/Logic/While.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Math/AABBNode.h
    Include/ScriptCanvas/Libraries/Math/AABBNodes.h
    Include/ScriptCanvas/Libraries/Math/ColorNode.h
    Include/ScriptCanvas/Libraries/Math/ColorNodes.h
    Include/ScriptCanvas/Libraries/Math/CRCNode.h
    Include/ScriptCanvas/Libraries/Math/CRCNodes.h
    Include/ScriptCanvas/Libraries/Math/Divide.h
    Include/ScriptCanvas/Libraries/Math/Math.cpp
    Include/ScriptCanvas/Libraries/Math/Math.h
    Include/ScriptCanvas/Libraries/Math/MathExpression.cpp
    Include/ScriptCanvas/Libraries/Math/MathExpression.h
    Include/ScriptCanvas/Libraries/Math/MathExpression.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Math/MathNodeUtilities.cpp
    Include/ScriptCanvas/Libraries/Math/MathNodeUtilities.h
    Include/ScriptCanvas/Libraries/Math/MathGenerics.h
    Include/ScriptCanvas/Libraries/Math/MathRandom.h
    Include/ScriptCanvas/Libraries/Math/Matrix3x3Node.h
    Include/ScriptCanvas/Libraries/Math/Matrix3x3Nodes.h
    Include/ScriptCanvas/Libraries/Math/Matrix4x4Node.h
    Include/ScriptCanvas/Libraries/Math/Matrix4x4Nodes.h
    Include/ScriptCanvas/Libraries/Math/Multiply.h
    Include/ScriptCanvas/Libraries/Math/Number.h
    Include/ScriptCanvas/Libraries/Math/OBBNode.h
    Include/ScriptCanvas/Libraries/Math/OBBNodes.h
    Include/ScriptCanvas/Libraries/Math/PlaneNode.h
    Include/ScriptCanvas/Libraries/Math/PlaneNodes.h
    Include/ScriptCanvas/Libraries/Math/Random.cpp
    Include/ScriptCanvas/Libraries/Math/Random.h
    Include/ScriptCanvas/Libraries/Math/Random.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Math/Rotation.h
    Include/ScriptCanvas/Libraries/Math/RotationNodes.h
    Include/ScriptCanvas/Libraries/Math/Subtract.h
    Include/ScriptCanvas/Libraries/Math/Sum.h
    Include/ScriptCanvas/Libraries/Math/Transform.h
    Include/ScriptCanvas/Libraries/Math/TransformNodes.h
    Include/ScriptCanvas/Libraries/Math/Vector.h
    Include/ScriptCanvas/Libraries/Math/Vector2Nodes.h
    Include/ScriptCanvas/Libraries/Math/Vector3Nodes.h
    Include/ScriptCanvas/Libraries/Math/Vector4Nodes.h
    Include/ScriptCanvas/Libraries/Comparison/Comparison.h
    Include/ScriptCanvas/Libraries/Comparison/Comparison.cpp
    Include/ScriptCanvas/Libraries/Comparison/ComparisonFunctions.h
    Include/ScriptCanvas/Libraries/Comparison/EqualTo.h
    Include/ScriptCanvas/Libraries/Comparison/NotEqualTo.h
    Include/ScriptCanvas/Libraries/Comparison/Less.h
    Include/ScriptCanvas/Libraries/Comparison/Greater.h
    Include/ScriptCanvas/Libraries/Comparison/LessEqual.h
    Include/ScriptCanvas/Libraries/Comparison/GreaterEqual.h
    Include/ScriptCanvas/Libraries/Time/Time.h
    Include/ScriptCanvas/Libraries/Time/Time.cpp
    Include/ScriptCanvas/Libraries/Time/Countdown.cpp
    Include/ScriptCanvas/Libraries/Time/Countdown.h
    Include/ScriptCanvas/Libraries/Time/Countdown.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Time/DelayNodeable.h
    Include/ScriptCanvas/Libraries/Time/DelayNodeable.cpp
    Include/ScriptCanvas/Libraries/Time/DelayNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Time/Duration.cpp
    Include/ScriptCanvas/Libraries/Time/Duration.h
    Include/ScriptCanvas/Libraries/Time/Duration.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Time/HeartBeat.cpp
    Include/ScriptCanvas/Libraries/Time/HeartBeat.h
    Include/ScriptCanvas/Libraries/Time/HeartBeat.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Time/Timer.cpp
    Include/ScriptCanvas/Libraries/Time/Timer.h
    Include/ScriptCanvas/Libraries/Time/Timer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Time/TimeDelayNodeable.h
    Include/ScriptCanvas/Libraries/Time/TimeDelayNodeable.cpp
    Include/ScriptCanvas/Libraries/Time/TimeDelayNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Time/DurationNodeable.h
    Include/ScriptCanvas/Libraries/Time/DurationNodeable.cpp
    Include/ScriptCanvas/Libraries/Time/DurationNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Time/HeartBeatNodeable.h
    Include/ScriptCanvas/Libraries/Time/HeartBeatNodeable.cpp
    Include/ScriptCanvas/Libraries/Time/HeartBeatNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Time/TimerNodeable.h
    Include/ScriptCanvas/Libraries/Time/TimerNodeable.cpp
    Include/ScriptCanvas/Libraries/Time/TimerNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Spawning/Spawning.cpp
    Include/ScriptCanvas/Libraries/Spawning/Spawning.h
    Include/ScriptCanvas/Libraries/Spawning/SpawnNodeable.cpp
    Include/ScriptCanvas/Libraries/Spawning/SpawnNodeable.h
    Include/ScriptCanvas/Libraries/Spawning/SpawnNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/String/Contains.cpp
    Include/ScriptCanvas/Libraries/String/Contains.h
    Include/ScriptCanvas/Libraries/String/Contains.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/String/Format.cpp
    Include/ScriptCanvas/Libraries/String/Format.h
    Include/ScriptCanvas/Libraries/String/Format.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/String/Print.cpp
    Include/ScriptCanvas/Libraries/String/Print.h
    Include/ScriptCanvas/Libraries/String/Print.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/String/Replace.cpp
    Include/ScriptCanvas/Libraries/String/Replace.h
    Include/ScriptCanvas/Libraries/String/Replace.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/String/String.h
    Include/ScriptCanvas/Libraries/String/String.cpp
    Include/ScriptCanvas/Libraries/String/StringMethods.h
    Include/ScriptCanvas/Libraries/String/StringMethods.cpp
    Include/ScriptCanvas/Libraries/String/StringGenerics.h
    Include/ScriptCanvas/Libraries/String/Utilities.cpp
    Include/ScriptCanvas/Libraries/String/Utilities.h
    Include/ScriptCanvas/Libraries/String/Utilities.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/AddFailure.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/AddFailure.h
    Include/ScriptCanvas/Libraries/UnitTesting/AddFailure.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/AddSuccess.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/AddSuccess.h
    Include/ScriptCanvas/Libraries/UnitTesting/AddSuccess.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/Checkpoint.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/Checkpoint.h
    Include/ScriptCanvas/Libraries/UnitTesting/Checkpoint.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectEqual.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectEqual.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectEqual.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectFalse.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectFalse.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectFalse.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThan.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThan.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThan.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThanEqual.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThanEqual.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThanEqual.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThan.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThan.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThan.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThanEqual.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThanEqual.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThanEqual.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectNotEqual.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectNotEqual.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectNotEqual.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectTrue.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectTrue.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectTrue.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/MarkComplete.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/MarkComplete.h
    Include/ScriptCanvas/Libraries/UnitTesting/MarkComplete.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestBus.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestBusMacros.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTesting.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTesting.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestingLibrary.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestingLibrary.h
    Include/ScriptCanvas/Libraries/UnitTesting/Auxiliary/Auxiliary.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/Auxiliary/Auxiliary.h
    Include/ScriptCanvas/Libraries/UnitTesting/Auxiliary/AuxiliaryGenerics.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestBusSender.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestBusSender.cpp
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestBusSenderMacros.h
    Include/ScriptCanvas/Libraries/Operators/Operators.cpp
    Include/ScriptCanvas/Libraries/Operators/Operators.h
    Include/ScriptCanvas/Libraries/Operators/Operator.cpp
    Include/ScriptCanvas/Libraries/Operators/Operator.h
    Include/ScriptCanvas/Libraries/Operators/Operator.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorAt.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorAt.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorAt.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorBack.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorBack.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorBack.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorClear.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorClear.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorClear.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorEmpty.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorEmpty.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorEmpty.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorErase.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorErase.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorErase.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorFront.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorFront.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorFront.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorInsert.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorInsert.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorInsert.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorPushBack.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorPushBack.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorPushBack.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorSize.cpp
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorSize.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorSize.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorAdd.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorAdd.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorAdd.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorArithmetic.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorArithmetic.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorArithmetic.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDiv.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDiv.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDiv.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDivideByNumber.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDivideByNumber.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDivideByNumber.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLength.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLength.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLength.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerp.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerp.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerp.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorMul.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorMul.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorMul.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorSub.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorSub.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorSub.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerpNodeable.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerpNodeable.cpp
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerpNodeableNode.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerpNodeableNode.cpp
    Include/ScriptCanvas/Profiler/Driller.h
    Include/ScriptCanvas/Profiler/Aggregator.h
    Include/ScriptCanvas/Profiler/Aggregator.cpp
    Include/ScriptCanvas/Profiler/DrillerEvents.h
    Include/ScriptCanvas/Profiler/DrillerEvents.cpp
    Include/ScriptCanvas/Serialization/ScriptUserDataSerializer.h
    Include/ScriptCanvas/Serialization/ScriptUserDataSerializer.cpp
    Include/ScriptCanvas/Data/DataTrait.cpp
    Include/ScriptCanvas/Data/DataTrait.h
    Include/ScriptCanvas/Data/PropertyTraits.cpp
    Include/ScriptCanvas/Data/PropertyTraits.h
    Include/ScriptCanvas/Data/Traits.h
    Include/ScriptCanvas/Variable/VariableBus.h
    Include/ScriptCanvas/Variable/GraphVariable.h
    Include/ScriptCanvas/Variable/GraphVariable.cpp
    Include/ScriptCanvas/Variable/GraphVariableManagerComponent.h
    Include/ScriptCanvas/Variable/GraphVariableManagerComponent.cpp
    Include/ScriptCanvas/Variable/VariableCore.h
    Include/ScriptCanvas/Variable/VariableCore.cpp
    Include/ScriptCanvas/Variable/VariableData.h
    Include/ScriptCanvas/Variable/VariableData.cpp
    Include/ScriptCanvas/Utils/DataUtils.h
    Include/ScriptCanvas/Utils/DataUtils.cpp
    Include/ScriptCanvas/Utils/NodeUtils.h
    Include/ScriptCanvas/Utils/NodeUtils.cpp
    Include/ScriptCanvas/Utils/SerializationUtils.h
    Include/ScriptCanvas/Utils/VersionConverters.h
    Include/ScriptCanvas/Utils/VersionConverters.cpp
    Include/ScriptCanvas/Utils/VersioningUtils.cpp
    Include/ScriptCanvas/Utils/VersioningUtils.cpp
    Include/ScriptCanvas/Utils/BehaviorContextUtils.h
    Include/ScriptCanvas/Utils/BehaviorContextUtils.cpp
)

set(SKIP_UNITY_BUILD_INCLUSION_FILES
    Include/ScriptCanvas/Libraries/Core/FunctionCallNode.cpp
    Include/ScriptCanvas/Libraries/Core/FunctionCallNode.h
    Include/ScriptCanvas/Libraries/Core/FunctionCallNodeIsOutOfDate.h
    Include/ScriptCanvas/Libraries/Core/FunctionCallNodeIsOutOfDate.cpp
)
