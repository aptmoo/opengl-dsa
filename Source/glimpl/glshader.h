#ifndef GLSHADER_H
#define GLSHADER_H
#include "shader.h"
#include <unordered_map>

struct GLUniformInfo
{
    std::string Name;
    unsigned int Location;
    unsigned int Size;
    unsigned int Type;
};

class GLShader : public Shader
{
public:
    GLShader(const std::string& vsource, const std::string& fsource);
    virtual ~GLShader();

private:
    unsigned int CompileProgramStage(const std::string& source, unsigned int type);
    void PreCacheUniforms();

    unsigned int m_glID;
    std::unordered_map<std::string, GLUniformInfo> m_UniformCache;
};

#endif