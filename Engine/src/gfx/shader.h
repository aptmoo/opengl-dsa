#ifndef GFX_SHADER_H
#define GFX_SHADER_H
#include "common/types.h"
#include "glm/glm.hpp"
#include <string>

class Shader
{
public:
    virtual ~Shader() = default;


    /* Virtual functions */
    /**
     * @brief Bind this shader.
     * 
     */
    virtual void Bind() = 0;

    /**
     * @brief Unbind this shader.
     * Optional on some platforms.
     * 
     */
    virtual void Unbind() = 0;

    /**
     * @brief Reflect this shader.
     * This should be called from all implementation subclass constructors.
     * 
     */
    virtual void Reflect() = 0;

    virtual void SetInt(const std::string& name, int value) = 0;
    virtual void SetFloat(const std::string& name, float value) = 0;

    virtual void SetVec2(const std::string& name, glm::vec2 value) = 0;
    virtual void SetVec3(const std::string& name, glm::vec3 value) = 0;
    virtual void SetVec4(const std::string& name, glm::vec4 value) = 0;

    virtual void SetMat4(const std::string& name, glm::mat4 value) = 0;

    /* Creation functions */
    /**
     * @brief Create a shader using two sources as a string.
     * TODO: Deprecate
     * 
     * @param vsource 
     * @param fsource 
     * @return Ref<Shader> 
     */
    static Ref<Shader> Create(const std::string& vsource, const std::string& fsource);
};

#endif