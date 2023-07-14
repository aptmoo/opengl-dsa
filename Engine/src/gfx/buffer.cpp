#include "buffer.h"
#include "backend/gl/glbuffer.h"

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

Ref<IndexBuffer> IndexBuffer::Create(const void* data, u32 data_size)
{
    // TODO: Platform detection
    // TODO: Implement GLIndexbuffer
}