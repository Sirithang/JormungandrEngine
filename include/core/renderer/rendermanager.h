#pragma once

#include "vector3.h"
#include "core/component/renderer.h"
#include "core/manager.h"

#include <stdint.h>
#include <list>
#include <vector>

namespace jormungandr
{

	namespace rendermanager
	{
		union RenderKey
		{
			struct info
			{
				uint16_t materialID;
				uint16_t padding;
			} parts;
			uint32_t key;
		};

		struct RenderCommand
		{
			RenderKey _renderkey;

			component::renderer::Vertex	_vertex[6];
		};
	}

	class RenderManager : public Manager<component::Renderer>
	{
	public:
		std::vector<rendermanager::RenderCommand>	_commands;

	protected:
		void onInit();
		void onCreate(uint32_t p_ID);
	};
	
	namespace rendermanager
	{
		void update(RenderManager& p_Manager);

		void addCommand( RenderManager& p_Manager, component::Renderer& p_Renderer);
		void render(RenderManager& p_Manager);
	}
}