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
		bool getFileContent(const char* p_File, const char* p_Buffer, unsigned int p_BufferSize);
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

inline bool getFileContent(const char* p_File, char* p_Buffer, unsigned int p_BufferSize)
{
	FILE * f;

	f = fopen(p_File, "r");

	if(!f)
	{
		jormungandr::logger::error(p_File);
		jormungandr::logger::error("can't open file.");
		return false;
	}

	size_t number = fread((void*)p_Buffer, sizeof(unsigned char), p_BufferSize, f);

	if(number == p_BufferSize)
	{
		jormungandr::logger::error(p_File);
		jormungandr::logger::error("error reading : buffer too small");
	}

	return true;
}