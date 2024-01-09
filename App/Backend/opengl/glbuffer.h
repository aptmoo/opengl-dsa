#ifndef GL_BUFFER_H
#define GL_BUFFER_H
#include "graphics/buffer.h"

class GLVertexBuffer : public VertexBuffer
{
public: 
    GLVertexBuffer(const BufferLayout& layout, void* data, size_t size);
    virtual ~GLVertexBuffer() override;

    virtual void SetData(void* data, size_t size) override;

    virtual const BufferLayout& GetLayout() const override { return m_Layout; };
    virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

    unsigned int GetID(){ return m_glID; };
private:
    unsigned int m_glID;
    BufferLayout m_Layout;
};

class GLIndexBuffer : public IndexBuffer
{
public:
    GLIndexBuffer(BufferElementType type, void* data, size_t count);
    virtual ~GLIndexBuffer() override;

    virtual size_t GetIndexCount() override { return m_ElementCount; };
    virtual BufferElementType GetType() override { return m_Type; };

    unsigned int GetID(){ return m_glID; };
private:
    unsigned int m_glID;

    size_t m_ElementCount;
    BufferElementType m_Type;
};

#endif