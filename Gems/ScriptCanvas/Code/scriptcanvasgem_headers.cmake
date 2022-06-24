#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    Include/ScriptCanvas/SystemComponent.h
    Include/ScriptCanvas/ScriptCanvasGem.h
    Include/ScriptCanvas/Asset/AssetDescription.h
    Include/ScriptCanvas/Asset/AssetRegistry.h
    Include/ScriptCanvas/Asset/AssetRegistryBus.h
    Include/ScriptCanvas/Asset/ExecutionLogAsset.h
    Include/ScriptCanvas/Asset/ExecutionLogAssetBus.h
    Include/ScriptCanvas/Asset/RuntimeAsset.h
    Include/ScriptCanvas/Asset/RuntimeAssetHandler.h
    Include/ScriptCanvas/Asset/SubgraphInterfaceAssetHandler.h
    Include/ScriptCanvas/Core/ScriptCanvasBus.h
    Include/ScriptCanvas/Core/ExecutionNotificationsBus.h
    Include/ScriptCanvas/Core/GraphBus.h
    Include/ScriptCanvas/Core/NodeBus.h
    Include/ScriptCanvas/Core/EBusNodeBus.h
    Include/ScriptCanvas/Core/NodelingBus.h
    Include/ScriptCanvas/Core/Attributes.h
    Include/ScriptCanvas/Core/Connection.h
    Include/ScriptCanvas/Core/ConnectionBus.h
    Include/ScriptCanvas/Core/Contract.h
    Include/ScriptCanvas/Core/Contracts.h
    Include/ScriptCanvas/Core/Contracts/MethodOverloadContract.h
    Include/ScriptCanvas/Core/Contracts/RestrictedNodeContract.h
    Include/ScriptCanvas/Core/Core.h
    Include/ScriptCanvas/Core/Datum.h
    Include/ScriptCanvas/Core/DatumBus.h
    Include/ScriptCanvas/Core/EBusHandler.h
    Include/ScriptCanvas/Core/Endpoint.h
    Include/ScriptCanvas/Core/Graph.h
    Include/ScriptCanvas/Core/GraphData.h
    Include/ScriptCanvas/Core/GraphSerialization.h
    Include/ScriptCanvas/Core/GraphScopedTypes.h
    Include/ScriptCanvas/Core/MethodConfiguration.h
    Include/ScriptCanvas/Core/ModifiableDatumView.h
    Include/ScriptCanvas/Core/Node.h
    Include/ScriptCanvas/Core/Nodeable.h
    Include/ScriptCanvas/Core/NodeableNode.h
    Include/ScriptCanvas/Core/NodeableNodeOverloaded.h
    Include/ScriptCanvas/Core/NodeableOut.h
    Include/ScriptCanvas/Core/NodeFunctionGeneric.h
    Include/ScriptCanvas/Core/SerializationListener.h
    Include/ScriptCanvas/Core/Slot.h
    Include/ScriptCanvas/Core/SlotConfigurationDefaults.h
    Include/ScriptCanvas/Core/SlotConfigurations.h
    Include/ScriptCanvas/Core/SlotExecutionMap.h
    Include/ScriptCanvas/Core/SlotMetadata.h
    Include/ScriptCanvas/Core/SlotNames.h
    Include/ScriptCanvas/Core/SubgraphInterface.h
    Include/ScriptCanvas/Core/SubgraphInterfaceUtility.h
    Include/ScriptCanvas/Translation/Configuration.h
    Include/ScriptCanvas/Translation/GraphToLua.h
    Include/ScriptCanvas/Translation/GraphToLuaUtility.h
    Include/ScriptCanvas/Translation/GraphToX.h
    Include/ScriptCanvas/Translation/Translation.h
    Include/ScriptCanvas/Translation/TranslationContext.h
    Include/ScriptCanvas/Translation/TranslationResult.h
    Include/ScriptCanvas/Translation/TranslationUtilities.h
    Include/ScriptCanvas/PerformanceStatistician.h
    Include/ScriptCanvas/PerformanceStatisticsBus.h
    Include/ScriptCanvas/PerformanceTracker.h
    Include/ScriptCanvas/CodeGen/NodeableCodegen.h
    Include/ScriptCanvas/Core/Contracts/ConnectionLimitContract.h
    Include/ScriptCanvas/Core/Contracts/ContractRTTI.h
    Include/ScriptCanvas/Core/Contracts/DisallowReentrantExecutionContract.h
    Include/ScriptCanvas/Core/Contracts/DisplayGroupConnectedSlotLimitContract.h
    Include/ScriptCanvas/Core/Contracts/DynamicTypeContract.h
    Include/ScriptCanvas/Core/Contracts/IsReferenceTypeContract.h
    Include/ScriptCanvas/Core/Contracts/MathOperatorContract.h
    Include/ScriptCanvas/Core/Contracts/SlotTypeContract.h
    Include/ScriptCanvas/Core/Contracts/SupportsMethodContract.h
    Include/ScriptCanvas/Core/Contracts/TypeContract.h
    Include/ScriptCanvas/Data/BehaviorContextObject.h
    Include/ScriptCanvas/Data/BehaviorContextObjectPtr.h
    Include/ScriptCanvas/Data/Data.h
    Include/ScriptCanvas/Data/DataMacros.h
    Include/ScriptCanvas/Data/DataRegistry.h
    Include/ScriptCanvas/Data/NumericData.h
    Include/ScriptCanvas/Deprecated/VariableDatumBase.h
    Include/ScriptCanvas/Deprecated/VariableDatum.h
    Include/ScriptCanvas/Deprecated/VariableHelpers.h
    Include/ScriptCanvas/Execution/ErrorBus.h
    Include/ScriptCanvas/Execution/Executor.h
    Include/ScriptCanvas/Execution/ExecutionBus.h
    Include/ScriptCanvas/Execution/ExecutionContext.h
    Include/ScriptCanvas/Execution/ExecutionObjectCloning.h
    Include/ScriptCanvas/Execution/ExecutionPerformanceTimer.h
    Include/ScriptCanvas/Execution/ExecutionState.h
    Include/ScriptCanvas/Execution/ExecutionStateDeclarations.h
    Include/ScriptCanvas/Execution/ExecutionStateHandler.h
    Include/ScriptCanvas/Execution/ExecutionStateStorage.h
    Include/ScriptCanvas/Execution/RuntimeComponent.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedClassAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedCloningAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedComponentAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedDebugAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedEBusAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionInterpretedOut.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpreted.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedAPI.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedPerActivation.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedPure.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedSingleton.h
    Include/ScriptCanvas/Execution/Interpreted/ExecutionStateInterpretedUtility.h
    Include/ScriptCanvas/Grammar/AbstractCodeModel.h
    Include/ScriptCanvas/Grammar/DebugMap.h
    Include/ScriptCanvas/Grammar/ExecutionTraversalListeners.h
    Include/ScriptCanvas/Grammar/ParsingMetaData.h
    Include/ScriptCanvas/Grammar/ParsingUtilities.h
    Include/ScriptCanvas/Grammar/ParsingUtilitiesScriptEventExtension.h
    Include/ScriptCanvas/Grammar/Primitives.h
    Include/ScriptCanvas/Grammar/PrimitivesDeclarations.h
    Include/ScriptCanvas/Grammar/PrimitivesExecution.h
    Include/ScriptCanvas/Grammar/SymbolNames.h
    Include/ScriptCanvas/Execution/ErrorBus.h
    Include/ScriptCanvas/Execution/ExecutionContext.h
    Include/ScriptCanvas/Execution/ExecutionBus.h
    Include/ScriptCanvas/Execution/RuntimeComponent.h
    Include/ScriptCanvas/Internal/Nodeables/BaseTimer.h
    Include/ScriptCanvas/Internal/Nodeables/BaseTimer.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Internal/Nodes/BaseTimerNode.h
    Include/ScriptCanvas/Internal/Nodes/BaseTimerNode.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Internal/Nodes/ExpressionNodeBase.h
    Include/ScriptCanvas/Internal/Nodes/ExpressionNodeBase.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Internal/Nodes/StringFormatted.h
    Include/ScriptCanvas/Internal/Nodes/StringFormatted.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Grammar/AbstractCodeModel.h
    Include/ScriptCanvas/Libraries/Libraries.h
    Include/ScriptCanvas/Libraries/Core/AzEventHandler.h
    Include/ScriptCanvas/Libraries/Core/AzEventHandler.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/BinaryOperator.h
    Include/ScriptCanvas/Libraries/Core/CoreNodes.h
    Include/ScriptCanvas/Libraries/Core/ContainerTypeReflection.h
    Include/ScriptCanvas/Libraries/Core/EBusEventHandler.h
    Include/ScriptCanvas/Libraries/Core/EBusEventHandler.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/ExtractProperty.h
    Include/ScriptCanvas/Libraries/Core/ExtractProperty.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/EventHandlerTranslationUtility.h
    Include/ScriptCanvas/Libraries/Core/ForEach.h
    Include/ScriptCanvas/Libraries/Core/ForEach.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/FunctionCallNode.h
    Include/ScriptCanvas/Libraries/Core/FunctionCallNode.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/FunctionCallNodeIsOutOfDate.h
    Include/ScriptCanvas/Libraries/Core/FunctionDefinitionNode.h
    Include/ScriptCanvas/Libraries/Core/FunctionDefinitionNode.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/GetVariable.h
    Include/ScriptCanvas/Libraries/Core/GetVariable.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/Method.h
    Include/ScriptCanvas/Libraries/Core/MethodOverloaded.h
    Include/ScriptCanvas/Libraries/Core/Nodeling.h
    Include/ScriptCanvas/Libraries/Core/Nodeling.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/ReceiveScriptEvent.h
    Include/ScriptCanvas/Libraries/Core/ReceiveScriptEvent.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/Repeater.h
    Include/ScriptCanvas/Libraries/Core/Repeater.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/RepeaterNodeable.h
    Include/ScriptCanvas/Libraries/Core/RepeaterNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Core/ScriptEventBase.h
    Include/ScriptCanvas/Libraries/Core/ScriptEventBase.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/SendScriptEvent.h
    Include/ScriptCanvas/Libraries/Core/SendScriptEvent.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/SetVariable.h
    Include/ScriptCanvas/Libraries/Core/SetVariable.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/Start.h
    Include/ScriptCanvas/Libraries/Core/Start.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Core/UnaryOperator.h
    Include/ScriptCanvas/Libraries/Deprecated/AABBNodes.h
    Include/ScriptCanvas/Libraries/Deprecated/ColorNodes.h
    Include/ScriptCanvas/Libraries/Deprecated/Contains.h
    Include/ScriptCanvas/Libraries/Deprecated/Contains.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Deprecated/CRCNodes.h
    Include/ScriptCanvas/Libraries/Deprecated/DeprecatedNodeLibrary.h
    Include/ScriptCanvas/Libraries/Deprecated/Divide.h
    Include/ScriptCanvas/Libraries/Deprecated/EntityNodes.h
    Include/ScriptCanvas/Libraries/Deprecated/MathGenerics.h
    Include/ScriptCanvas/Libraries/Deprecated/MathRandom.h
    Include/ScriptCanvas/Libraries/Deprecated/Matrix3x3Nodes.h
    Include/ScriptCanvas/Libraries/Deprecated/Matrix4x4Nodes.h
    Include/ScriptCanvas/Libraries/Deprecated/Multiply.h
    Include/ScriptCanvas/Libraries/Deprecated/OBBNodes.h
    Include/ScriptCanvas/Libraries/Deprecated/PlaneNodes.h
    Include/ScriptCanvas/Libraries/Deprecated/Replace.h
    Include/ScriptCanvas/Libraries/Deprecated/Replace.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Deprecated/RotateMethod.h
    Include/ScriptCanvas/Libraries/Deprecated/RotationNodes.h
    Include/ScriptCanvas/Libraries/Deprecated/StringGenerics.h
    Include/ScriptCanvas/Libraries/Deprecated/StringMethods.h
    Include/ScriptCanvas/Libraries/Deprecated/Subtract.h
    Include/ScriptCanvas/Libraries/Deprecated/Sum.h
    Include/ScriptCanvas/Libraries/Deprecated/TransformNodes.h
    Include/ScriptCanvas/Libraries/Deprecated/Utilities.h
    Include/ScriptCanvas/Libraries/Deprecated/Utilities.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Deprecated/Vector2Nodes.h
    Include/ScriptCanvas/Libraries/Deprecated/Vector3Nodes.h
    Include/ScriptCanvas/Libraries/Deprecated/Vector4Nodes.h
    Include/ScriptCanvas/Libraries/Deprecated/WorldNodes.h
    Include/ScriptCanvas/Libraries/Entity/EntityFunctions.h
    Include/ScriptCanvas/Libraries/Entity/EntityFunctions.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Logic/And.h
    Include/ScriptCanvas/Libraries/Logic/Any.h
    Include/ScriptCanvas/Libraries/Logic/Any.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Break.h
    Include/ScriptCanvas/Libraries/Logic/Break.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Cycle.h
    Include/ScriptCanvas/Libraries/Logic/Cycle.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Gate.h
    Include/ScriptCanvas/Libraries/Logic/Gate.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Indexer.h
    Include/ScriptCanvas/Libraries/Logic/Indexer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/IsNull.h
    Include/ScriptCanvas/Libraries/Logic/IsNull.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Logic.h
    Include/ScriptCanvas/Libraries/Logic/Multiplexer.h
    Include/ScriptCanvas/Libraries/Logic/Multiplexer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Not.h
    Include/ScriptCanvas/Libraries/Logic/Once.h
    Include/ScriptCanvas/Libraries/Logic/Once.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Or.h
    Include/ScriptCanvas/Libraries/Logic/OrderedSequencer.h
    Include/ScriptCanvas/Libraries/Logic/OrderedSequencer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/Sequencer.h
    Include/ScriptCanvas/Libraries/Logic/Sequencer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/TargetedSequencer.h
    Include/ScriptCanvas/Libraries/Logic/TargetedSequencer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/WeightedRandomSequencer.h
    Include/ScriptCanvas/Libraries/Logic/WeightedRandomSequencer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Logic/While.h
    Include/ScriptCanvas/Libraries/Logic/While.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Math/AABB.h
    Include/ScriptCanvas/Libraries/Math/AABB.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/Color.h
    Include/ScriptCanvas/Libraries/Math/Color.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/CRC.h
    Include/ScriptCanvas/Libraries/Math/CRC.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/MathExpression.h
    Include/ScriptCanvas/Libraries/Math/MathExpression.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Math/MathFunctions.h
    Include/ScriptCanvas/Libraries/Math/MathFunctions.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/MathNodeUtilities.h
    Include/ScriptCanvas/Libraries/Math/Matrix3x3.h
    Include/ScriptCanvas/Libraries/Math/Matrix3x3.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/Matrix4x4.h
    Include/ScriptCanvas/Libraries/Math/Matrix4x4.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/OBB.h
    Include/ScriptCanvas/Libraries/Math/OBB.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/Plane.h
    Include/ScriptCanvas/Libraries/Math/Plane.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/Quaternion.h
    Include/ScriptCanvas/Libraries/Math/Quaternion.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/Transform.h
    Include/ScriptCanvas/Libraries/Math/Transform.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/Vector2.h
    Include/ScriptCanvas/Libraries/Math/Vector2.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/Vector3.h
    Include/ScriptCanvas/Libraries/Math/Vector3.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Math/Vector4.h
    Include/ScriptCanvas/Libraries/Math/Vector4.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/Comparison/Comparison.h
    Include/ScriptCanvas/Libraries/Comparison/EqualTo.h
    Include/ScriptCanvas/Libraries/Comparison/NotEqualTo.h
    Include/ScriptCanvas/Libraries/Comparison/Less.h
    Include/ScriptCanvas/Libraries/Comparison/Greater.h
    Include/ScriptCanvas/Libraries/Comparison/LessEqual.h
    Include/ScriptCanvas/Libraries/Comparison/GreaterEqual.h
    Include/ScriptCanvas/Libraries/Time/Time.h
    Include/ScriptCanvas/Libraries/Time/Countdown.h
    Include/ScriptCanvas/Libraries/Time/Countdown.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Time/DelayNodeable.h
    Include/ScriptCanvas/Libraries/Time/DelayNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Time/Duration.h
    Include/ScriptCanvas/Libraries/Time/Duration.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Time/HeartBeat.h
    Include/ScriptCanvas/Libraries/Time/HeartBeat.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Time/Timer.h
    Include/ScriptCanvas/Libraries/Time/Timer.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Time/TimeDelayNodeable.h
    Include/ScriptCanvas/Libraries/Time/TimeDelayNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Time/DurationNodeable.h
    Include/ScriptCanvas/Libraries/Time/DurationNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Time/HeartBeatNodeable.h
    Include/ScriptCanvas/Libraries/Time/HeartBeatNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Time/TimerNodeable.h
    Include/ScriptCanvas/Libraries/Time/TimerNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Spawning/Spawning.h
    Include/ScriptCanvas/Libraries/Spawning/CreateSpawnTicketNodeable.h
    Include/ScriptCanvas/Libraries/Spawning/CreateSpawnTicketNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Spawning/SpawnNodeable.h
    Include/ScriptCanvas/Libraries/Spawning/SpawnNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/Spawning/DespawnNodeable.h
    Include/ScriptCanvas/Libraries/Spawning/DespawnNodeable.ScriptCanvasNodeable.xml
    Include/ScriptCanvas/Libraries/String/Format.h
    Include/ScriptCanvas/Libraries/String/Format.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/String/Print.h
    Include/ScriptCanvas/Libraries/String/Print.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/String/StringFunctions.h
    Include/ScriptCanvas/Libraries/String/StringFunctions.ScriptCanvasFunction.xml
    Include/ScriptCanvas/Libraries/UnitTesting/AddFailure.h
    Include/ScriptCanvas/Libraries/UnitTesting/AddFailure.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/AddSuccess.h
    Include/ScriptCanvas/Libraries/UnitTesting/AddSuccess.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/Checkpoint.h
    Include/ScriptCanvas/Libraries/UnitTesting/Checkpoint.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectEqual.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectEqual.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectFalse.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectFalse.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThan.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThan.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThanEqual.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectGreaterThanEqual.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThan.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThan.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThanEqual.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectLessThanEqual.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectNotEqual.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectNotEqual.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectTrue.h
    Include/ScriptCanvas/Libraries/UnitTesting/ExpectTrue.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/MarkComplete.h
    Include/ScriptCanvas/Libraries/UnitTesting/MarkComplete.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestBus.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestBusMacros.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTesting.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestingLibrary.h
    Include/ScriptCanvas/Libraries/UnitTesting/Auxiliary/Auxiliary.h
    Include/ScriptCanvas/Libraries/UnitTesting/UnitTestBusSender.h
    Include/ScriptCanvas/Libraries/Operators/Operators.h
    Include/ScriptCanvas/Libraries/Operators/Operator.h
    Include/ScriptCanvas/Libraries/Operators/Operator.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorAt.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorAt.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorBack.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorBack.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorClear.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorClear.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorEmpty.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorEmpty.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorErase.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorErase.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorFront.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorFront.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorInsert.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorInsert.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorPushBack.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorPushBack.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorSize.h
    Include/ScriptCanvas/Libraries/Operators/Containers/OperatorSize.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorAdd.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorAdd.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorArithmetic.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorArithmetic.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDiv.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDiv.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDivideByNumber.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorDivideByNumber.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLength.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLength.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerp.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerp.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorMul.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorMul.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorSub.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorSub.ScriptCanvasGrammar.xml
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerpNodeable.h
    Include/ScriptCanvas/Libraries/Operators/Math/OperatorLerpNodeableNode.h
    Include/ScriptCanvas/Serialization/BehaviorContextObjectSerializer.h
    Include/ScriptCanvas/Serialization/DatumSerializer.h
    Include/ScriptCanvas/Serialization/RuntimeVariableSerializer.h
    Include/ScriptCanvas/Data/DataTrait.h
    Include/ScriptCanvas/Data/PropertyTraits.h
    Include/ScriptCanvas/Data/Traits.h
    Include/ScriptCanvas/Variable/VariableBus.h
    Include/ScriptCanvas/Variable/GraphVariable.h
    Include/ScriptCanvas/Variable/GraphVariableManagerComponent.h
    Include/ScriptCanvas/Variable/VariableCore.h
    Include/ScriptCanvas/Variable/VariableData.h
    Include/ScriptCanvas/Utils/DataUtils.h
    Include/ScriptCanvas/Utils/NodeUtils.h
    Include/ScriptCanvas/Utils/SerializationUtils.h
    Include/ScriptCanvas/Utils/VersionConverters.h
    Include/ScriptCanvas/Utils/BehaviorContextUtils.h
    Include/ScriptCanvas/Utils/ReplacementUtils.h
    Include/ScriptCanvas/Utils/ScriptCanvasConstants.h
)

set(SKIP_UNITY_BUILD_INCLUSION_FILES
    Include/ScriptCanvas/Libraries/Core/FunctionCallNode.h
    Include/ScriptCanvas/Libraries/Core/FunctionCallNodeIsOutOfDate.h
)
