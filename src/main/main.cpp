#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <iostream>
#include <cstdio>

int main(int argc, char const *argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, false);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Title", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);
    std::cout << glGetString(GL_VERSION) << '\n';

    const char *vertexShaderSource = 
    "#version 330 core\n"
    "";

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
