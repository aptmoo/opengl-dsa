#include "glbuffer.h"
#include "glad/gl.h"

GLVertexBuffer::GLVertexBuffer(const BufferLayout& layout, void* data, size_t size)
    : m_Layout(layout)
{
    glCreateBuffers(1, &m_glID);
    glNamedBufferStorage(m_glID, size, data, GL_DYNAMIC_STORAGE_BIT);
}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers(1, &m_glID);
}

void GLVertexBuffer::SetData(void* data, size_t size)
{
    glNamedBufferSubData(m_glID, 0, size, data);
}

GLIndexBuffer::GLIndexBuffer(BufferElementType type, void* data, size_t count)
    : m_ElementCount(count), m_Type(type)
{
    glCreateBuffers(1, &m_glID);
    glNamedBufferStorage(m_glID, BufferElementTypeSize(type) * count, data, GL_DYNAMIC_STORAGE_BIT);
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &m_glID);
}

