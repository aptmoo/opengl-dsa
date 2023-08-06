#include "glrenderer.h"
#include "common/instrumentor.h"

void GLRenderer::SetClearColor(float r, float g, float b, float a)
{
    PROFILE_FUNCTION();
    glClearColor(r, g, b, a);
}

void GLRenderer::Clear()
{
    PROFILE_FUNCTION();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::Clear(float r, float g, float b, float a)
{
    PROFILE_FUNCTION();
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::SetDepthTest(bool value)
{
    if(value)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void GLRenderer::DrawIndexed(const Ref<VertexArray> &array)
{
    PROFILE_FUNCTION();
    array->Bind();
    glDrawElements(GL_TRIANGLES, array->GetIndexBuffer()->GetElements(), BufferToGLType(array->GetIndexBuffer()->GetType()), nullptr);
}

void GLRenderer::DrawIndexed(const Ref<VertexArray> &array, const Ref<IndexBuffer> &buffer)
{
    PROFILE_FUNCTION();
    /* This is dumb, but OpenGL DSA has forced my hand. */
    Ref<IndexBuffer> oldBuffer = array->GetIndexBuffer();
    array->SetIndexBuffer(buffer);
    array->Bind();
    glDrawElements(GL_TRIANGLES, buffer->GetElements(), BufferToGLType(buffer->GetType()), nullptr);
    array->SetIndexBuffer(oldBuffer);
};