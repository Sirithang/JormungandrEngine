#include "core/engine.h"
#include "core/scene.h"

using namespace jormungandr;

Engine* jormungandr::g_engine = new Engine();

Scene& engine::addScene()
{
	g_engine->_scenes.resize(g_engine->_scenes.size() + 1);

	g_engine->_current = &g_engine->_scenes.back();

	g_engine->_current->init();

	return g_engine->_scenes.back();
}

//======================================

void engine::update()
{
	jormungandr::scene::update(*g_engine->_current);
}