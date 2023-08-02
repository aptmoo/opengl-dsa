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
    
    static u32 CompileShader(const std::string& source, GLenum type);

    friend class DrawCallCompare;
    friend class GLRenderer;
};

#endif