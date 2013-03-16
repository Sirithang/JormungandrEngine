#include "data/material.h"
#include "utils/utils.h"
#include "utils/logger.h"

#include <GL/glew.h>

using namespace jormungandr;
using namespace jormungandr::data;

std::vector<Material> jormungandr::data::g_Materials(64);
std::list<uint32_t> jormungandr::data::g_FreeID(32);
int jormungandr::data::g_TopID = 0;

uint32_t g_MaxMat = 64;

//********************************************************

uint32_t material::create()
{
	uint32_t id;
	
	if(g_FreeID.size() != 0)
	{
		id = g_FreeID.back();
		g_FreeID.pop_back();
	}
	else
	{
		id = g_TopID;
		g_TopID++;

		if(g_TopID == g_MaxMat)
		{
			g_MaxMat += 64;
			g_Materials.reserve(g_MaxMat);
		}
	}

	g_Materials[id]._hardwareID = glCreateProgram();

	glBindAttribLocation(g_Materials[id]._hardwareID, 0, "in_position");

	return id;
}

//********************************************************

bool material::loadShader(uint32_t p_ID, const char* p_File)
{
	char ext[3];
	strncpy(ext, p_File + (strlen(p_File) - 2), 2);
	ext[2] = '\0';

	uint32_t id;

	char buffer[65535];
	if(!jormungandr::utils::getFileContent(p_File, buffer, 65535))
	{
		jormungandr::logger::error("Couldn't open the shader :");
		jormungandr::logger::error(p_File);
		return false;
	}

	if(strcmp(ext,"vs") == 0)
	{
		id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if(strcmp(ext, "fs") == 0)
	{
		id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else
	{
		jormungandr::logger::error("Couldn't guess the type of shader : ");
		jormungandr::logger::error(p_File);
		return false;
	}

	const char* b = buffer;
	glShaderSource(id, 1, &b, NULL);
	glCompileShader(id);

	int lCompilationStatus;
	glGetShaderiv(id, GL_COMPILE_STATUS, &lCompilationStatus);

	if(lCompilationStatus == GL_FALSE)
	{
		int infologLength = 0;

		int charsWritten  = 0;
		char *infoLog;

		glGetShaderiv(id, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(id, infologLength, &charsWritten, infoLog);

			jormungandr::logger::error("Error in shader compilation for : ");
			jormungandr::logger::error(p_File);
			jormungandr::logger::error(infoLog);

			free(infoLog);
		}

		glDeleteShader(id);
		return false;
	}

	glAttachShader(g_Materials[p_ID]._hardwareID, id);

	return true;

}


//---------------------------------------------

bool material::compile(uint32_t p_ID)
{
	glLinkProgram(g_Materials[p_ID]._hardwareID);

	int iLinkStatus;
	glGetProgramiv(g_Materials[p_ID]._hardwareID, GL_LINK_STATUS, &iLinkStatus);
	if(!iLinkStatus == GL_TRUE)
	{
		jormungandr::logger::error("Linking of program failed");
		return false;
	}

	return true;
}

//--------------------------------------------

void material::bind(uint32_t p_ID)
{
	glUseProgram(g_Materials[p_ID]._hardwareID);
}

//--------------------------------------------

void material::setUniform(uint32_t p_Location, const alfar::Matrix4x4& p_Matrix)
{
	glUniform4fv(p_Location, sizeof(alfar::Matrix4x4), &p_Matrix.x.x);
}