#pragma once
#include "pch.h"
#include <unordered_map>

// TODO: Use GLCall wrapper

struct ShaderProgramSource
{
    std::string vertex;
    std::string fragment;
};

ShaderProgramSource ParseShader(const std::string& path);


class Shader
{
public:
    Shader();
    ~Shader();

    Shader& Use();

    void Compile(ShaderProgramSource source);
    unsigned int GetId(){return gl_ID;};

    void SetFloat(const char* name, float value);
    void SetInt(const char* name, int value);

    void SetVec4(const char* name, glm::vec4 value);
    void SetVec4(const char* name, float x, float y, float z, float w);

    void SetMat4(const char* name, const glm::mat4 matrix);

    int GetUniformLocation(const std::string& name) const;

private:
    unsigned int CompileShader(unsigned int type, const std::string &__source);
    unsigned int LinkProgram(const std::string &vertex, const std::string &fragment);

    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
    unsigned int gl_ID;
};