#pragma once

#include <vector>
#include <list>
#include <stdint.h>

#include "data/asset.h"
#include "data/assetdatabase.h"
#include "utils/logger.h"
#include "mat4x4.h"

namespace jormungandr
{
	namespace data
	{
		struct Material : public Asset
		{
			uint16_t _hardwareID;
			uint32_t _samplers[4]; // 4sampler max.
			uint8_t	 _nbSampler;
		};


		//===============================================


		/*template<>
		Asset* AssetLoader<Material>::create(const char* p_File)
		{
			jormungandr::logger::log("Loading material with name :");
			jormungandr::logger::log(p_File);

			return NULL;
		}*/

		//================================================

		namespace material
		{
			uint32_t create();

			void init(Material& p_Material);

			bool loadShader(uint32_t p_ID, const char* p_File);
			bool compile(uint32_t p_ID);
			void bind(uint32_t p_ID);

			/**
			* p_Number is the sampler number to bound (0 to 3) 
			*/
			void addSampler(uint32_t p_ID, Texture* p_Sampler, uint8_t p_Number);

			void setUniform(uint32_t p_ID, const char* p_Name, const alfar::Matrix4x4& p_Matrix);
		}
	}
}