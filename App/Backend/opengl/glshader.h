#ifndef GLSHADER_H
#define GLSHADER_H
#include "graphics/shader.h"
#include <unordered_map>

class GLShader : public Shader
{
public:
    GLShader(const std::string& vsource, const std::string& fsource);
    virtual ~GLShader();

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual void SetInt(const std::string& name, int value) override;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

    int GetID(){ return m_glID; };
private:
    unsigned int CompileProgramStage(const std::string& source, unsigned int type);
    int GetUniformLoc(const std::string& name);
    void PreCacheUniforms();

    unsigned int m_glID;

    struct GLUniformInfo
    {
        std::string Name;
        int Location;
        int Size;
        unsigned int Type;
    };
    std::unordered_map<std::string, GLUniformInfo> m_UniformCache;
};

#endif