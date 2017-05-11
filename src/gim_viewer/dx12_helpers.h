#pragma once

#include <d3d12.h>
#include <wrl/client.h>

namespace dx12
{
	using namespace Microsoft::WRL;

	using device	 = ID3D12Device1;
	using device_ptr = ComPtr<ID3D12Device1>;

	using heap		 = ID3D12Heap;
	using heap_ptr	 = ComPtr<ID3D12Heap>;

	using fence		 = ID3D12Fence;
	using fence_ptr  = ComPtr<ID3D12Fence>;

	using command_list = ID3D12CommandList;
	using command_list_ptr = ComPtr<ID3D12CommandList>;

	using graphics_command_list = ID3D12GraphicsCommandList1;
	using graphics_command_list_ptr = ComPtr<ID3D12GraphicsCommandList1>;

	using command_allocator	    = ID3D12CommandAllocator;
	using command_allocator_ptr = ComPtr<ID3D12CommandAllocator>;

	using direct_command_allocator	= command_allocator;
	using copy_command_allocator	= command_allocator;

	using command_queue				= ID3D12CommandQueue;
	using command_queue_ptr			= ComPtr<ID3D12CommandQueue>;

	heap_ptr   create_upload_constant_heap(device* d, size_t size);
	heap_ptr   create_upload_buffer_heap(device* d, size_t size);

	fence_ptr  create_fence(device* d, uint64_t initial_value = 0);
	
	command_queue_ptr create_direct_command_queue(device* d);
	command_queue_ptr create_copy_command_queue(device* d);
	command_queue_ptr create_compute_command_queue(device* d);

	command_queue_ptr create_command_allocator(device* d);

}