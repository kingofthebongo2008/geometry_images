#pragma once

#include <cstdint>
#include <memory>

#include <asset/geometry_image_noncopyable.h>

namespace asset
{
	struct vector3
	{
		float m_x;
		float m_y;
		float m_z;
	};

	struct point3
	{
		float m_x;
		float m_y;
		float m_z;
	};

	struct point2
	{
		float m_x;
		float m_y;
	};

	struct index
	{
		uint32_t m_index;
	};

	struct geometry_image : non_copyable
	{
		std::unique_ptr<point3[]> m_position;
		std::unique_ptr<point2[]> m_uv;
		std::unique_ptr<index[]>  m_indices;

		uint32_t	m_positions_size;
		uint32_t	m_uv_size;
		uint32_t	m_indices_size;
	};

	void serialize(class serializer* s, geometry_image* g);
	void deserialize(class deserializer* s, geometry_image* g);
}

