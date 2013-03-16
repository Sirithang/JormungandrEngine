#pragma once

#include <vector>
#include <list>
#include <stdint.h>

#include "mat4x4.h"

namespace jormungandr
{
	namespace data
	{
		struct Material
		{
			uint16_t _hardwareID;
		};

		extern std::vector<Material> g_Materials;
		extern std::list<uint32_t> g_FreeID;
		extern int g_TopID;

		namespace material
		{
			uint32_t create();
			bool loadShader(uint32_t p_ID, const char* p_File);
			bool compile(uint32_t p_ID);
			void bind(uint32_t p_ID);

			void setUniform(uint32_t p_Location, const alfar::Matrix4x4& p_Matrix);
		}
	}
}