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
			ANIMATION,
			SOUNDSOURCE,
			SOUNDLISTENER
		};

		struct Transform;
        struct Renderer;
        struct Animation;
        struct SoundSource;
        struct SoundListener;
    }
}
