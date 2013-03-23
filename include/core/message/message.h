#pragma once
#include "core/message/message_types.h"
#include <stdint.h>

namespace jormungandr
{
	namespace message
	{
		struct Message
		{
			MessageType _type;
			uint32_t	_objectID;//sender
		};
	}
}