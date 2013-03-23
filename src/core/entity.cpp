#include "core/entity.h"

#include "core/component/renderer.h"

#include "core/renderer/rendermanager.h"
#include "core/engine.h"
#include "core/scene.h"

using namespace jormungandr;

void manager::init(Entity& p_Entity, uint32_t p_ID)
{
	p_Entity._components.clear();

	p_Entity._id = p_ID;

	uint32_t id = jormungandr::g_engine->_current->_transformManager.createData();
	jormungandr::g_engine->_current->_transformManager._datas.at(id)._owner = p_ID;

	p_Entity._components.insert(std::pair<component::ComponentType, uint32_t>(component::ComponentType::TRANSFORM, id));

	p_Entity._transform = id;
}

//=====================================

uint32_t entity::addComponent(uint32_t p_Entity, component::ComponentType p_Type)
{
	uint32_t id = -1;

	switch(p_Type)
	{
	case component::ComponentType::RENDERER:
		id = jormungandr::g_engine->_current->_renderManager.createData();
		jormungandr::g_engine->_current->_renderManager._datas[id]._owner = p_Entity;
		break;
	default:
		break;
	}

	if(id >= 0)
	{
		jormungandr::g_engine->_current->_datas[p_Entity]._components.insert(std::pair<component::ComponentType, uint32_t>(p_Type, id));
	}

	return id;
}

//=======================================

void entity::sendMessage(Entity& p_Sender, message::Message* p_Message)
{
	/*std::list<Component*>::iterator it = p_Sender._components.begin();

	while(it != p_Sender._components.end())
	{
		(*it)->handleMessage(p_Message);
		++it;
	}*/
}