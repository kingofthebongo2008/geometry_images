#pragma once

#include <d3d12.h>
#include <wrl/client.h>

namespace dx12
{
	class moveable
	{
		protected:

		moveable() = default;
		~moveable() = default;
	

		private:
			moveable(const moveable&) = delete;
			moveable& operator=(const moveable&) = delete;
	};

	class fence_event : moveable
	{
		public:

		fence_event();
		~fence_event();
		operator HANDLE() const { return m_handle;}
		private:

		HANDLE m_handle = 0;
	};
}

namespace dx12
{
	using namespace Microsoft::WRL;

	using device						= ID3D12Device1;
	using device_ptr					= ComPtr<ID3D12Device1>;

    using resource                      = ID3D12Resource;
    using resource_ptr                  = ComPtr<ID3D12Resource>;

	using heap							= ID3D12Heap;
	using heap_ptr						= ComPtr<ID3D12Heap>;

    using descriptor_heap               = ID3D12DescriptorHeap;
    using descriptor_heap_ptr           = ComPtr<ID3D12DescriptorHeap>;

	using fence							= ID3D12Fence;
	using fence_ptr						= ComPtr<ID3D12Fence>;

	using command_list					= ID3D12CommandList;
	using command_list_ptr				= ComPtr<ID3D12CommandList>;

	using graphics_command_list			= ID3D12GraphicsCommandList1;
	using graphics_command_list_ptr		= ComPtr<ID3D12GraphicsCommandList1>;

	using command_allocator				= ID3D12CommandAllocator;
	using command_allocator_ptr			= ComPtr<ID3D12CommandAllocator>;

	using direct_command_allocator		= command_allocator;
	using direct_command_allocator_ptr  = command_allocator_ptr;
	using compute_command_allocator		= command_allocator;
	using compute_command_allocator_ptr = command_allocator_ptr;
	using copy_command_allocator		= command_allocator;
	using copy_command_allocator_ptr	= command_allocator_ptr;

	using command_queue					= ID3D12CommandQueue;
	using command_queue_ptr				= ComPtr<ID3D12CommandQueue>;

	using direct_command_queue			= command_queue;
	using direct_command_queue_ptr		= command_queue_ptr;
	using compute_command_queue			= command_queue;
	using compute_command_queue_ptr		= command_queue_ptr;
	using copy_command_queue			= command_queue;
	using copy_command_queue_ptr		= command_queue_ptr;

	using cpu_descriptor_handle			= D3D12_CPU_DESCRIPTOR_HANDLE;
	using gpu_descriptor_handle			= D3D12_GPU_DESCRIPTOR_HANDLE;

	using resource_barrier				= D3D12_RESOURCE_BARRIER;

	using root_signature_deserializer		= ID3D12RootSignatureDeserializer;
	using root_signature_deserializer_ptr	= ComPtr<ID3D12RootSignatureDeserializer>;

	using root_signature				= ID3D12RootSignature;
	using root_signature_ptr			= ComPtr<ID3D12RootSignature>;

	heap_ptr							make_upload_constant_heap(device* d, size_t size);
	heap_ptr							make_upload_buffer_heap(device* d, size_t size);

	fence_ptr							make_fence(device* d, uint64_t initial_value = 0);
	
	direct_command_queue_ptr			make_direct_command_queue(device* d);
	copy_command_queue_ptr				make_copy_command_queue(device* d);
	compute_command_queue_ptr			make_compute_command_queue(device* d);

	direct_command_allocator_ptr		make_direct_command_allocator(device* d);
	compute_command_allocator_ptr		make_compute_command_allocator(device* d);
	copy_command_allocator_ptr			make_copy_command_allocator(device* d);

    graphics_command_list_ptr           make_graphics_command_list(device*d, direct_command_allocator* r);
    
    descriptor_heap_ptr					make_shader_resources_descriptor_heap(device* d, uint32_t descriptor_count);
    descriptor_heap_ptr					make_render_targets_descriptor_heap(device* d, uint32_t descriptor_count);
    descriptor_heap_ptr					make_depth_stencil_descriptor_heap(device* d, uint32_t descriptor_count);
 
    device_ptr							make_device();

	root_signature_deserializer_ptr		make_root_signature_deserializer(const void* byte_code, size_t byte_code_size);


	void set_resource_barrier(graphics_command_list* r, resource_barrier b);
}