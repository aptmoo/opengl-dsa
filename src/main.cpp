#include "pch.h"
#include "gl/shader.h"
#include "vendor/stb_image.h"

int window_w = 1280;
int window_h = 720;

float sz = 5;


static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    sz += (float)yoffset;
}

static void FrameBufferSizeCallback(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
    window_w = w;
    window_h = h;
}

int main(void)
{

    #ifdef LOGFILE
    freopen("game.log", "w", stdout);
    #endif

    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwSwapInterval(1);

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return -1;

    std::printf("%s\n", glGetString(GL_VERSION));

    // float positions[] = {
    //     -0.5f, -0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, 0.0f, 1.0f
    // };


    // float positions[] = {
    //     -50.0f, -50.0f, 0.0f, 0.0f, // 0
    //     50.0f, -50.0f, 1.0f, 0.0f, // 1
    //     50.0f, 50.0f, 1.0f, 1.0f, // 2
    //     -50.0f, 50.0f, 0.0f, 1.0f  // 3
    // };

    float positions[] =
    {
        -50.0f, -50.0f, 0.0f, 0.0f, // 0
        50.0f, -50.0f, 1.0f, 0.0f, // 1
        50.0f, 50.0f, 1.0f, 1.0f, // 2
        -50.0f, 50.0f, 0.0f, 1.0f  // 3
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int va, vb, ib;
    glCreateVertexArrays(1, &va);
    glCreateBuffers(1, &vb);
    glCreateBuffers(1, &ib);

    glNamedBufferData(vb, 4 * 4 * sizeof(float), positions, GL_STATIC_DRAW);
    glNamedBufferData(ib, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(va, 0);
    glVertexArrayAttribBinding(va, 0, 0);
    glVertexArrayAttribFormat(va, 0, 2, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(va, 1);
    glVertexArrayAttribBinding(va, 1, 0);
    glVertexArrayAttribFormat(va, 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float));

    glVertexArrayVertexBuffer(va, 0, vb, 0, 4 * sizeof(float));
    glVertexArrayElementBuffer(va, ib);

    unsigned char* pImg;
    stbi_set_flip_vertically_on_load(true);
    int x, y, bpp;
    pImg = stbi_load("textures/heit.png", &x, &y, &bpp, 4);

    std::cout << bpp;

    unsigned int name;
    glCreateTextures(GL_TEXTURE_2D, 1, &name);

    glTextureParameteri(name, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTextureParameteri(name, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTextureParameteri(name, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(name, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureStorage2D(name, 1, GL_RGBA8, x, y);
    glTextureSubImage2D(name, 0, 0, 0, x, y, GL_RGBA, GL_UNSIGNED_BYTE, pImg);
    glGenerateTextureMipmap(name);

    stbi_image_free(pImg);


    Shader test;
    test.Compile(ParseShader("shaders/debug.shader"));
    test.Use();

    
    // glm::mat4 proj = glm::perspective(glm::radians(45.f), (float)1280/(float)720, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);


    float delta = 0.0f;
    float previousFrameTime = 0.0f;
    float currentFrameTime;

    float r = 0.0f;
    float increment = 0.5f;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        currentFrameTime = glfwGetTime();
        delta = currentFrameTime - previousFrameTime;
        previousFrameTime = currentFrameTime;

        if(r > 1.0f)
            increment = -0.5f;
        else if(r < 0.0f)
            increment = 0.5f;

        r += increment * delta;

        double px, py;

        glfwGetCursorPos(window, &px, &py);

        glm::mat4 proj = glm::ortho(0.0f, (float)window_w, 0.0f, (float)window_h, -1.0f, 1.0f);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(px, -py + window_h, 0));
        model = glm::scale(model, glm::vec3(sz, sz, 0));

        glm::mat4 mvp = proj * view;
        test.SetMat4("u_ViewProj", mvp);
        test.SetMat4("u_Transform", model);
        
        test.SetVec4("u_Color", r, 0.3f, 0.8f, 1.0f);
        
        glBindTextureUnit(0, name);
        test.SetInt("u_Texture", 0);

        glBindVertexArray(va);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

