#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "glm/glm.hpp"

#include <iostream>

void GLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto const src_str = [source]() {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
        default: return "NONE";
		}
	}();

	auto const type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
        default: return "NONE";
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
        default: return "NONE";
		}
	}();

	std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}

int main(int argc, char const *argv[])
{   
    /* Init glfw */
    if(!glfwInit())
    {   
        std::cout << "Failed to init glfw!\n";  // TODO: actual error logging
        glfwTerminate();
        return -1;
    }
    
    /* Window creation */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Title!", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if(!window)
    {
        std::cout << "Failed to create a glfw window.\n";
        glfwTerminate();
        return -1;
    }

    /* Init GL */
    if(!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to init glad!\n";
        glfwTerminate();
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << '\n';

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLMessageCallback, nullptr);

    /* Shaders */
    const char* vertexSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";

    const char* fragmentSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){FragColor = vec4(1.0, 0.5, 0.2, 1.0);}\n";

    unsigned int vs = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vertexSource);
    unsigned int fs = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragmentSource);
    unsigned int pr;
    glCreateProgramPipelines(1, &pr);
    glUseProgramStages(pr, GL_VERTEX_SHADER_BIT, vs);
    glUseProgramStages(pr, GL_FRAGMENT_SHADER_BIT, fs);

    glBindProgramPipeline(pr);
    
    /* Buffers */
    float vertices[] = 
    {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f  
    };
    unsigned int indices[] = 
    { 
        0, 1, 3,   
        1, 2, 3    
    };  

    unsigned int vbo, ibo, vao;
    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, 3 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);

    glCreateBuffers(1, &ibo);
    glNamedBufferData(ibo, 2 * 3 * sizeof(unsigned), indices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));
    glVertexArrayElementBuffer(vao, ibo);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);

    glBindVertexArray(vbo);


    /* Main loop */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(vs);
    glDeleteProgram(fs);
    glDeleteProgramPipelines(1, &pr);
    

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
