#include "pch.h"

#include <asset/geometry_image.h>
#include <asset/geometry_image_serializer.h>

namespace asset
{
	void serialize(class serializer* s, geometry_image* g)
	{
		s->write_bytes(&g->m_positions_size, sizeof(g->m_positions_size));
		s->write_bytes(g->m_position.get(), sizeof(point3) * g->m_positions_size);

		s->write_bytes(&g->m_uv_size, sizeof(g->m_uv_size));
		s->write_bytes(g->m_uv.get(), sizeof(point2) * g->m_uv_size);

		s->write_bytes(&g->m_indices_size, sizeof(g->m_indices_size));
		s->write_bytes(g->m_indices.get(), sizeof(index) * g->m_indices_size);
	}

	void deserialize(class deserializer* s, geometry_image* g)
	{
		{
			auto size = read_uint32_t(s);
			g->m_position = std::unique_ptr< point3[] >(new point3[size]);
			g->m_positions_size = size;
			s->read_bytes(g->m_position.get(), sizeof(point3) * size);
		}

		{
			auto size	= read_uint32_t(s);
			g->m_uv		= std::unique_ptr< point2[] >(new point2[size]);
			g->m_uv_size = size;
			s->read_bytes(g->m_uv.get(), sizeof(point2) * size);
		}

		{
			auto size = read_uint32_t(s);
			g->m_indices = std::unique_ptr< index[] >(new index[size]);
			g->m_indices_size = size;
			s->read_bytes(g->m_indices.get(), sizeof(index) * size);
		}
	}
}
