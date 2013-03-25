#pragma once

#include "data/asset.h"
#include "data/assetdatabase.h"
#include "utils/logger.h"
#include <stdint.h>

namespace jormungandr
{
	namespace data
	{
		struct Texture : public Asset
		{
			uint32_t _hardwareID;
		};
	}
}