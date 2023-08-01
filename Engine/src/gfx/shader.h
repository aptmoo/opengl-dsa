#ifndef GFX_SHADER_H
#define GFX_SHADER_H
#include "common/types.h"
#include "glm/glm.hpp"

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