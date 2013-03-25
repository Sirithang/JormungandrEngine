#pragma once

#include "core/component.h"

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <sys/stat.h>

namespace jormungandr
{
	namespace component
	{
		struct Script : public Component
		{
			lua_State* _luaState;
			time_t	_fileTime; //file time for modification watch
			char	_file[500];
		};

		namespace script
		{
			void setScriptFile(uint32_t p_ID, const char* p_File);

			void update(Script& p_Script);
		}
	}

	namespace manager
	{
		void init(component::Script& p_Script, uint32_t p_ID);
	}
}