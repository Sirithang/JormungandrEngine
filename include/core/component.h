#pragma once

#include "core/entity_type.h"

#include <vector>
#include <stdint.h>

namespace jormungandr
{
    class Component
    {
    private:
        static std::vector<Component*> g_Components;

        Entity      _owningEntity;
        uint16_t    _typeGUID;

    public:
        virtual void update() = 0;
    };
}