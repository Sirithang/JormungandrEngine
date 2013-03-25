#pragma once

#include "core/component/transform.h"
#include "core/manager.h"

#include <set>
#include <vector>
#include <stdint.h>

namespace jormungandr
{
	class TransformManager : public Manager<component::Transform>
	{
	public:
		std::vector<uint32_t> _toSync;
		uint32_t _nbToSync;

	protected:
		void onInit();
		void onCreate(uint32_t id);
	};

	namespace transformmanager
	{
		inline void toSync(TransformManager& p_Manager, uint32_t p_Transform)
		{
			if(p_Manager._toSync.size() >= p_Manager._toSync.capacity())
			{
				p_Manager._toSync.reserve(p_Manager._toSync.size() + 512);
			}

			p_Manager._toSync.push_back(p_Transform);
		}

		void sync(TransformManager& p_Manager);
	}
}