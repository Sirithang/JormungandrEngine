#pragma once

extern "C"
{
	#include <lua.h>
}

namespace jormungandr
{
	namespace scriptimpl
	{
		int setPosition(lua_State *L);
	}
}