#include <gl/glew.h>
#include <gl/glfw.h>

#include "utils/configuration.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "core/component_type.h"

#include "data/sprite.h"

#include "mat4x4.h"


bool running = true;

int main(int argc, char** argv)
{
    glfwInit();

    jormungandr::logger::log("Application launched");
    jormungandr::configuration::loadFrom("data/config/application.json");

    glfwOpenWindow(jormungandr::config._width, jormungandr::config._height, 8, 8, 8, 8, 16, 16, jormungandr::config._fullscreen? GLFW_FULLSCREEN : GLFW_WINDOW);

    glewInit();

    while(running)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }

    jormungandr::logger::log("Application Quit");

    glfwTerminate();
}