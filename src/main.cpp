#include <gl/glew.h>
#include <gl/glfw.h>

#include <time.h>

#include "utils/configuration.h"
#include "utils/logger.h"
#include "utils/utils.h"

#include "core/engine.h"
#include "core/scene.h"
#include "core/entity.h"

#include "core/component_types.h"
#include "core/component/script.h"

#include "core/message/message.h"

#include "data/material.h"

#include "vector3.h"
#include "mat4x4.h"

#include "data/assetdatabase.h"
#include "data/texture.h"
#include "data/data_types.h"


bool running = true;

int main(int argc, char** argv)
{
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwInit();

    jormungandr::logger::log("Application launched");
    jormungandr::configuration::loadFrom("data/config/application.json");

    glfwOpenWindow(jormungandr::config._width, jormungandr::config._height, 8, 8, 8, 8, 16, 16, jormungandr::config._fullscreen? GLFW_FULLSCREEN : GLFW_WINDOW);

    glewInit();

	srand(42);

	jormungandr::Scene& scn = jormungandr::engine::addScene();

	const int nb = 1;
	for(int i = 0; i < nb; i++)
	{
		uint32_t e = scn.createData();

		uint32_t id = jormungandr::entity::addComponent(e, jormungandr::component::ComponentType::RENDERER);

		jormungandr::component::renderer::setMaterial(scn._renderManager._datas[id], 0);

		jormungandr::component::transform::translate(scn._datas[i]._transform, alfar::vector3::create(rand()%jormungandr::config._width, rand()%jormungandr::config._height, 1));
	}

	glDisable(GL_CULL_FACE);

	//=========

	uint32_t mat = jormungandr::data::material::create();
	jormungandr::data::material::loadShader(mat, "data/vertex.vs");
	jormungandr::data::material::loadShader(mat, "data/fragment.fs");
	jormungandr::data::material::compile(mat);

	jormungandr::data::Texture* a = jormungandr::data::assetdatabase::load<jormungandr::data::Texture>("data/test/test.png");
	jormungandr::data::material::addSampler(mat, a, 0);

	jormungandr::data::material::bind(mat);

	//*****************************************************

	uint32_t scr = jormungandr::entity::addComponent(0, jormungandr::component::ComponentType::SCRIPT);
	jormungandr::component::script::setScriptFile(scr, "data/test/test.lua");

	//*****************************************************

    while(running)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		/*for(int i = 0; i < nb; ++i)
		{
			jormungandr::component::transform::translate(scn._datas[i]._transform, alfar::vector3::create(0.1f, 0, 0));
		}*/

		jormungandr::engine::update();

        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }

    jormungandr::logger::log("Application Quit");

    glfwTerminate();
}