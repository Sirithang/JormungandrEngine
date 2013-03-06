#include <gl/glfw.h>

#include "utils/configuration.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "core/component_type.h"

#include "mat4x4.h"


bool running = true;

int main(int argc, char** argv)
{
    glfwInit();

    jormungandr::logger::log("Application launched");
    jormungandr::configuration::loadFrom("data/config/application.json");

    glfwOpenWindow(jormungandr::config._width, jormungandr::config._height, 8, 8, 8, 8, 16, 16, jormungandr::config._fullscreen? GLFW_FULLSCREEN : GLFW_WINDOW);

    alfar::Matrix4x4 mat1 = alfar::mat4x4::create(  alfar::vector4::create(-2,  0,  1,  7),
                                                    alfar::vector4::create( 6,  1, -2,  6),
                                                    alfar::vector4::create( 6,  3,  2,  3),
                                                    alfar::vector4::create( 5,  0, -2, -1));

    alfar::Matrix4x4 mat2 = alfar::mat4x4::create(  alfar::vector4::create( 1,  7, -2,  6),
                                                    alfar::vector4::create( 3,  3,  4,  4),
                                                    alfar::vector4::create( 4,  5,  1,  2),
                                                    alfar::vector4::create(-2,  6,  4,  6));

    alfar::Matrix4x4 res = alfar::mat4x4::mul(mat1, mat2);

    while(running)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }

    jormungandr::logger::log("Application Quit");

    glfwTerminate();
}