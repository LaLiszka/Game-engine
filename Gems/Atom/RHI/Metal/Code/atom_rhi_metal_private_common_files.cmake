#
# Copyright (c) Contributors to the Open 3D Engine Project
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    Source/RHI/Buffer.cpp
    Source/RHI/Buffer.h
    Source/RHI/BufferView.cpp
    Source/RHI/BufferView.h
    Source/RHI/BufferPool.cpp
    Source/RHI/BufferPool.h
    Source/RHI/BufferMemoryView.cpp
    Source/RHI/BufferMemoryView.h
    Source/RHI/BufferMemoryAllocator.cpp
    Source/RHI/BufferMemoryAllocator.h
    Source/RHI/BufferPoolResolver.cpp
    Source/RHI/BufferPoolResolver.h
    Source/RHI/CommandList.cpp
    Source/RHI/CommandList.h
    Source/RHI/CommandListPool.cpp
    Source/RHI/CommandListPool.h
    Source/RHI/AsyncUploadQueue.h
    Source/RHI/AsyncUploadQueue.cpp
    Source/RHI/Conversions.cpp
    Source/RHI/Conversions.h
    Source/RHI/CommandListBase.cpp
    Source/RHI/CommandListBase.h
    Source/RHI/Metal.cpp
    Source/RHI/Metal.h
    Source/RHI/MetalCopyShaders.h
    Source/RHI/Device.cpp
    Source/RHI/Device.h
    Source/RHI/CommandQueue.cpp
    Source/RHI/CommandQueue.h
    Source/RHI/CommandQueueContext.cpp
    Source/RHI/CommandQueueContext.h
    Source/RHI/CommandQueueCommandBuffer.cpp
    Source/RHI/CommandQueueCommandBuffer.h
    Source/RHI/Fence.cpp
    Source/RHI/Fence.h
    Source/RHI/FrameGraphCompiler.cpp
    Source/RHI/FrameGraphCompiler.h
    Source/RHI/FrameGraphExecuteGroup.cpp
    Source/RHI/FrameGraphExecuteGroup.h
    Source/RHI/FrameGraphExecuteGroupBase.cpp
    Source/RHI/FrameGraphExecuteGroupBase.h
    Source/RHI/FrameGraphExecuteGroupMerged.cpp
    Source/RHI/FrameGraphExecuteGroupMerged.h
    Source/RHI/FrameGraphExecuter.cpp
    Source/RHI/FrameGraphExecuter.h
    Source/RHI/Image.cpp
    Source/RHI/Image.h
    Source/RHI/ImagePool.cpp
    Source/RHI/ImagePool.h
    Source/RHI/ImagePoolResolver.cpp
    Source/RHI/ImagePoolResolver.h
    Source/RHI/ImageView.cpp
    Source/RHI/ImageView.h
    Source/RHI/StreamingImagePool.cpp
    Source/RHI/StreamingImagePool.h
    Source/RHI/StreamingImagePoolResolver.cpp
    Source/RHI/StreamingImagePoolResolver.h
    Source/RHI/Memory.h
    Source/RHI/MemoryView.cpp
    Source/RHI/MemoryView.h
    Source/RHI/MemorySubAllocator.h
    Source/RHI/MemoryPageAllocator.cpp
    Source/RHI/MemoryPageAllocator.h
    Source/RHI/PhysicalDevice.cpp
    Source/RHI/PhysicalDevice.h
    Source/RHI/PipelineLayout.cpp
    Source/RHI/PipelineLayout.h
    Source/RHI/PipelineState.cpp
    Source/RHI/PipelineState.h
    Source/RHI/PipelineLibrary.cpp
    Source/RHI/PipelineLibrary.h
    Source/RHI/ReleaseQueue.h
    Source/RHI/ResourcePoolResolver.h
    Source/RHI/Scope.cpp
    Source/RHI/Scope.h
    Source/RHI/ShaderResourceGroup.cpp
    Source/RHI/ShaderResourceGroup.h
    Source/RHI/ShaderResourceGroupPool.cpp
    Source/RHI/ShaderResourceGroupPool.h
    Source/RHI/SwapChain.cpp
    Source/RHI/SwapChain.h
    Source/RHI/SystemComponent.cpp
    Source/RHI/SystemComponent.h
    Source/RHI/ArgumentBuffer.cpp
    Source/RHI/ArgumentBuffer.h
    Source/RHI/Util.cpp
    Source/RHI/Util.h
    Source/RHI/AliasedHeap.cpp
    Source/RHI/AliasedHeap.h
    Source/RHI/AliasingBarrierTracker.h
    Source/RHI/AliasingBarrierTracker.cpp
    Source/RHI/TransientAttachmentPool.cpp
    Source/RHI/TransientAttachmentPool.h
    Source/RHI/Query.cpp
    Source/RHI/Query.h
    Source/RHI/QueryPool.cpp
    Source/RHI/QueryPool.h
    Source/RHI/NullDescriptorManager.cpp
    Source/RHI/NullDescriptorManager.h
    Source/RHI/MetalView.h
    Source/RHI/MetalView.mm
    Source/RHI/MetalViewController.h
    Source/RHI/MetalViewController.mm
)
