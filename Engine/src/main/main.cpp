#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "stb/stb_image.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

#include "gfx/buffer.h"
#include "gfx/vertexArray.h"
#include "gfx/shader.h"
#include "gfx/renderer.h"
#include "gfx/texture.h"

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
        default: return "INVALID";
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
        default: return "INVALID";
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
        default: return "INVALID";
		}
	}();
	std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}

static int s_WindowWidth = 1280;
static int s_WindowHeight = 720;
static bool s_FrameBufferChanged = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    s_FrameBufferChanged = true;
    s_WindowWidth = width;
    s_WindowHeight = height;
    glViewport(0, 0, width, height);
}

int main(int argc, char const *argv[])
{
    PROFILE_START("Test", "perf.json");

    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, false);
    GLFWwindow* window = glfwCreateWindow(s_WindowWidth, s_WindowHeight, "Title", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gladLoadGL(glfwGetProcAddress);
    std::cout << glGetString(GL_VERSION) << '\n';

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(message_callback, nullptr);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    stbi_set_flip_vertically_on_load(true);

    int texWidth, texHeight, texBPP;
    unsigned char* data = stbi_load("textures/l.jpg", &texWidth, &texHeight, &texBPP, 4);

    Ref<Texture> texture = Texture::Create(data, texWidth, texHeight, ImageFormat::RGBA8, TextureWrapMode::REPEAT);
    texture->Bind(0);

    stbi_image_free(data);


    const char* vs_source = 
    "#version 330 core\n"
    "layout(location = 0) in vec3 vPos;\n"
    "layout(location = 1) in vec4 vColor;\n"
    "layout(location = 2) in vec2 vTexCoord;\n"
    "out vec3 vertexColor;\n"
    "out vec2 uv0;\n"
    "uniform mat4 vp;\n"
    "uniform mat4 model;\n"
    "void main(){ vertexColor = vColor.xyz; uv0 = vTexCoord; gl_Position = vp * model *  vec4(vPos, 1.0); }\n";
    const char* fs_source = 
    "#version 330 core\n"
    "uniform sampler2D u_Texture;\n"
    "in vec3 vertexColor;\n"
    "in vec2 uv0;\n"
    "out vec4 fragColor;\n"
    "void main(){ fragColor = texture(u_Texture, uv0) * vec4(vertexColor, 1.0); }";
    
    Ref<Shader> shader = Shader::Create(vs_source, fs_source);
    shader->Bind();

    std::vector<float> vertices = {
        // positions            colors
        -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f,

         1.0f, -1.0f, -1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f, -1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     0.0f, 1.0f,

        -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     0.0f, 1.0f
    };

    std::vector<unsigned char> indices =
    {
        0, 1, 2,  0, 2, 3,
        6, 5, 4,  7, 6, 4,
        8, 9, 10,  8, 10, 11,
        14, 13, 12,  15, 14, 12,
        16, 17, 18,  16, 18, 19,
        22, 21, 20,  23, 22, 20
    };

    VertexBufferLayout layout;
    layout.AddElement(BufferElementType::FLOAT3);
    layout.AddElement(BufferElementType::FLOAT4);
    layout.AddElement(BufferElementType::FLOAT2);

    Ref<VertexBuffer> vertexbuffer = VertexBuffer::Create(0);
    vertexbuffer->SetData(vertices.data(), sizeof(float) * vertices.size());
    vertexbuffer->SetLayout(layout);

    Ref<IndexBuffer> indexbuffer = IndexBuffer::Create(indices.data(), indices.size(), BufferElementType::UCHAR);
    Ref<VertexArray> vertexarray = VertexArray::Create();
    vertexarray->SetIndexBuffer(indexbuffer);
    vertexarray->AddVertexBuffer(vertexbuffer);

    vertexarray->Bind();

    Scope<Renderer> renderer = Renderer::Create();
    renderer->SetDepthTest(true);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(60.0f), (float)s_WindowWidth / (float)s_WindowHeight, 0.1f, 100.0f);

    shader->SetInt("u_Texture", 0);

    while(!glfwWindowShouldClose(window))
    {
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        if(s_FrameBufferChanged)
            projection = glm::perspective(glm::radians(45.0f), (float)s_WindowWidth / (float)s_WindowHeight, 0.1f, 100.0f);

        s_FrameBufferChanged = false;
        shader->Bind();
        shader->SetMat4("vp", projection * view);
        shader->SetMat4("model", model);

        renderer->Clear();
        renderer->DrawIndexed(vertexarray);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    PROFILE_END();
    return 0;
}
