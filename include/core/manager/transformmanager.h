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
		std::set<uint32_t> _toSync;

	protected:
		void onInit();
		void onCreate(uint32_t id);
	};

	namespace transformmanager
	{
		inline void toSync(TransformManager& p_Manager, uint32_t p_Transform)
		{
			p_Manager._toSync.insert(p_Transform);
		}

		void sync(TransformManager& p_Manager);
	}
}