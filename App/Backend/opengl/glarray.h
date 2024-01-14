#ifndef GL_ARRAY_H
#define GL_ARRAY_H
#include "graphics/array.h"

class GLVertexArray : public VertexArray
{
public:
    GLVertexArray();
    virtual ~GLVertexArray() override;

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer) override;
    virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) override;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
    virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };
private:
    unsigned int m_glID;

    unsigned int m_VertexBufferIndex = 0;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

#endif