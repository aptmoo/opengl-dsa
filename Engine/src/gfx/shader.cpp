#include "shader.h"

#include "backend/gl/glshader.h"

Ref<Shader> Shader::Create(const std::string& vsource, const std::string& fsource)
{
    // TODO: Platform detection
    return MakeRef<GLShader>(vsource, fsource);
}