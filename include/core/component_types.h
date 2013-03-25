#pragma once

#include "core/entity_types.h"

namespace jormungandr
{
    struct Component;

    namespace component
    {
		enum ComponentType
		{
			TRANSFORM,
			RENDERER,
			SCRIPT,
			SOUNDSOURCE,
			SOUNDLISTENER
		};

		struct Transform;
        struct Renderer;
        struct Script;
        struct SoundSource;
        struct SoundListener;
    }
}
