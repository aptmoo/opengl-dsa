#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"

#include "graphics/shader.h"
#include "graphics/device.h"

#include <vector>
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

static struct
{
    glm::mat4 view, projection, model;
    unsigned int vao, ibo, vbo;

    unsigned int transformLoc;

    int width, height;
} state;


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
    state.width = 1280;
    state.height = 720;
    if(!window)
    {
        std::cout << "Failed to create a glfw window.\n";
        glfwTerminate();
        return -1;
    }

    std::unique_ptr<GraphicsDevice> device = GraphicsDevice::Create(window);
    device->Init();

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        state.width = width;
        state.height = height;
    });

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLMessageCallback, nullptr);

    /* Shaders */
    const char* vertexSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec4 vColor;\n"
    "layout (location = 2) in vec2 uv0;\n"
    "out vec3 vertexColor;\n"
    "out vec2 texCoord;\n"
    "uniform mat4 transform;"
    "void main()\n"
    "{\n"
    "vertexColor = vColor.xyz;\n"
    "texCoord = uv0;\n"
    "gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

    const char* fragmentSource = 
    "#version 330 core\n"
    "uniform sampler2D sTexture;\n"
    "in vec3 vertexColor;\n"
    "in vec2 texCoord;\n"
    "out vec4 FragColor;\n"
    "void main(){FragColor = vec4(vertexColor, 1.0) * texture(sTexture, texCoord);}\n";

    std::shared_ptr<Shader> shader = Shader::Create(vertexSource, fragmentSource);

    /* Textures */
    unsigned int tex, tex2;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);
    glCreateTextures(GL_TEXTURE_2D, 1, &tex2);

    glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTextureParameteri(tex2, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(tex2, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(tex2, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(tex2, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    int texWidth, texHeight, texChannels;
    unsigned char* pixels = stbi_load("data/texture.jpg", &texWidth, &texHeight, &texChannels, 4);
    glTextureStorage2D(tex, 1, GL_RGBA8, texWidth, texHeight);
    glTextureSubImage2D(tex, 0, 0, 0, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    stbi_image_free(pixels);
    glGenerateTextureMipmap(tex);
    glBindTextureUnit(0, tex);

    int tex2Width, tex2Height, tex2Channels;
    pixels = stbi_load("data/awesomeface.png", &tex2Width, &tex2Height, &tex2Channels, 4);
    glTextureStorage2D(tex2, 1, GL_RGBA8, tex2Width, tex2Height);
    glTextureSubImage2D(tex2, 0, 0, 0, tex2Width, tex2Height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    stbi_image_free(pixels);
    glGenerateTextureMipmap(tex2);
    glBindTextureUnit(1, tex2);
    
    /* Buffers */
    std::vector<float> vertices = 
    {
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
    std::vector<unsigned int> indices = 
    { 
        0, 1, 2,  0, 2, 3,
        6, 5, 4,  7, 6, 4,
        8, 9, 10,  8, 10, 11,
        14, 13, 12,  15, 14, 12,
        16, 17, 18,  16, 18, 19,
        22, 21, 20,  23, 22, 20
    };  

    glCreateBuffers(1, &state.vbo);
    glNamedBufferStorage(state.vbo, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateBuffers(1, &state.ibo);
    glNamedBufferData(state.ibo, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

    glCreateVertexArrays(1, &state.vao);
    glVertexArrayVertexBuffer(state.vao, 0, state.vbo, 0, 9 * sizeof(float));
    glVertexArrayElementBuffer(state.vao, state.ibo);

    glEnableVertexArrayAttrib(state.vao, 0);
    glVertexArrayAttribFormat(state.vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(state.vao, 0, 0);

    glEnableVertexArrayAttrib(state.vao, 1);
    glVertexArrayAttribFormat(state.vao, 1, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    glVertexArrayAttribBinding(state.vao, 1, 0);

    glEnableVertexArrayAttrib(state.vao, 2);
    glVertexArrayAttribFormat(state.vao, 2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float));
    glVertexArrayAttribBinding(state.vao, 2, 0);

    glBindVertexArray(state.vbo);

    /* Transform */
    state.model = glm::rotate(glm::mat4(1.0f), glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    state.view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
    state.projection = glm::perspective(glm::radians(45.0f), (float)state.width / (float)state.height, 0.1f, 100.0f);

    /* Main loop */
    while (!glfwWindowShouldClose(window))
    {
        glm::mat4 transform = state.projection * state.view * state.model;
        shader->Bind();
        shader->SetInt("sTexture", 0);
        shader->SetMat4("transform", transform);

        glBindVertexArray(state.vao);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &state.vao);
    glDeleteBuffers(1, &state.vbo);
    glDeleteBuffers(1, &state.ibo);
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
