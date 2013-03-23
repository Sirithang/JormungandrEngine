#pragma once

#include "core/entity_types.h"

namespace jormungandr
{
	namespace message
	{
		enum MessageType
		{
			UNKNOWN = 0,
			ENTITY_CHANGED
		};

		struct Message;
	}
}