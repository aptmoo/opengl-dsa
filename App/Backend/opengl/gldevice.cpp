#include "gldevice.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

GLGraphicsDevice::GLGraphicsDevice(void* handle)
    : m_Handle(handle)
{}

GLGraphicsDevice::~GLGraphicsDevice()
{}

void GLGraphicsDevice::Init()
{
    glfwMakeContextCurrent((GLFWwindow*)m_Handle);
    gladLoadGL(glfwGetProcAddress);
}

void GLGraphicsDevice::Shutdown()
{

}

void GLGraphicsDevice::SetDepthTest(bool enable)
{
    if(enable)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}