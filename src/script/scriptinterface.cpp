#include "script/scriptinterface.h"

#include "core/scene.h"
#include "core/engine.h"
#include "core/manager/transformmanager.h"

#include "core/component/transform.h"
#include "core/entity.h"

#include "utils/logger.h"

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <stdint.h>

using namespace jormungandr;
using namespace jormungandr::scriptimpl;

int scriptimpl::setPosition(lua_State *L)
{
	double x =  luaL_checknumber(L, 1);
	double y = luaL_checknumber(L, 2);

	char buffX[10];
	char buffY[10];

	itoa(x, buffX, 10);
	itoa(y, buffY, 10);

	lua_pushstring(L, "this");
	lua_gettable(L, LUA_REGISTRYINDEX);

	uint32_t ent = lua_tointeger(L, -1);

	jormungandr::component::transform::setPosition(jormungandr::g_engine->_current->_datas[ent]._transform, alfar::vector3::create(x,y,1));

	return 0;
}