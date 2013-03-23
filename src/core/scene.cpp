#include "core/scene.h"
#include "core/entity.h"

using namespace jormungandr;

void Scene::onInit()
{
	_renderManager.init();
	_transformManager.init();
}

//======================================================

void Scene::onCreate(uint32_t p_ID)
{
}

//=======================================================

void scene::update(Scene& p_Scene)
{
	jormungandr::transformmanager::sync(p_Scene._transformManager);

	jormungandr::rendermanager::update(p_Scene._renderManager);

	jormungandr::rendermanager::render(p_Scene._renderManager);
}