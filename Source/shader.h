#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    virtual ~Shader() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetInt(const std::string& name, int value) = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
};

#endif