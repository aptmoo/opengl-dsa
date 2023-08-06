#include "buffer.h"
#include "backend/gl/glbuffer.h"

void VertexBufferLayout::AddElement(BufferElementType type, bool normalized)
{
    m_Elements.push_back({type, BufferElementTypeSize(type), normalized});
}

u32 VertexBufferLayout::GetStride()
{
    if(m_Stride != 0)
        return m_Stride;
    
    u32 offset = 0;
    for(auto& element : m_Elements)
    {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }

    return m_Stride;
}

Ref<VertexBuffer> VertexBuffer::Create(const void* data, u32 data_size)
{
    // TODO: Platform detection
    return MakeRef<GLVertexBuffer>(data, data_size);
}

Ref<VertexBuffer> VertexBuffer::Create(u32 prealloc_size)
{
    // TODO: Platform detection
    return MakeRef<GLVertexBuffer>(prealloc_size);
}

Ref<IndexBuffer> IndexBuffer::Create(const void* data, u32 elements, BufferElementType type)
{
    // TODO: Platform detection
    return MakeRef<GLIndexBuffer>(data, elements, type);
}