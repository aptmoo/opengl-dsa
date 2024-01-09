#include "shader.h"
#include "opengl/glshader.h"

std::shared_ptr<Shader> Shader::Create(const std::string& vsource, const std::string& fsource)
{
    return std::make_shared<GLShader>(vsource, fsource);
}