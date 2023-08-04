#include "glrenderer.h"
#include "common/instrumentor.h"

void GLRenderer::Begin()
{
    PROFILE_FUNCTION();
    /* Make sure the call queue is empty so calls added in between frames get ignored */
    while(!m_CallQueue.empty())
    {
        m_CallQueue.pop();
    }
}

void GLRenderer::End()
{
    PROFILE_FUNCTION();
    /* 0 is a valid opengl id. To avoid not binding the first time, we set the "current" to an ID that will probably never exist */
    u32 currentShader = UINT32_MAX;
    u32 currentArray = UINT32_MAX;
    while(!m_CallQueue.empty())
    {
        const DrawCall& call = m_CallQueue.top();
        Ref<GLVertexArray> array = std::static_pointer_cast<GLVertexArray>(call.array);
        Ref<GLShader> shader = std::static_pointer_cast<GLShader>(call.shader);

        if(currentShader != shader->m_glID)
            shader->Bind();

        if(currentArray != array->m_glID)
            array->Bind();

        glDrawElements(GL_TRIANGLES, call.array->GetIndexBuffer()->GetElements(), GL_UNSIGNED_INT, nullptr);

        m_CallQueue.pop();
    }
}

void GLRenderer::Draw(const Ref<Shader> &shader, const Ref<VertexArray> array)
{
    PROFILE_FUNCTION();
    m_CallQueue.emplace(shader, array);
}