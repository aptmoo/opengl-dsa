#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include "gfx/buffer.h"
#include "backend/gl/glbuffer.h"

#include "common/instrumentor.h"

#include <iostream>
#include <cstdio>

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
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
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		}
	}();
	std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}

int main(int argc, char const *argv[])
{
    PROFILE_START("Test", "perf.json");

    glfwInit();

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, false);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Title", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);
    std::cout << glGetString(GL_VERSION) << '\n';

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(message_callback, nullptr);

    // TODO: Do program pipelines still suck on NVidia?
    unsigned int vs, fs, pr;
    const char* vs_source = 
    "#version 330 core\n"
    "layout(location = 0) in vec3 vPos;\n"
    "void main(){ gl_Position = vec4(vPos, 1.0); }\n";
    const char* fs_source = 
    "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main(){ fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";

    vs = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vs_source);
    fs = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fs_source);
    glCreateProgramPipelines(1, &pr);
    glUseProgramStages(pr, GL_VERTEX_SHADER_BIT, vs);
    glUseProgramStages(pr, GL_FRAGMENT_SHADER_BIT, fs);

    glBindProgramPipeline(pr);

    float vertices[] = 
    {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    
    unsigned int indices[] = 
    {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Ref<VertexBuffer> vertexbuffer = VertexBuffer::Create(0);
    vertexbuffer->SetData(&vertices, sizeof(float) * 3 * 4);

    Ref<IndexBuffer> indexbuffer = IndexBuffer::Create(&indices, sizeof(unsigned) * 2 * 3);

    unsigned int vbuf, ibuf, varr;
    GLVertexBuffer* buf_internal = (GLVertexBuffer*)(vertexbuffer.get());
    vbuf = buf_internal->m_glID;    // hacks
    GLIndexBuffer *ibuf_internal = (GLIndexBuffer *)(indexbuffer.get());
    ibuf = ibuf_internal->m_glID; // hacks
    
    glCreateVertexArrays(1, &varr);
    glVertexArrayVertexBuffer(varr, 0, vbuf, 0, 3 * sizeof(float));
    glVertexArrayElementBuffer(varr, ibuf);

    glEnableVertexArrayAttrib(varr, 0);
    glVertexArrayAttribFormat(varr, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(varr, 0, 0);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(varr);
        glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteProgramPipelines(1, &pr);


    glfwTerminate();

    PROFILE_END();
    return 0;
}
