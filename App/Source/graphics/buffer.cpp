#include "buffer.h"
#include "opengl/glbuffer.h"

std::shared_ptr<VertexBuffer> VertexBuffer::Create(const BufferLayout& layout, void* data, size_t size)
{
    return std::make_shared<GLVertexBuffer>(layout, data, size);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(BufferElementType type, void* data, size_t count)
{
    return std::make_shared<GLIndexBuffer>(type, data, count);
}