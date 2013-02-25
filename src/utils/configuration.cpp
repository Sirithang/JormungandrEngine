#include "utils/configuration.h"
#include "utils/utils.h"

using namespace jormungandr::configuration;

void loadFrom(const char* p_File)
{
	jsmntok_t tokens[256];

	char buffer[10000];

	if(jormungandr::utils::getFileContent(p_File, buffer, 10000))
		return;

	if(jormungandr::utils::parseJSON(buffer, tokens, 256))
	{
		unsigned int current = 0;

		if(tokens[current].type != JSMN_OBJECT)
			return;

		++current;

		while(tokens[current].start != -1)
		{
			if(tokens[current].type == JSMN_OBJECT)
			{
				unsigned int size = tokens[current].size;

				++current;
				for(unsigned int i = 0; i < size; ++i)
				{
					char key[256];
					char value[256];
				}
			}
		}
	}
}