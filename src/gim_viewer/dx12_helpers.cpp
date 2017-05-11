#include "pch.h"

#include "dx12_helpers.h"
#include "com_error.h"

namespace dx12
{
	device_ptr create_device()
	{
		device_ptr r;
		throw_if_failed(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device1), reinterpret_cast<void**>(r.GetAddressOf())));
		return r;
	}

	heap_ptr   create_upload_constant_heap(device* d, size_t size)
	{
		heap_ptr r;

		D3D12_HEAP_PROPERTIES props = {};

		props.Type				 = D3D12_HEAP_TYPE_UPLOAD;

		D3D12_HEAP_DESC heap	= {};
		heap.SizeInBytes		= size;
		heap.Flags				= D3D12_HEAP_FLAG_NONE;
		heap.Properties			= props;

		throw_if_failed( d->CreateHeap(&heap, IID_PPV_ARGS(&r)) );

		return r;
	}

	heap_ptr   create_upload_buffer_heap(device* d, size_t size)
	{
		heap_ptr r;

		D3D12_HEAP_PROPERTIES props = {};

		props.Type = D3D12_HEAP_TYPE_UPLOAD;

		D3D12_HEAP_DESC heap = {};
		heap.SizeInBytes = size;
		heap.Flags = D3D12_HEAP_FLAG_NONE;
		heap.Properties = props;

		throw_if_failed(d->CreateHeap(&heap, IID_PPV_ARGS(&r)));
		return r;
	}

	fence_ptr  create_fence(device* d, uint64_t initial_value)
	{
		fence_ptr r;
		throw_if_failed(d->CreateFence( initial_value, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&r)));
		return r;
	}

	command_queue_ptr create_direct_command_queue(device* d)
	{
		command_queue_ptr r;
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		throw_if_failed( d->CreateCommandQueue(&desc, IID_PPV_ARGS(&r)));
		return r;
	}

	command_queue_ptr create_copy_command_queue(device* d)
	{
		command_queue_ptr r;
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		throw_if_failed(d->CreateCommandQueue(&desc, IID_PPV_ARGS(&r)));
		return r;
	}

	command_queue_ptr create_compute_command_queue(device* d)
	{
		command_queue_ptr r;
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		throw_if_failed(d->CreateCommandQueue(&desc, IID_PPV_ARGS(&r)));
		return r;
	}

	command_allocator_ptr create_direct_command_allocator(device* d)
	{
		
	}
}