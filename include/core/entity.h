#pragma once

#include "core/component_types.h"
#include "core/message/message.h"
#include "vector3.h"

#include <map>

namespace jormungandr
{
	struct Entity
	{
		uint32_t _id;

		std::multimap<component::ComponentType, uint32_t> _components;
		uint32_t _transform;
	};

	namespace manager
	{
		void init(Entity& p_Entity, uint32_t p_ID);
	}

	namespace entity
	{
		uint32_t addComponent(uint32_t p_Entity, component::ComponentType p_Type);

		void sendMessage(Entity& p_Sender, message::Message* p_Message);
	}
}