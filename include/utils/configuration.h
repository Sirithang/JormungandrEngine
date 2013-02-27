#pragma once

#include "configuration_type.h"

namespace jormungandr
{
    namespace configuration
    {
        void init(Configuration& p_Config);
        void loadFrom(const char* p_File);
    }
}