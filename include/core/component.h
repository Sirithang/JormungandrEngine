#pragma once

#include "core/component_types.h"

#include <vector>
#include <stdint.h>

namespace jormungandr
{
    struct Component
    {
		component::ComponentType _type;
		uint32_t				 _owner;
		uint32_t				 _id;
    };
}