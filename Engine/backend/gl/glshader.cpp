#include "glshader.h"
#include "common/instrumentor.h"

#include "glad/gl.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <alloca.h>

GLShader::GLShader(const std::string &vsource, const std::string &fsource)
{
    PROFILE_FUNCTION();
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
    PROFILE_FUNCTION();
    glDeleteProgram(m_glID);
}

void GLShader::Bind()
{
    PROFILE_FUNCTION();
    glUseProgram(m_glID);
}

void GLShader::Unbind()
{
    PROFILE_FUNCTION();
    glUseProgram(0);
}

void GLShader::Reflect()
{
    PROFILE_FUNCTION();
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

void GLShader::SetInt(const std::string &name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void GLShader::SetFloat(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void GLShader::SetVec2(const std::string &name, glm::vec2 value)
{
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void GLShader::SetVec3(const std::string &name, glm::vec3 value)
{
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void GLShader::SetVec4(const std::string &name, glm::vec4 value)
{
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}


void GLShader::SetMat4(const std::string& name, glm::mat4 value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(value));
}

i32 GLShader::GetUniformLocation(const std::string &name)
{
    PROFILE_FUNCTION();
    if(m_UniformCache.find(name) != m_UniformCache.end())
    {
        UniformInfo info = m_UniformCache.at(name);
        return info.location;
    }

    return glGetUniformLocation(m_glID, name.c_str());
}

u32 GLShader::CompileShader(const std::string &source, GLenum type)
{
    PROFILE_FUNCTION();
    u32 id;
    id = glCreateShader(type);

    const char* strsource = source.c_str();
    glShaderSource(id, 1, &strsource, nullptr);
    glCompileShader(id);

    return id;
}