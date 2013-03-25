#include "core/manager/scriptmanager.h"

using namespace jormungandr;


void ScriptManager::onInit()
{

}

//==========================================

void ScriptManager::onCreate(uint32_t p_ID)
{

}

//===========================================

void scriptmanager::update(ScriptManager& p_Manager)
{
	uint32_t size = p_Manager._datas.size();

	for(uint32_t i = 0; i < size; ++i)
	{
		jormungandr::component::script::update(p_Manager._datas.at(i));
	}
}