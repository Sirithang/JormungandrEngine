#pragma once

#include "utils/logger.h"
#include "jsmn/jsmn.h"

#include <stdio.h>

namespace jormungandr
{
    namespace utils
    {
        //just wrap the call to print if an error is detected
        bool parseJSON(const char* p_String, jsmntok_t* p_Tokens, unsigned int p_Number);

        //caller must assure that buffer is big enought. Call the std::string version for a computed size version.
        bool getFileContent(const char* p_File,char* p_Buffer, unsigned int p_BufferSize);
    }
}

//**********************************************************************

inline bool jormungandr::utils::parseJSON(const char* p_String, jsmntok_t* p_Tokens, unsigned int p_Number)
{
    jsmn_parser parser;

    jsmn_init(&parser);

    jsmnerr_t r = jsmn_parse(&parser, p_String, p_Tokens, p_Number);

    if(r == JSMN_ERROR_INVAL)
    {
        logger::error("Invalid Json File");
    }
    else if(r == JSMN_ERROR_PART)
    {
        logger::error("Json not ended File");
    }
    else if(r == JSMN_ERROR_NOMEM)
    {
        logger::error("Not enought memory");
    }

    if(r != JSMN_SUCCESS)
    {
        logger::error(p_String);
        return false;
    }

    return true;
}

//*************************************************************************

inline bool jormungandr::utils::getFileContent(const char* p_File, char* p_Buffer, unsigned int p_BufferSize)
{
    FILE * f;

    f = fopen(p_File, "rb");

    if(!f)
    {
        jormungandr::logger::error(p_File);
        jormungandr::logger::error("can't open file.");
        return false;
    }

    // obtain file size:
    fseek (f , 0 , SEEK_END);
    unsigned int size = ftell (f);
    rewind (f);

    if(size >= p_BufferSize)
    {
        jormungandr::logger::error(p_File);
        jormungandr::logger::error("error reading : buffer too small");
        return false;
    }

    fread((void*)p_Buffer, sizeof(char), size, f);
    
    p_Buffer[size] = '\0';

    fclose(f);

    return true;
}