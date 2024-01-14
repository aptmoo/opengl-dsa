#include "glarray.h"
#include "glbuffer.h"
#include "glad/gl.h"
#include "iostream"

GLenum BufferElementToGL(BufferElementType type)
{
    switch(type)
    {
        case BufferElementType::_DEFAULT:   return GL_INVALID_ENUM;

        case BufferElementType::FLOAT:      return GL_FLOAT;
        case BufferElementType::FLOAT2:     return GL_FLOAT;
        case BufferElementType::FLOAT3:     return GL_FLOAT;
        case BufferElementType::FLOAT4:     return GL_FLOAT;

        case BufferElementType::INT:        return GL_INT;
        case BufferElementType::INT2:       return GL_INT;
        case BufferElementType::INT3:       return GL_INT;
        case BufferElementType::INT4:       return GL_INT;

        case BufferElementType::UINT:       return GL_UNSIGNED_INT;

        case BufferElementType::MAT4:       return GL_INVALID_ENUM; // THOU SHALT NOT USE MATRICES IN THYNE VERTEX LAYOUT

        case BufferElementType::BOOL:       return GL_BOOL;
        case BufferElementType::CHAR:       return GL_BYTE;

        default: return GL_INVALID_ENUM;
    }

    return 0;
}

GLVertexArray::GLVertexArray()
{
    glCreateVertexArrays(1, &m_glID);
}

GLVertexArray::~GLVertexArray()
{
    glDeleteVertexArrays(1, &m_glID);
}

void GLVertexArray::Bind()
{
    glBindVertexArray(m_glID);
}

void GLVertexArray::Unbind()
{
    glBindVertexArray(0);
}

void GLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
    std::shared_ptr<GLVertexBuffer> nativeBuffer = std::static_pointer_cast<GLVertexBuffer>(buffer);
    
    unsigned int attribIndex = 0;
    const BufferLayout& elements = nativeBuffer->GetLayout();

    glVertexArrayVertexBuffer(m_glID, m_VertexBufferIndex, nativeBuffer->GetID(), 0, elements.GetStride());
    for(const BufferElement& element : elements)    
    {
        glEnableVertexArrayAttrib(m_glID, attribIndex);
        glVertexArrayAttribFormat(m_glID, attribIndex, element.Components, BufferElementToGL(element.Type), element.Normalized, element.Offset);
        glVertexArrayAttribBinding(m_glID, attribIndex, m_VertexBufferIndex);
        attribIndex++;
    }

    m_VertexBuffers.push_back(buffer);
    m_VertexBufferIndex++;
}

void GLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
{
    std::shared_ptr<GLIndexBuffer> nativeBuffer = std::static_pointer_cast<GLIndexBuffer>(buffer);
    glVertexArrayElementBuffer(m_glID, nativeBuffer->GetID());
}