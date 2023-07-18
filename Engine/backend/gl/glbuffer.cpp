#include "glbuffer.h"
#include "common/instrumentor.h"

#include "glad/gl.h"

GLVertexBuffer::GLVertexBuffer(const void* data, u32 data_size)
{
    PROFILE_FUNCTION();
    glCreateBuffers(1, &m_glID);
    glNamedBufferData(m_glID, data_size, data, GL_DYNAMIC_DRAW);    // TODO: GL_DYNAMIC_DRAW or GL_STATIC_DRAW?

    /*
    TODO: Should glNamedBufferStorage or glNamedBufferData be used?
    glNamedBufferData removes old data. IDK if glNamedBufferStorage does that?
    */
    // glNamedBufferStorage(m_glID, data_size, data, GL_DYNAMIC_STORAGE_BIT);
}

GLVertexBuffer::GLVertexBuffer(u32 prealloc_size)
{
    PROFILE_FUNCTION();
    glCreateBuffers(1, &m_glID);
    glNamedBufferData(m_glID, prealloc_size, nullptr, GL_DYNAMIC_DRAW);
    // glNamedBufferStorage(m_glID, prealloc_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
}

GLVertexBuffer::~GLVertexBuffer()
{
    PROFILE_FUNCTION();
    glDeleteBuffers(1, &m_glID);
}

void GLVertexBuffer::SetData(const void* data, u32 data_size)
{
    PROFILE_FUNCTION();
    
    if(m_glID != 0)
        // glNamedBufferStorage(m_glID, data_size, data, GL_DYNAMIC_STORAGE_BIT);
        glNamedBufferData(m_glID, data_size, data, GL_DYNAMIC_DRAW);
}

GLIndexBuffer::GLIndexBuffer(const void* data, u32 data_size)
{
    PROFILE_FUNCTION();
    glCreateBuffers(1, &m_glID);
    glNamedBufferStorage(m_glID, data_size, data, GL_DYNAMIC_STORAGE_BIT);
}

GLIndexBuffer::~GLIndexBuffer()
{
    PROFILE_FUNCTION();
    glDeleteBuffers(1, &m_glID);
}