#pragma once

#include <stdint.h>

namespace jormungandr
{
	namespace data
	{
		enum AssetType
		{
			TEXTURE,
			MATERIAL
		};

		struct Asset
		{
			uint32_t	_id;
			AssetType	_type;
		};
	}
}