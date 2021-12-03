#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    base.h
    Docs.h
    Platform.cpp
    Platform.h
    PlatformDef.h
    PlatformIncl.h
    AzCoreModule.h
    AzCoreModule.cpp
    Asset/AssetCommon.cpp
    Asset/AssetCommon.h
    Asset/AssetContainer.cpp
    Asset/AssetContainer.h
    Asset/AssetDataStream.cpp
    Asset/AssetDataStream.h
    Asset/AssetJsonSerializer.cpp
    Asset/AssetJsonSerializer.h
    Asset/AssetManager.cpp
    Asset/AssetManager.h
    Asset/AssetManager_private.h
    Asset/AssetManagerBus.h
    Asset/AssetManagerComponent.cpp
    Asset/AssetManagerComponent.h
    Asset/AssetSerializer.cpp
    Asset/AssetSerializer.h
    Asset/AssetTypeInfoBus.h
    Asset/AssetInternal/WeakAsset.h
    Casting/lossy_cast.h
    Casting/numeric_cast.h
    Casting/numeric_cast_internal.h
    Component/Component.cpp
    Component/Component.h
    Component/ComponentApplication.cpp
    Component/ComponentApplication.h
    Component/ComponentApplicationBus.h
    Component/ComponentApplicationLifecycle.cpp
    Component/ComponentApplicationLifecycle.h
    Component/ComponentBus.cpp
    Component/ComponentBus.h
    Component/ComponentExport.h
    Component/Entity.cpp
    Component/Entity.h
    Component/EntityBus.h
    Component/EntityId.h
    Component/EntityIdSerializer.cpp
    Component/EntityIdSerializer.h
    Component/EntitySerializer.cpp
    Component/EntitySerializer.h
    Component/EntityUtils.cpp
    Component/EntityUtils.h
    Component/NamedEntityId.cpp
    Component/NamedEntityId.h
    Component/NonUniformScaleBus.cpp
    Component/NonUniformScaleBus.h
    Component/TickBus.h
    Component/TransformBus.h
    Console/Console.cpp
    Console/Console.h
    Console/ConsoleDataWrapper.h
    Console/ConsoleDataWrapper.inl
    Console/ConsoleFunctor.cpp
    Console/ConsoleFunctor.h
    Console/ConsoleFunctor.inl
    Console/ConsoleTypeHelpers.h
    Console/ConsoleTypeHelpers.inl
    Console/IConsole.h
    Console/IConsoleTypes.h
    Console/ILogger.h
    Console/LoggerSystemComponent.cpp
    Console/LoggerSystemComponent.h
    Slice/SliceAsset.cpp
    Slice/SliceAsset.h
    Slice/SliceAssetHandler.cpp
    Slice/SliceAssetHandler.h
    Slice/SliceBus.h
    Slice/SliceComponent.cpp
    Slice/SliceComponent.h
    Slice/SliceSystemComponent.h
    Slice/SliceSystemComponent.cpp
    Slice/SliceMetadataInfoBus.h
    Slice/SliceMetadataInfoComponent.h
    Slice/SliceMetadataInfoComponent.cpp
    Compression/compression.cpp
    Compression/Compression.h
    Compression/zstd_compression.cpp
    Compression/zstd_compression.h
    Debug/Budget.h
    Debug/Budget.cpp
    Debug/BudgetTracker.h
    Debug/BudgetTracker.cpp
    Debug/LocalFileEventLogger.h
    Debug/LocalFileEventLogger.cpp
    Debug/IEventLogger.h
    Debug/MemoryProfiler.h
    Debug/Profiler.cpp
    Debug/Profiler.inl
    Debug/Profiler.h
    Debug/ProfilerBus.h
    Debug/ProfilerReflection.cpp
    Debug/ProfilerReflection.h
    Debug/StackTracer.h
    Debug/Timer.h
    Debug/Trace.cpp
    Debug/Trace.h
    Debug/TraceMessageBus.h
    Debug/TraceReflection.cpp
    Debug/TraceReflection.h
    DOM/DomVisitor.cpp
    DOM/DomVisitor.h
    EBus/BusImpl.h
    EBus/EBus.h
    EBus/EBusEnvironment.cpp
    EBus/Environment.h
    EBus/Event.h
    EBus/Event.inl
    EBus/EventSchedulerSystemComponent.cpp
    EBus/EventSchedulerSystemComponent.h
    EBus/IEventScheduler.h
    EBus/OrderedEvent.h
    EBus/OrderedEvent.inl
    EBus/Policies.h
    EBus/Results.h
    EBus/ScheduledEvent.cpp
    EBus/ScheduledEvent.h
    EBus/ScheduledEventHandle.cpp
    EBus/ScheduledEventHandle.h
    EBus/Internal/BusContainer.h
    EBus/Internal/CallstackEntry.h
    EBus/Internal/Debug.h
    EBus/Internal/Handlers.h
    EBus/Internal/StoragePolicies.h
    Interface/Interface.h
    IO/ByteContainerStream.h
    IO/CompressionBus.h
    IO/CompressionBus.cpp
    IO/Compressor.cpp
    IO/Compressor.h
    IO/CompressorStream.cpp
    IO/CompressorStream.h
    IO/CompressorZLib.cpp
    IO/CompressorZLib.h
    IO/CompressorZStd.cpp
    IO/CompressorZStd.h
    IO/FileIO.cpp
    IO/FileIO.h
    IO/FileIOEventBus.h
    IO/FileReader.cpp
    IO/FileReader.h
    IO/IOUtils.h
    IO/IOUtils.cpp
    IO/IStreamer.h
    IO/IStreamerTypes.h
    IO/IStreamerTypes.inl
    IO/IStreamerTypes.cpp
    IO/GenericStreams.cpp
    IO/GenericStreams.h
    IO/Path/Path.cpp
    IO/Path/Path.h
    IO/Path/Path.inl
    IO/Path/PathIterable.inl
    IO/Path/PathParser.inl
    IO/Path/PathReflect.cpp
    IO/Path/PathReflect.h
    IO/Path/Path_fwd.h
    IO/SystemFile.cpp
    IO/SystemFile.h
    IO/TextStreamWriters.h
    IO/Streamer/BlockCache.h
    IO/Streamer/BlockCache.cpp
    IO/Streamer/DedicatedCache.h
    IO/Streamer/DedicatedCache.cpp
    IO/Streamer/FileRange.h
    IO/Streamer/FileRange.cpp
    IO/Streamer/FileRequest.h
    IO/Streamer/FileRequest.inl
    IO/Streamer/FileRequest.cpp
    IO/Streamer/FullFileDecompressor.h
    IO/Streamer/FullFileDecompressor.cpp
    IO/Streamer/ReadSplitter.h
    IO/Streamer/ReadSplitter.cpp
    IO/Streamer/RequestPath.h
    IO/Streamer/RequestPath.cpp
    IO/Streamer/Scheduler.h
    IO/Streamer/Scheduler.cpp
    IO/Streamer/Statistics.h
    IO/Streamer/Statistics.cpp
    IO/Streamer/StorageDrive.h
    IO/Streamer/StorageDrive.cpp
    IO/Streamer/StreamerConfiguration.h
    IO/Streamer/StreamerConfiguration.cpp
    IO/Streamer/Streamer.cpp
    IO/Streamer/Streamer.h
    IO/Streamer/StreamerContext.h
    IO/Streamer/StreamerContext.cpp
    IO/Streamer/StreamerComponent.cpp
    IO/Streamer/StreamerComponent.h
    IO/Streamer/StreamStackEntry.h
    IO/Streamer/StreamStackEntry.cpp
    IPC/SharedMemory.cpp
    IPC/SharedMemory.h
    Jobs/Algorithms.h
    Jobs/Internal/JobManagerBase.cpp
    Jobs/Internal/JobManagerBase.h
    Jobs/Internal/JobManagerWorkStealing.cpp
    Jobs/Internal/JobManagerWorkStealing.h
    Jobs/Internal/JobNotify.h
    Jobs/Job.cpp
    Jobs/Job.h
    Jobs/JobCancelGroup.h
    Jobs/JobCompletion.h
    Jobs/JobCompletionSpin.h
    Jobs/JobContext.cpp
    Jobs/JobContext.h
    Jobs/JobEmpty.h
    Jobs/JobFunction.h
    Jobs/JobManager.cpp
    Jobs/JobManager.h
    Jobs/JobManagerBus.h
    Jobs/JobManagerComponent.cpp
    Jobs/JobManagerComponent.h
    Jobs/JobManagerDesc.h
    Jobs/LegacyJobExecutor.h
    Jobs/MultipleDependentJob.h
    Jobs/task_group.h
    Math/Aabb.cpp
    Math/Aabb.h
    Math/Aabb.inl
    Math/Color.cpp
    Math/Color.h
    Math/Color.inl
    Math/ColorSerializer.h
    Math/ColorSerializer.cpp
    Math/Crc.cpp
    Math/Crc.inl
    Math/Crc.h
    Math/DocsMath.h
    Math/Frustum.cpp
    Math/Frustum.h
    Math/Frustum.inl
    Math/Geometry2DUtils.cpp
    Math/Geometry2DUtils.h
    Math/Guid.h
    Math/Internal/MathTypes.h
    Math/Internal/SimdMathVec1_neon.inl
    Math/Internal/SimdMathVec1_scalar.inl
    Math/Internal/SimdMathVec1_sse.inl
    Math/Internal/SimdMathVec2_neon.inl
    Math/Internal/SimdMathVec2_scalar.inl
    Math/Internal/SimdMathVec2_sse.inl
    Math/Internal/SimdMathVec3_neon.inl
    Math/Internal/SimdMathVec3_scalar.inl
    Math/Internal/SimdMathVec3_sse.inl
    Math/Internal/SimdMathVec4_neon.inl
    Math/Internal/SimdMathVec4_scalar.inl
    Math/Internal/SimdMathVec4_sse.inl
    Math/Internal/SimdMathCommon_neon.inl
    Math/Internal/SimdMathCommon_neonDouble.inl
    Math/Internal/SimdMathCommon_neonQuad.inl
    Math/Internal/SimdMathCommon_simd.inl
    Math/Internal/SimdMathCommon_sse.inl
    Math/Internal/VectorConversions.inl
    Math/Internal/VertexContainer.inl
    Math/InterpolationSample.h
    Math/IntersectPoint.h
    Math/IntersectSegment.inl
    Math/IntersectSegment.cpp
    Math/IntersectSegment.h
    Math/MathIntrinsics.h
    Math/MathReflection.cpp
    Math/MathReflection.h
    Math/MathScriptHelpers.cpp
    Math/MathScriptHelpers.h
    Math/MathUtils.cpp
    Math/MathUtils.h
    Math/MathMatrixSerializer.h
    Math/MathMatrixSerializer.cpp
    Math/MathVectorSerializer.h
    Math/MathVectorSerializer.cpp
    Math/Matrix3x3.cpp
    Math/Matrix3x3.h
    Math/Matrix3x3.inl
    Math/Matrix3x4.cpp
    Math/Matrix3x4.h
    Math/Matrix3x4.inl
    Math/Matrix4x4.cpp
    Math/Matrix4x4.h
    Math/Matrix4x4.inl
    Math/MatrixUtils.h
    Math/MatrixUtils.cpp
    Math/Obb.cpp
    Math/Obb.h
    Math/Obb.inl
    Math/Plane.cpp
    Math/Plane.h
    Math/Plane.inl
    Math/PolygonPrism.h
    Math/PolygonPrism.cpp
    Math/Quaternion.cpp
    Math/Quaternion.inl
    Math/Quaternion.h
    Math/Random.h
    Math/Sfmt.cpp
    Math/Sfmt.h
    Math/ShapeIntersection.h
    Math/ShapeIntersection.inl
    Math/SimdMath.h
    Math/SimdMathVec1.h
    Math/SimdMathVec2.h
    Math/SimdMathVec3.h
    Math/SimdMathVec4.h
    Math/Sha1.h
    Math/Spline.cpp
    Math/Spline.h
    Math/Sphere.h
    Math/Sphere.inl
    Math/Transform.cpp
    Math/Transform.h
    Math/Transform.inl
    Math/TransformSerializer.cpp
    Math/TransformSerializer.h
    Math/Uuid.cpp
    Math/Uuid.h
    Math/UuidSerializer.h
    Math/UuidSerializer.cpp
    Math/Vector2.cpp
    Math/Vector2.h
    Math/Vector2.inl
    Math/Vector3.cpp
    Math/Vector3.h
    Math/Vector3.inl
    Math/Vector4.cpp
    Math/Vector4.h
    Math/Vector4.inl
    Math/VectorConversions.h
    Math/VertexContainer.h
    Math/VertexContainer.cpp
    Math/VertexContainerInterface.h
    Math/PackedVector3.h
    Math/Color.h
    Math/Color.cpp
    Math/ColorSerializer.h
    Math/ColorSerializer.cpp
    Math/ToString.h
    Math/ToString.cpp
    Memory/AllocationRecords.cpp
    Memory/AllocationRecords.h
    Memory/AllocatorBase.cpp
    Memory/AllocatorBase.h
    Memory/AllocatorManager.cpp
    Memory/AllocatorManager.h
    Memory/AllocatorOverrideShim.cpp
    Memory/AllocatorOverrideShim.h
    Memory/AllocatorWrapper.h
    Memory/AllocatorScope.h
    Memory/BestFitExternalMapAllocator.cpp
    Memory/BestFitExternalMapAllocator.h
    Memory/BestFitExternalMapSchema.cpp
    Memory/BestFitExternalMapSchema.h
    Memory/Config.h
    Memory/dlmalloc.inl
    Memory/HeapSchema.h
    Memory/HphaSchema.cpp
    Memory/HphaSchema.h
    Memory/IAllocator.cpp
    Memory/IAllocator.h
    Memory/MallocSchema.cpp
    Memory/MallocSchema.h
    Memory/Memory.cpp
    Memory/Memory.h
    Memory/MemoryComponent.cpp
    Memory/MemoryComponent.h
    Memory/nedmalloc.inl
    Memory/NewAndDelete.inl
    Memory/OSAllocator.cpp
    Memory/OSAllocator.h
    Memory/OverrunDetectionAllocator.cpp
    Memory/OverrunDetectionAllocator.h
    Memory/PoolAllocator.h
    Memory/PoolSchema.cpp
    Memory/PoolSchema.h
    Memory/SimpleSchemaAllocator.h
    Memory/SystemAllocator.cpp
    Memory/SystemAllocator.h
    Module/DynamicModuleHandle.cpp
    Module/DynamicModuleHandle.h
    Module/Environment.cpp
    Module/Environment.h
    Module/Module.cpp
    Module/Module.h
    Module/ModuleManagerBus.h
    Module/ModuleManager.cpp
    Module/ModuleManager.h
    Module/Internal/ModuleManagerSearchPathTool.h
    Module/Internal/ModuleManagerSearchPathTool.cpp
    NativeUI/NativeUISystemComponent.cpp
    NativeUI/NativeUISystemComponent.h
    NativeUI/NativeUIRequests.h
    Name/Name.h
    Name/Name.cpp
    Name/NameDictionary.h
    Name/NameDictionary.cpp
    Name/NameJsonSerializer.h
    Name/NameJsonSerializer.cpp
    Name/NameSerializer.h
    Name/NameSerializer.cpp
    Name/Internal/NameData.h
    Name/Internal/NameData.cpp
    Outcome/Outcome.h
    Outcome/Internal/OutcomeStorage.h
    Outcome/Internal/OutcomeImpl.h
    Preprocessor/CodeGen.h
    Preprocessor/Enum.h
    Preprocessor/EnumReflectUtils.h
    Preprocessor/Sequences.h
    RTTI/RTTI.h
    RTTI/TypeInfo.h
    RTTI/TypeInfoSimple.h
    RTTI/ReflectContext.h
    RTTI/ReflectContext.cpp
    RTTI/ReflectionManager.h
    RTTI/ReflectionManager.cpp
    RTTI/AttributeReader.h
    RTTI/AzStdOnDemandPrettyName.inl
    RTTI/AzStdOnDemandReflection.inl
    RTTI/AzStdOnDemandReflectionSpecializations.cpp
    RTTI/AzStdOnDemandReflectionLuaFunctions.inl
    RTTI/BehaviorContext.cpp
    RTTI/BehaviorContext.h
    RTTI/BehaviorContextUtilities.h
    RTTI/BehaviorContextUtilities.cpp
    RTTI/BehaviorInterfaceProxy.h
    RTTI/BehaviorObjectSignals.h
    RTTI/TypeSafeIntegral.h
    Script/ScriptAsset.cpp
    Script/ScriptAsset.h
    Script/ScriptContext.h
    Script/ScriptContext.cpp
    Script/ScriptContextAttributes.h
    Script/ScriptContextDebug.cpp
    Script/ScriptContextDebug.h
    Script/ScriptSystemBus.h
    Script/ScriptSystemComponent.cpp
    Script/ScriptSystemComponent.h
    Script/ScriptTimePoint.cpp
    Script/ScriptTimePoint.h
    Script/ScriptProperty.h
    Script/ScriptProperty.cpp
    Script/ScriptPropertySerializer.h
    Script/ScriptPropertySerializer.cpp
    Script/ScriptPropertyTable.h
    Script/ScriptPropertyTable.cpp
    Script/ScriptPropertyWatcherBus.h
    Script/ScriptDebug.cpp
    Script/ScriptDebug.h
    ScriptCanvas/ScriptCanvasAttributes.h
    ScriptCanvas/ScriptCanvasOnDemandNames.cpp
    ScriptCanvas/ScriptCanvasOnDemandNames.h
    Serialization/DataOverlay.h
    Serialization/DataOverlayInstanceMsgs.h
    Serialization/DataOverlayProviderMsgs.cpp
    Serialization/DataOverlayProviderMsgs.h
    Serialization/AZStdContainers.inl
    Serialization/AZStdAnyDataContainer.inl
    Serialization/DynamicSerializableField.cpp
    Serialization/DynamicSerializableField.h
    Serialization/EditContext.cpp
    Serialization/EditContext.h
    Serialization/EditContext.inl
    Serialization/EditContextConstants.inl
    Serialization/IdUtils.inl
    Serialization/IdUtils.h
    Serialization/Utils.h
    Serialization/SerializationUtils.cpp
    Serialization/ObjectStream.cpp
    Serialization/ObjectStream.h
    Serialization/SerializeContext.cpp
    Serialization/SerializeContext.h
    Serialization/SerializeContextEnum.cpp
    Serialization/SerializeContextEnum.inl
    Serialization/DataPatch.h
    Serialization/DataPatch.cpp
    Serialization/DataPatchBus.h
    Serialization/DataPatchUpgradeManager.h
    Serialization/DataPatchUpgradeManager.cpp
    Serialization/Json/ArraySerializer.h
    Serialization/Json/ArraySerializer.cpp
    Serialization/Json/BaseJsonSerializer.h
    Serialization/Json/BaseJsonSerializer.cpp
    Serialization/Json/BasicContainerSerializer.h
    Serialization/Json/BasicContainerSerializer.cpp
    Serialization/Json/BoolSerializer.h
    Serialization/Json/BoolSerializer.cpp
    Serialization/Json/ByteStreamSerializer.h
    Serialization/Json/ByteStreamSerializer.cpp
    Serialization/Json/CastingHelpers.h
    Serialization/Json/DoubleSerializer.h
    Serialization/Json/DoubleSerializer.cpp
    Serialization/Json/IntSerializer.h
    Serialization/Json/IntSerializer.cpp
    Serialization/Json/JsonDeserializer.h
    Serialization/Json/JsonDeserializer.cpp
    Serialization/Json/JsonImporter.cpp
    Serialization/Json/JsonImporter.h
    Serialization/Json/JsonMerger.h
    Serialization/Json/JsonMerger.cpp
    Serialization/Json/JsonSerialization.h
    Serialization/Json/JsonSerialization.cpp
    Serialization/Json/JsonSerializationMetadata.h
    Serialization/Json/JsonSerializationMetadata.inl
    Serialization/Json/JsonSerializationResult.h
    Serialization/Json/JsonSerializationResult.cpp
    Serialization/Json/JsonSerializationSettings.h
    Serialization/Json/JsonSerializer.h
    Serialization/Json/JsonSerializer.cpp
    Serialization/Json/JsonStringConversionUtils.h
    Serialization/Json/JsonSystemComponent.h
    Serialization/Json/JsonSystemComponent.cpp
    Serialization/Json/JsonUtils.h
    Serialization/Json/JsonUtils.cpp
    Serialization/Json/MapSerializer.h
    Serialization/Json/MapSerializer.cpp
    Serialization/Json/RegistrationContext.h
    Serialization/Json/RegistrationContext.cpp
    Serialization/Json/SmartPointerSerializer.h
    Serialization/Json/SmartPointerSerializer.cpp
    Serialization/Json/StackedString.h
    Serialization/Json/StackedString.cpp
    Serialization/Json/StringSerializer.h
    Serialization/Json/StringSerializer.cpp
    Serialization/Json/TupleSerializer.h
    Serialization/Json/TupleSerializer.cpp
    Serialization/Json/UnorderedSetSerializer.h
    Serialization/Json/UnorderedSetSerializer.cpp
    Serialization/Json/UnsupportedTypesSerializer.h
    Serialization/Json/UnsupportedTypesSerializer.cpp
    Serialization/std/VariantReflection.inl
    Settings/CommandLine.cpp
    Settings/CommandLine.h
    Settings/SettingsRegistry.cpp
    Settings/SettingsRegistry.h
    Settings/SettingsRegistryConsoleUtils.cpp
    Settings/SettingsRegistryConsoleUtils.h
    Settings/SettingsRegistryImpl.cpp
    Settings/SettingsRegistryImpl.h
    Settings/SettingsRegistryMergeUtils.cpp
    Settings/SettingsRegistryMergeUtils.h
    Settings/SettingsRegistryScriptUtils.cpp
    Settings/SettingsRegistryScriptUtils.h
    Settings/SettingsRegistryVisitorUtils.cpp
    Settings/SettingsRegistryVisitorUtils.h
    State/HSM.cpp
    State/HSM.h
    Statistics/NamedRunningStatistic.h
    Statistics/RunningStatistic.cpp
    Statistics/RunningStatistic.h
    Statistics/StatisticalProfiler.h
    Statistics/StatisticalProfilerProxy.h
    Statistics/StatisticalProfilerProxySystemComponent.cpp
    Statistics/StatisticalProfilerProxySystemComponent.h
    Statistics/StatisticsManager.h
    StringFunc/StringFunc.cpp
    StringFunc/StringFunc.h
    UserSettings/UserSettings.cpp
    UserSettings/UserSettings.h
    UserSettings/UserSettingsComponent.cpp
    UserSettings/UserSettingsComponent.h
    UserSettings/UserSettingsProvider.cpp
    UserSettings/UserSettingsProvider.h
    XML/rapidxml.h
    XML/rapidxml_iterators.h
    XML/rapidxml_print.h
    XML/rapidxml_utils.h
    JSON/allocators.h
    JSON/cursorstreamwrapper.h
    JSON/document.h
    JSON/encodedstream.h
    JSON/encodings.h
    JSON/filereadstream.h
    JSON/filewritestream.h
    JSON/fwd.h
    JSON/istreamwrapper.h
    JSON/memorybuffer.h
    JSON/memorystream.h
    JSON/ostreamwrapper.h
    JSON/pointer.h
    JSON/prettywriter.h
    JSON/rapidjson.h
    JSON/reader.h
    JSON/schema.h
    JSON/stream.h
    JSON/stringbuffer.h
    JSON/writer.h
    JSON/error/en.h
    JSON/error/error.h
    Utils/TypeHash.cpp
    Utils/TypeHash.h
    Utils/Utils.cpp
    Utils/Utils.h
    Script/lua/lua.h
    Memory/HeapSchema.cpp
    PlatformId/PlatformDefaults.h
    PlatformId/PlatformDefaults.cpp
    PlatformId/PlatformId.h
    PlatformId/PlatformId.cpp
    Socket/AzSocket_fwd.h
    Socket/AzSocket.cpp
    Socket/AzSocket.h
    Task/Internal/Task.cpp
    Task/Internal/Task.inl
    Task/Internal/Task.h
    Task/Internal/TaskConfig.h
    Task/TaskDescriptor.h
    Task/TaskExecutor.cpp
    Task/TaskExecutor.h
    Task/TaskGraph.cpp
    Task/TaskGraph.h
    Task/TaskGraph.inl
    Task/TaskGraphSystemComponent.h
    Task/TaskGraphSystemComponent.cpp
    Threading/ThreadSafeDeque.h
    Threading/ThreadSafeDeque.inl
    Threading/ThreadSafeObject.h
    Threading/ThreadSafeObject.inl
    Threading/ThreadUtils.h
    Threading/ThreadUtils.cpp
    Time/ITime.h
    Time/TimeSystem.cpp
    Time/TimeSystem.h
)

# Prevent the following files from being grouped in UNITY builds
set(SKIP_UNITY_BUILD_INCLUSION_FILES
    # In some platforms, dlmalloc.inl gives issues when compiled in unity because there is a getpagesize defined differently
    Memory/HeapSchema.cpp
)
