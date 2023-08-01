#include "glshader.h"
#include "glad/gl.h"
#include <alloca.h>

GLShader::GLShader(const std::string &vsource, const std::string &fsource)
{
    u32 vs = CompileShader(vsource, GL_VERTEX_SHADER);
    u32 fs = CompileShader(fsource, GL_FRAGMENT_SHADER);

    m_glID = glCreateProgram();
    glAttachShader(m_glID, vs);
    glAttachShader(m_glID, fs);
    glLinkProgram(m_glID);

    glDeleteShader(fs);
    glDeleteShader(vs);

    Reflect();
}

GLShader::~GLShader()
{
    glDeleteProgram(m_glID);
}

void GLShader::Bind()
{
    glUseProgram(m_glID);
}

void GLShader::Unbind()
{
    glUseProgram(0);
}

void GLShader::Reflect()
{
    glGetProgramiv(m_glID, GL_ACTIVE_UNIFORMS, &m_UniformCount);
    
    if(m_UniformCount == 0)
        return;
    
    GLint maxNameLength;
    GLsizei length;
    UniformInfo info;

    glGetProgramiv(m_glID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

    char* name = (char*)alloca(maxNameLength * sizeof(char));

    for(GLint i = 0; i < m_UniformCount; i++)
    {
        glGetActiveUniform(m_glID, i, maxNameLength, &length, &info.size, &info.type, name);
        info.location = glGetUniformLocation(m_glID, name);

        m_UniformCache.emplace(std::make_pair(std::string(name), info));
    }
}

u32 GLShader::CompileShader(const std::string &source, GLenum type)
{
    u32 id;
    id = glCreateShader(type);

    const char* strsource = source.c_str();
    glShaderSource(id, 1, &strsource, nullptr);
    glCompileShader(id);

    return id;
}