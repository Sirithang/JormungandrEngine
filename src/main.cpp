#include <gl/glew.h>
#include <gl/glfw.h>

#include "utils/configuration.h"
#include "utils/logger.h"
#include "utils/utils.h"

#include "core/engine.h"
#include "core/scene.h"
#include "core/entity.h"

#include "core/component_types.h"

#include "core/message/message.h"

#include "data/material.h"

#include "vector3.h"
#include "mat4x4.h"


bool running = true;

int main(int argc, char** argv)
{
    glfwInit();

    jormungandr::logger::log("Application launched");
    jormungandr::configuration::loadFrom("data/config/application.json");

    glfwOpenWindow(jormungandr::config._width, jormungandr::config._height, 8, 8, 8, 8, 16, 16, jormungandr::config._fullscreen? GLFW_FULLSCREEN : GLFW_WINDOW);

    glewInit();

	jormungandr::Scene& scn = jormungandr::engine::addScene();

	const int nb = 1000;
	for(int i = 0; i < nb; i++)
	{
		uint32_t e = scn.createData();

		uint32_t id = jormungandr::entity::addComponent(e, jormungandr::component::ComponentType::RENDERER);

		jormungandr::component::renderer::setMaterial(scn._renderManager._datas[id], 0);
	}


	glDisable(GL_CULL_FACE);

	//=========

	uint32_t mat = jormungandr::data::material::create();
	jormungandr::data::material::loadShader(mat, "data/vertex.vs");
	jormungandr::data::material::loadShader(mat, "data/fragment.fs");
	jormungandr::data::material::compile(mat);

	jormungandr::data::material::bind(mat);

	//*****************************************************

    while(running)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		for(int i = 0; i < nb; ++i)
			jormungandr::component::transform::translate(scn._datas[i]._transform, alfar::vector3::create(0.01f, 0, 0));

		jormungandr::engine::update();

		//glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }

    jormungandr::logger::log("Application Quit");

    glfwTerminate();
}