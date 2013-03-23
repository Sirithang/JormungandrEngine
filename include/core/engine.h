#pragma once

#include "engine_types.h"

#include <stdint.h>
#include <list>

namespace jormungandr
{
	struct Engine
	{
		std::list<Scene> _scenes;
		Scene* _current;
	};

	extern Engine* g_engine;

	namespace engine
	{
		Scene& addScene();

		void update();
	}
}