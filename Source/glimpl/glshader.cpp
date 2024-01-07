#include "glshader.h"
#include "glad/gl.h"
#include <memory>

GLShader::GLShader(const std::string& vsource, const std::string& fsource)
{

}

GLShader::~GLShader()
{
    glDeleteProgram(m_glID);
}

unsigned int GLShader::CompileProgramStage(const std::string& source, unsigned int type)
{
    const char* src = source.c_str();
    unsigned int id = glCreateShaderProgramv(type, 1, &src);
    return id;
}

void GLShader::PreCacheUniforms()
{
    int uniformAmount = 0;
    glGetProgramiv(m_glID, GL_ACTIVE_UNIFORMS, &uniformAmount);
    int maxUniformNameLen = 0;
    glGetProgramiv(m_glID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformNameLen);

    std::unique_ptr<char[]> uniformName = std::make_unique<char[]>(maxUniformNameLen);

    for(int i = 0; i < uniformAmount; i++)
    {
        int size = 0;
        int length = 0;
        unsigned int type = 0;
        glGetActiveUniform(m_glID, i, maxUniformNameLen, &length, &size, &type, uniformName.get());

        GLUniformInfo info;
        info.Location = i;
        info.Name = std::string(uniformName.get());
        info.Type = type;
        info.Size = size;

        m_UniformCache.emplace(info.Name, info);
    }
}   