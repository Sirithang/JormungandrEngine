#pragma once

#include <stdint.h>

namespace jormungandr
{

	struct RenderCommand
	{
		union
		{
			struct info
			{
				uint16_t materialID;
			};
			uint32_t key;
		};


	};

	struct RendererManager
	{
	};
}