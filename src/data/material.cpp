#include "data/material.h"
#include "utils/utils.h"
#include "utils/logger.h"
#include "data/texture.h"

#include <GL/glew.h>

using namespace jormungandr;
using namespace jormungandr::data;

//********************************************************

uint32_t material::create()
{

	uint32_t id = AssetLoader<Material>::_instance.create();
	
	Material& mat = AssetLoader<Material>::_instance._assets[id];

	material::init(mat);

	return id;
}

//********************************************************

void material::init(Material& p_Mat)
{
	p_Mat._hardwareID = glCreateProgram();

	glBindAttribLocation(p_Mat._hardwareID, 0, "in_position");
	glBindAttribLocation(p_Mat._hardwareID, 1, "in_uv");

	for(uint8_t i = 0; i < 4; ++i)
	{
		p_Mat._samplers[i] = 0;
	}
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

	glAttachShader(AssetLoader<Material>::_instance._assets[p_ID]._hardwareID, id);

	return true;

}


//---------------------------------------------

bool material::compile(uint32_t p_ID)
{
	Material& mat = AssetLoader<Material>::_instance._assets[p_ID];

	glLinkProgram(mat._hardwareID);

	int iLinkStatus;
	glGetProgramiv(mat._hardwareID, GL_LINK_STATUS, &iLinkStatus);
	if(!iLinkStatus == GL_TRUE)
	{
		jormungandr::logger::error("Linking of program failed");
		return false;
	}


	const char* names[] = {"_sampler0", "_sampler1", "_sampler2", "_sampler3"};
	for(int i = 0; i < 4; ++i)
	{
		uint32_t loc = glGetUniformLocation(mat._hardwareID, names[i]);
		glUniform1i(loc, i);
	}

	return true;
}

//--------------------------------------------

void material::bind(uint32_t p_ID)
{
	Material& mat = AssetLoader<Material>::_instance._assets[p_ID];
	glUseProgram(mat._hardwareID);

	const char* names[] = {"_sampler0", "_sampler1", "_sampler2", "_sampler3"};

	for(int i = 0; i < 4; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mat._samplers[i]);
	}
}

//--------------------------------------------

void material::setUniform(uint32_t p_ID, const char* p_Name, const alfar::Matrix4x4& p_Matrix)
{

	uint32_t loc = glGetUniformLocation(AssetLoader<Material>::_instance._assets[p_ID]._hardwareID, p_Name);

	glUniformMatrix4fv(loc, 1, GL_FALSE, &p_Matrix.x.x);
}

//===============================================

void material::addSampler(uint32_t p_ID, Texture* p_Sampler, uint8_t p_Number)
{
	Material& mat = AssetLoader<Material>::_instance._assets[p_ID];

	mat._samplers[p_Number] = p_Sampler->_hardwareID;
}