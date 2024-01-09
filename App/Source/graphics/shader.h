#ifndef SHADER_H
#define SHADER_H
#include <memory>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    virtual ~Shader() = default;

    /**
     * @brief Bind this shader.
     * 
     */
    virtual void Bind() = 0;

    /**
     * @brief Unbind this shader.
     * 
     */
    virtual void Unbind() = 0;

    virtual void SetInt(const std::string& name, int value) = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

    /**
     * @brief 
     * 
     * TODO: Move to device?
     * 
     * @param vsource 
     * @param fsource 
     * @return std::shared_ptr<Shader> 
     */
    static std::shared_ptr<Shader> Create(const std::string& vsource, const std::string& fsource);
};

#endif