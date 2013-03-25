#pragma once

#include "renderer/rendermanager.h"
#include "manager/transformmanager.h"
#include "manager/scriptmanager.h"
#include "entity.h"

#include <stdint.h>
#include <vector>
#include <list>

namespace jormungandr
{
	class Scene : public Manager<Entity>
	{
	public:
		RenderManager	_renderManager;
		TransformManager _transformManager;
		ScriptManager	_scriptManager;

	protected:
		void onInit();
		void onCreate(uint32_t p_ID);
	};

	namespace scene
	{
		void	update(Scene& p_Scene);
	}
}