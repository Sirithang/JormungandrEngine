#include <gl/glfw.h>
#include "utils/logger.h"

bool running = true;

int main(int argc, char** argv)
{
	glfwInit();

	jormungandr::logger::log("Application launched");

	glfwOpenWindow(800, 600, 8, 8, 8, 8, 16, 16, GLFW_WINDOW);

	while(running)
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers();

		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}

	jormungandr::logger::log("Application Quit");

	glfwTerminate();
}