#include "data/texture.h"

#include "utils/logger.h"

#include <gl/glew.h>

#include <png.h>
#include <zlib.h>
#include <malloc.h>

using namespace jormungandr;
using namespace jormungandr::data;

template<> 
bool AssetLoader<Texture>::_internalCreate(Texture& p_Created, const char* p_File)
{
	logger::log("loading png");
	png_image image;

	memset(&image, 0, (sizeof image));
	image.version = PNG_IMAGE_VERSION;

	/* The first argument is the file to read: */
	if (png_image_begin_read_from_file(&image, p_File))
	{
		png_bytep buffer;

		image.format = PNG_FORMAT_RGBA;
		buffer = (png_bytep)malloc(PNG_IMAGE_SIZE(image));

		if (buffer != NULL &&
			png_image_finish_read(&image, NULL, buffer,
			0, NULL))
		{
			glGenTextures(1, &p_Created._hardwareID);
			glBindTexture(GL_TEXTURE_2D, p_Created._hardwareID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			glBindTexture(GL_TEXTURE_2D, 0);

			return true;
		}
		else
		{
			logger::error("PNG error : ");
			logger::error(image.message);
		}

		free(buffer);
	}

	return false;
}