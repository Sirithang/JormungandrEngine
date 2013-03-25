#include "core/component/script.h"
#include "utils/logger.h"

#include "core/manager/scriptmanager.h"
#include "core/engine.h"

#include "script/scriptinterface.h"

using namespace jormungandr;
using namespace jormungandr::component;


//*************************************************************


void manager::init(Script& p_Script, uint32_t p_ID)
{
	p_Script._id = p_ID;
	p_Script._type = component::ComponentType::SCRIPT;

	p_Script._luaState = lua_open();

	luaL_openlibs(p_Script._luaState);
}

//=====================================================


inline void loadFile(Script& p_Script, const char* p_File)
{

}


//----

void script::setScriptFile(uint32_t p_ID, const char* p_File)
{
	int error = 0;
	Script& scr = jormungandr::g_engine->_currentScriptManager->_datas.at(p_ID);

	struct _stat info;
	int result = _stat( p_File, &info );

	scr._fileTime = info.st_mtime;

	strcpy(scr._file, p_File);

	error = luaL_loadfile(scr._luaState, p_File);

	if(error != 0)
	{
		logger::error("LUA error: ");
		logger::error(lua_tostring(scr._luaState, -1));
		lua_pop(scr._luaState, 1); 
	}
	else
	{
		lua_pcall(scr._luaState, 0,0,0);

		lua_pushstring(scr._luaState, "this");
		lua_pushinteger(scr._luaState, scr._owner);
		lua_settable(scr._luaState, LUA_REGISTRYINDEX);

		lua_pushcfunction(scr._luaState, jormungandr::scriptimpl::setPosition);
		lua_setglobal(scr._luaState, "setPosition");

		lua_getglobal(scr._luaState, "onCreate");
		
		if (lua_pcall(scr._luaState, 0, 0, 0) != 0)
		{
			logger::error("error running function");
			logger::error(lua_tostring(scr._luaState, -1));
			lua_pop(scr._luaState, 1);
		}
	}
}

//=================================================================

void script::update(Script& p_Script)
{
	struct _stat info;
	int result = _stat( p_Script._file, &info );

	if( p_Script._fileTime != info.st_mtime)
	{
		int error = luaL_loadfile(p_Script._luaState, p_Script._file);

		if(error != 0)
		{
			logger::error("LUA error: ");
			logger::error(lua_tostring(p_Script._luaState, -1));
			lua_pop(p_Script._luaState, 1); 
		}

		lua_pcall(p_Script._luaState, 0, 0, 0);
	}

	lua_getglobal(p_Script._luaState, "onUpdate");
	
	if (lua_pcall(p_Script._luaState, 0, 0, 0) != 0)
	{
		logger::error("error running function");
		logger::error(lua_tostring(p_Script._luaState, -1));
		lua_pop(p_Script._luaState, 1);
	}
}