#include "glutils.h"

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::printf("OpenGL Error: %d\n", error);
        std::printf("Func: %s\nFile: %s\nLine:%d\n", function, file, line);
        return false;
    }
    return true;
}