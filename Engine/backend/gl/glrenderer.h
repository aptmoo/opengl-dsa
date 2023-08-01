#ifndef GL_RENDERER_H
#define GL_RENDERER_H
#include "gfx/renderer.h"

#include "glarray.h"
#include "glshader.h"

#include <queue>

struct DrawCall
{
    Ref<Shader> shader;
    Ref<VertexArray> array;

    DrawCall(Ref<Shader> shd, Ref<VertexArray> arr) : shader(shd), array(arr) {}
};

class DrawCallCompare
{
public:
    bool operator()(DrawCall a, DrawCall b)
    {
        Ref<GLVertexArray> array_a = std::static_pointer_cast<GLVertexArray>(a.array);
        Ref<GLShader> shader_a = std::static_pointer_cast<GLShader>(a.shader);
        Ref<GLVertexArray> array_b = std::static_pointer_cast<GLVertexArray>(b.array);
        Ref<GLShader> shader_b = std::static_pointer_cast<GLShader>(b.shader);

        return (shader_a->m_glID > shader_b->m_glID) && (array_a->m_glID > array_b->m_glID);
    }
};

class GLRenderer : public Renderer
{
public:
    virtual void Begin() override;
    virtual void End() override;

    virtual void Draw(const Ref<Shader> &shader, const Ref<VertexArray> array) override;

private:
    std::priority_queue<DrawCall, std::vector<DrawCall>, DrawCallCompare> m_CallQueue;
};

#endif