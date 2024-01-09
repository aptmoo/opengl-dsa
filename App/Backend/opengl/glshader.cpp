#include "glshader.h"
#include "glad/gl.h"
#include <memory>

#include <glm/gtc/type_ptr.hpp>

GLShader::GLShader(const std::string& vsource, const std::string& fsource)
{
    unsigned int vs = CompileProgramStage(vsource, GL_VERTEX_SHADER);
    unsigned int fs = CompileProgramStage(fsource, GL_FRAGMENT_SHADER);

    m_glID = glCreateProgram();
    glAttachShader(m_glID, vs);
    glAttachShader(m_glID, fs);
    glLinkProgram(m_glID);
    glUseProgram(m_glID);

    glDeleteShader(vs);
    glDeleteShader(fs);
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

void GLShader::SetInt(const std::string& name, int value)
{
    glUniform1i(GetUniformLoc(name), value);
}

void GLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int GLShader::CompileProgramStage(const std::string& source, unsigned int type)
{
    const char* src = source.c_str();
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
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

int GLShader::GetUniformLoc(const std::string& name)
{
    if(m_UniformCache.find(name) == m_UniformCache.end())
    {
        // This should not happen.
        int loc = glGetUniformLocation(m_glID, name.c_str());
        return loc;
    }

    // Its best to use GLUniformLocation as a reference, since a string can be pretty big
    GLUniformInfo& info = m_UniformCache.at(name);
    return info.Location;
}