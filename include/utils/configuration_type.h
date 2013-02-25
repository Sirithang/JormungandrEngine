#pragma once

namespace jormungandr
{
	struct Configuration
	{
		bool _fullscreen;
		unsigned int _height, _width;
	};

	const Configuration g_Configuration;
}