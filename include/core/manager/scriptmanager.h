#pragma once

#include "core/component/script.h"
#include "core/manager.h"

namespace jormungandr
{
	class ScriptManager : public Manager<component::Script>
	{
	protected:
		void onInit();
		void onCreate(uint32_t p_ID);
	};

	namespace scriptmanager
	{
		void update(ScriptManager& p_Manager);
	}
}