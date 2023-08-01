#include "glrenderer.h"

void GLRenderer::Begin()
{
    /* Make sure the call queue is empty so calls added in between frames get ignored */
    while(!m_CallQueue.empty())
    {
        m_CallQueue.pop();
    }
}

void GLRenderer::End()
{
    while(!m_CallQueue.empty())
    {
        const DrawCall& call = m_CallQueue.top();
        call.shader->Bind();
        call.array->Bind();

        glDrawElements(GL_TRIANGLES, call.array->GetIndexBuffer()->GetElements(), GL_UNSIGNED_INT, nullptr);

        m_CallQueue.pop();
    }
}

void GLRenderer::Draw(const Ref<Shader> &shader, const Ref<VertexArray> array)
{
    m_CallQueue.emplace(shader, array);
}