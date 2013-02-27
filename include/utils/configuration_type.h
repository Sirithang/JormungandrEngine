#pragma once

#include <map>

namespace jormungandr
{
    struct Configuration
    {
        unsigned int _height, _width;
        bool _fullscreen;
    };

    extern Configuration config;
}