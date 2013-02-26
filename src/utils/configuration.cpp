#include "utils/configuration.h"
#include "utils/utils.h"

#include <string.h>

using namespace jormungandr;
using namespace jormungandr::configuration;

Configuration jormungandr::g_Configuration;

//-----

void handleWindowToken(const char* p_Buffer, jsmntok_t* tokens, int p_Number);

//------

void jormungandr::configuration::loadFrom(const char* p_File)
{
    jsmntok_t tokens[256];

    char buffer[10000];

    if(!jormungandr::utils::getFileContent(p_File, buffer, 10000))
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

                if(0 == strncmp("window", buffer + tokens[current].start, tokens[current].end - tokens[current].start))
                {
                    handleWindowToken(buffer, tokens + (current + 1), tokens[current].size);
                }

                current += size;
            }
        }
    }
}

//*****************************************************

void handleWindowToken(const char* p_Buffer, jsmntok_t* tokens, int p_Number)
{
    unsigned int i = 0;
    while(i < p_Number)
    {
        //key cmp
        if(0 == strncmp("width", p_Buffer + tokens[i].start, tokens[i].end - tokens[i].start))
        {
            char val[10];
            strncpy(val, p_Buffer + tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
            jormungandr::g_Configuration._width = atoi(val);

            i+=2;
        }
        else if(0 == strncmp("height", p_Buffer + tokens[i].start, tokens[i].end - tokens[i].start))
        {
            char val[10];
            strncpy(val, p_Buffer + tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
            jormungandr::g_Configuration._height = atoi(val);

            i+=2;
        }
    }
}