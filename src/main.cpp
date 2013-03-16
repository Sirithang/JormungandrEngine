#include <gl/glew.h>
#include <gl/glfw.h>

#include "utils/configuration.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "core/component_type.h"

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


	//******** DEBUG ***********

	GLuint indice;
	glGenBuffers(1, &indice);

	glBindBuffer(GL_ARRAY_BUFFER, indice);

	alfar::Vector3 vert[3];
	vert[0] = alfar::vector3::create(0,0,0);
	vert[1] = alfar::vector3::create(0,1,0);
	vert[2] = alfar::vector3::create(1,0,0);

	glBufferData(GL_ARRAY_BUFFER, 3*sizeof(alfar::Vector3), vert, GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, 3*sizeof(vertex), &vert);

	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	//===

	uint32_t mat = jormungandr::data::material::create();
	jormungandr::data::material::loadShader(mat, "data/vertex.vs");
	jormungandr::data::material::loadShader(mat, "data/fragment.fs");
	jormungandr::data::material::compile(mat);

	jormungandr::data::material::bind(mat);

	//jormungandr::data::material::setUniform(1, 


	//*****************************************************

    while(running)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3*3);

        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }

    jormungandr::logger::log("Application Quit");

    glfwTerminate();
}