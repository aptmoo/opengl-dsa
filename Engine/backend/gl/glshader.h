#ifndef GL_SHADER_H
#define GL_SHADER_H
#include "gfx/shader.h"
#include "common/types.h"
#include "glad/gl.h"

#include <unordered_map>

class GLShader : public Shader
{
public:
    GLShader(const std::string& vsource, const std::string& fsource);

    virtual ~GLShader();

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual void Reflect() override;

    virtual void SetInt(const std::string &name, int value) override;
    virtual void SetFloat(const std::string &name, float value) override;

    virtual void SetVec2(const std::string &name, glm::vec2 value) override;
    virtual void SetVec3(const std::string &name, glm::vec3 value) override;
    virtual void SetVec4(const std::string &name, glm::vec4 value) override;

    virtual void SetMat4(const std::string& name, glm::mat4 value) override;
private:
    u32 m_glID;

    GLint m_UniformCount;
    struct UniformInfo
    {
        GLint location;
        GLsizei size;
        GLenum type = GL_NONE;
    };
    std::unordered_map<std::string, UniformInfo> m_UniformCache;

    i32 GetUniformLocation(const std::string &name);

    static u32 CompileShader(const std::string &source, GLenum type);

    friend class GLRenderer;
};

#endif