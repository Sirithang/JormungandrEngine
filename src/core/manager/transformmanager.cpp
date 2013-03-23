#include "core/manager/transformmanager.h"

#include "core/engine.h"
#include "core/scene.h"

#include "mat4x4.h"

using namespace jormungandr;


//=================================================================

void TransformManager::onInit()
{
	_toSync.clear();
}

//=================================================================

void TransformManager::onCreate(uint32_t p_ID)
{
	
}

//=================================================================

void transformmanager::sync(TransformManager& p_Manager)
{
	std::set<uint32_t>::iterator it = p_Manager._toSync.begin();
	std::set<uint32_t>::iterator end = p_Manager._toSync.end();

	while(it != end)
	{
		component::Transform& transform = p_Manager._datas[*it];

		transform._matrix = alfar::mat4x4::translation(transform._position);


		Entity& ent = jormungandr::g_engine->_current->_datas[transform._owner];
		
		std::multimap<component::ComponentType, uint32_t>::iterator d = ent._components.begin();
		std::multimap<component::ComponentType, uint32_t>::iterator e = ent._components.end();

		while(d != e)
		{
			switch((*d).first)
			{
			case component::ComponentType::RENDERER:
				jormungandr::g_engine->_current->_renderManager._datas[d->second]._transform = transform._matrix;
				break;
			default:
				break;
			}

			++d;
		}

		++it;
	}

	p_Manager._toSync.clear();
}