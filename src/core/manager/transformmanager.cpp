#include "core/manager/transformmanager.h"

#include "core/engine.h"
#include "core/scene.h"

#include "mat4x4.h"

#include <algorithm>

using namespace jormungandr;


//=================================================================

void TransformManager::onInit()
{
	_toSync.clear();
	_toSync.reserve(1024);

	uint32_t id = createData(); //root node parent of all
}

//=================================================================

void TransformManager::onCreate(uint32_t p_ID)
{
	
}

//=================================================================

void transformmanager::sync(TransformManager& p_Manager)
{
	/*uint32_t size = p_Manager._toSync.size();
	for(uint32_t i = 0; i < size; ++i)
	{
		component::Transform& transform = p_Manager._datas[p_Manager._toSync.at(i)];

		transform._matrix = alfar::mat4x4::translation(transform._position);

		if(transform._renderer != -1)
		{
			jormungandr::g_engine->_current->_renderManager._datas[transform._renderer]._transform = transform._matrix;
		}
	}*/

	std::sort(p_Manager._datas.begin(), p_Manager._datas.end());

	uint32_t size = p_Manager._datas.size();

	for(uint32_t i = 1; i < size; i++)
	{
		component::Transform& tr  = p_Manager._datas.at(i);

		tr._matrix = alfar::mat4x4::translation(tr._position);
		tr._matrix = alfar::mat4x4::mul(tr._matrix, p_Manager._datas.at(tr._parent)._matrix);

		if(tr._renderer != -1)
		{
			jormungandr::g_engine->_current->_renderManager._datas.at(tr._renderer)._transform = tr._matrix;
		}
	}


	//p_Manager._toSync.clear();
}