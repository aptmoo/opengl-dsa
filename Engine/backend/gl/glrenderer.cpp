#include "glrenderer.h"
#include "common/instrumentor.h"

void GLRenderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void GLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::DrawIndexed(const Ref<VertexArray> &array)
{
    array->Bind();
    glDrawElements(GL_TRIANGLES, array->GetIndexBuffer()->GetElements(), GL_UNSIGNED_INT, nullptr);
}

void GLRenderer::DrawIndexed(const Ref<VertexArray> &array, const Ref<IndexBuffer> &buffer)
{
    /* This is dumb, but OpenGL DSA has forced my hand. */
    Ref<IndexBuffer> oldBuffer = array->GetIndexBuffer();
    array->SetIndexBuffer(buffer);
    glDrawElements(GL_TRIANGLES, buffer->GetElements(), GL_UNSIGNED_INT, nullptr);
    array->SetIndexBuffer(oldBuffer);
};