#include "shader.h"
#include "glutils.h"
#include <sstream>

ShaderProgramSource ParseShader(const std::string &path)
{
    std::ifstream stream(path);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            if(type != ShaderType::NONE) ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

Shader::Shader()
    : gl_ID(0){}

Shader::~Shader()
{
    if(gl_ID != 0)
    {
        GLCall(glDeleteProgram(gl_ID));
        std::printf("[Program ID: %d] Successfully unloaded\n", gl_ID);
    }
}

Shader &Shader::Use()
{
    GLCall(glUseProgram(gl_ID));
    return *this;
}

void Shader::Compile(ShaderProgramSource source)
{
    gl_ID = LinkProgram(source.vertex, source.fragment);
}

void Shader::SetFloat(const char* name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetInt(const char* name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetVec4(const char* name, glm::vec4 value)
{
    GLCall(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
}
void Shader::SetVec4(const char* name, float x, float y, float z, float w)
{
    GLCall(glUniform4f(GetUniformLocation(name), x, y, z, w));
}

void Shader::SetMat4(const char* name, const glm::mat4 matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(unsigned int location = glGetUniformLocation(gl_ID, name.c_str()));
    if(location == -1)
        std::printf("[Program ID: %d] Shader uniform '%s' not found\n", gl_ID, name.c_str());

    m_UniformLocationCache[name] = location;
    return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &__source)
{
    unsigned int id = glCreateShader(type);
    const char *source = __source.c_str();

    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::printf("Shader compilation failed:\n%s\n", message);
        return 0;
    }
    return id;
}

unsigned int Shader::LinkProgram(const std::string &vertex, const std::string &fragment)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

    // TODO: More streamlined method
    // Maybe make the resource manager responsible for this?
    // If either shader fails to compile, return a bright pink shader
    if (vs == 0 || fs == 0)
    {
        std::string vertexShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec4 position;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = position;\n"
            "}\n";

        std::string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0, 0.0, 1.0, 1.0);\n"
            "}\n";

        vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // Linkage and validation

    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        std::printf("Program linkage failed:\n%s\n", message);
        return 0;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        std::printf("Program validation failed:\n%s\n", message);  
        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    std::printf("[Program ID: %d] Successfully loaded\n", program);

    return program;
}
