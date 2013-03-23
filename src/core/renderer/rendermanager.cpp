#include "core/renderer/rendermanager.h"

#include "utils/configuration.h"
#include "data/material.h"

#include <gl/glew.h>

using namespace jormungandr;
using namespace jormungandr::rendermanager;

//========================================

void RenderManager::onInit()
{
	_commands.reserve(1024);
}

//========================================

void RenderManager::onCreate(uint32_t p_ID)
{
	//jormungandr::component::renderer::init(_datas.at(p_ID), p_ID);
}

//============================================

void rendermanager::update(RenderManager& p_Manager)
{
	uint32_t size = p_Manager._datas.size();
	uint32_t nbCommand = 0;

	for(uint32_t i = 0; i < size; i++)
	{
		component::Renderer& r = p_Manager._datas[i];

		addCommand(p_Manager, r);
	}
}

//===============================================

void rendermanager::addCommand(RenderManager& p_Manager, component::Renderer& p_Renderer)
{
	p_Manager._commands.resize(p_Manager._commands.size()+1);

	RenderCommand& c = p_Manager._commands.back();

	c._renderkey.parts.materialID = p_Renderer._matID;
	
	for(uint8_t i = 0; i < 6; i++)
	{
		c._vertex[i] = p_Renderer._vertex[i];
		c._vertex[i]._position = alfar::vector3::mul(p_Renderer._transform, p_Renderer._vertex[i]._position);
	}
}

//===============================================

inline void drawBuffer(uint16_t p_NbVertex, component::renderer::Vertex* buffer)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, p_NbVertex*sizeof(component::renderer::Vertex), buffer);
	glDrawArrays(GL_TRIANGLES, 0, p_NbVertex);
}

void rendermanager::render( RenderManager& p_Manager)
{
	uint32_t size = p_Manager._commands.size();

	uint16_t nbVertex = 0;
	component::renderer::Vertex buffer[1000];

	uint16_t lastMat = -1;
	
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 1000 * sizeof(component::renderer::Vertex), NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	for(uint32_t i = 0; i < size; ++i)
	{
		const RenderCommand& c = p_Manager._commands.at(i);

		uint16_t matId = c._renderkey.parts.materialID;

		if(matId != lastMat)
		{
			//*** draw the current buffer
			drawBuffer(nbVertex, buffer);

			//*** setup the new things
			lastMat = matId;
			jormungandr::data::material::bind(lastMat);

			alfar::Matrix4x4 matrice = alfar::mat4x4::ortho(jormungandr::config._width, 0, 0, jormungandr::config._height, 0.01, 100);

			jormungandr::data::material::setUniform(lastMat, "mvp", matrice);

			nbVertex = 0;
		}

		for(uint8_t j = 0; j < 6; j++)
		{
			buffer[nbVertex] = c._vertex[j];
			++nbVertex;
		}

		if(nbVertex + 6 >= 1000)
		{
			drawBuffer(nbVertex, buffer);
			nbVertex = 0;
		}
	}

	//*** draw the current buffer
	drawBuffer(nbVertex, buffer);

	glDeleteBuffers(1, &vbo);
	p_Manager._commands.clear();
}