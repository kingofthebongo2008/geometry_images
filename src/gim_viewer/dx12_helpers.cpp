#include "pch.h"

#include "dx12_helpers.h"
#include "com_error.h"

namespace dx12
{
	fence_event::fence_event()
	{
		m_handle = CreateEvent(nullptr, FALSE, FALSE, nullptr);

		if (m_handle == nullptr)
		{
			throw_if_failed(HRESULT_FROM_WIN32(GetLastError()));
		}
	}

	fence_event::~fence_event()
	{
		if (m_handle)
		{
			CloseHandle(m_handle);
		}
	}

	device_ptr make_device()
	{
		device_ptr r;
		throw_if_failed(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&r)));
		return r;
	}

	heap_ptr   make_upload_constant_heap(device* d, size_t size)
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

	heap_ptr   make_upload_buffer_heap(device* d, size_t size)
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

	fence_ptr  make_fence(device* d, uint64_t initial_value)
	{
		fence_ptr r;
		throw_if_failed(d->CreateFence(initial_value, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&r)));
		return r;
	}

	direct_command_queue_ptr make_direct_command_queue(device* d)
	{
		direct_command_queue_ptr r;
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		throw_if_failed(d->CreateCommandQueue(&desc, IID_PPV_ARGS(&r)));
		return r;
	}

	copy_command_queue_ptr make_copy_command_queue(device* d)
	{
		copy_command_queue_ptr r;
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		throw_if_failed(d->CreateCommandQueue(&desc, IID_PPV_ARGS(&r)));
		return r;
	}

	compute_command_queue_ptr make_compute_command_queue(device* d)
	{
		compute_command_queue_ptr r;
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		throw_if_failed(d->CreateCommandQueue(&desc, IID_PPV_ARGS(&r)));
		return r;
	}

	direct_command_allocator_ptr make_direct_command_allocator(device* d)
	{
		direct_command_allocator_ptr r;
		throw_if_failed(d->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&r)));
		return r;
	}

	compute_command_allocator_ptr make_compute_command_allocator(device* d)
	{
		compute_command_allocator_ptr r;
		throw_if_failed(d->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COMPUTE, IID_PPV_ARGS(&r)));
		return r;
	}

	copy_command_allocator_ptr make_copy_command_allocator(device* d)
	{
		copy_command_allocator_ptr r;

		throw_if_failed(d->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COPY, IID_PPV_ARGS(&r)));
		return r;
	}

    graphics_command_list_ptr make_graphics_command_list(device*d, direct_command_allocator* alloc)
    {
        graphics_command_list_ptr r;
        throw_if_failed(d->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT, alloc, nullptr, IID_PPV_ARGS(&r)));
        return r;
    }
}

