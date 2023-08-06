#ifndef GL_RENDERER_H
#define GL_RENDERER_H
#include "gfx/renderer.h"

#include "glarray.h"
#include "glshader.h"


class GLRenderer : public Renderer
{
public:
    virtual void SetClearColor(float r, float g, float b, float a) override;

    virtual void Clear() override;
    virtual void Clear(float r, float g, float b, float a) override;

    virtual void SetDepthTest(bool value) override;

    virtual void DrawIndexed(const Ref<VertexArray> &array) override;
    virtual void DrawIndexed(const Ref<VertexArray> &array, const Ref<IndexBuffer> &buffer) override;
};

#endif