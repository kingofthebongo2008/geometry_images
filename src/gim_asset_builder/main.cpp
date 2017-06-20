#include "pch.h"

#include <asset/geometry_image.h>
#include <asset/geometry_image_serializer.h>


#include <regex>
#include <iostream>
#include <fstream>
#include <assert.h>

enum state : uint32_t
{
	vertex,
	vertex_index,
	vertex_index_x,
	vertex_index_y,
	vertex_index_z,
	left_brace,
	normal_text,
	normal_equals,
	normal_left_bracket,
	normal_x,
	normal_y,
	normal_z,
	normal_right_bracket,
	uv_text,
	uv_equals,
	uv_left_bracket,
	uv_x,
	uv_y,
	ub_right_bracket,
	right_brace
};

std::regex get_regular_expresion(  state s )
{
	static const std::regex states[] =
	{
		std::regex("Vertex"),
		std::regex("[0-9]+"),
		std::regex("^-?[0-9]+.[0-9]+"),
		std::regex("^-?[0-9]+.[0-9]+"),
		std::regex("^-?[0-9]+.[0-9]+"),
		std::regex("\\{"),
		std::regex("normal"),
		std::regex("="),
		std::regex("\\("),
		std::regex("^-?[0-9]+.[0-9]+"),
		std::regex("^-?[0-9]+.[0-9]+"),
		std::regex("^-?[0-9]+.[0-9]+"),
		std::regex("\\)"),
		std::regex("uv"),
		std::regex("="),
		std::regex("\\("),
		std::regex("^-?[0-9]+.[0-9]+"),
		std::regex("^-?[0-9]+.[0-9]+"),
		std::regex("\\)"),
		std::regex("\\}")
	};

	return states[s];
}

void test(const std::string& s2)
{
	std::string s = "Vertex 1  0.157842 0.841054 0.344725  { normal = ( 0.823746 -0.382964 -0.418068 ) uv = ( 0.000977 0.000977 ) }";
	
	//std::regex regex("Vertex\\s?\\S?");
	//std::cout << std::regex_match(str, regex) << std::endl;
	//std::regex word_regex("\\(^Vertex\\s+\\d+\\)\\s+\\d+.\\d+");

	std::regex word_regex("\\S+");
	auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
	auto words_end = std::sregex_iterator();

	state st = state::vertex;

	for (auto&& a = words_begin; a != words_end; ++a)
	{
		auto reg = get_regular_expresion(st);

		if ( !std::regex_match(a->str(), reg) )
		{
			__debugbreak();
		}
		else
		{
			st = static_cast<state>(st + 1);
			//__debugbreak();
		}
	}

	assert(st == state::right_brace);
}

int main()
{
	std::fstream f("gim_data\\bunny.p65.gim257.m", std::ios::in);

	if (f.good())
	{
		std::string s;
		if (std::getline(f, s))
		{
			test(s);
		}
	}
}

/*
{
	asset::geometry_image g;

	g.m_indices = std::unique_ptr< asset::index[] >(new asset::index[3]);
	g.m_indices_size = 3;

	g.m_position = std::unique_ptr< asset::point3[] >(new asset::point3[3]);
	g.m_positions_size = 3;

	g.m_uv = std::unique_ptr< asset::point2[] >(new asset::point2[2]);
	g.m_uv_size = 2;

	{
		g.m_position[0] = { 1.0f, 0.0f, 0.0f };
		g.m_position[1] = { 0.0f, 1.0f, 0.0f };
		g.m_position[2] = { 0.0f, 0.0f, 1.0f };
	}

	{
		g.m_uv[0] = { 1.0f, 0.0f };
		g.m_uv[1] = { 0.0f, 1.0f };
	}

	{
		g.m_indices[0] = { 0 };
		g.m_indices[1] = { 1 };
		g.m_indices[2] = { 2 };
	}

	asset::serializer f(L"test.bin");
	serialize(&f, &g);
}
{
	asset::geometry_image g;
	asset::deserializer f(L"test.bin");

	asset::deserialize(&f, &g);
}
*/