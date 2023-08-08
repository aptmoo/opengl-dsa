#include "glarray.h"
#include "glad/gl.h"

#include "common/instrumentor.h"
#include "glbuffer.h"

#include <iostream>


unsigned BufferToGLType(const BufferElementType& type)
{
    switch (type)
    {
    case BufferElementType::FLOAT:  return GL_FLOAT;
    case BufferElementType::FLOAT2: return GL_FLOAT;
    case BufferElementType::FLOAT3: return GL_FLOAT;
    case BufferElementType::FLOAT4: return GL_FLOAT;
    case BufferElementType::CHAR:   return GL_BYTE;
    case BufferElementType::UCHAR:  return GL_UNSIGNED_BYTE;
    case BufferElementType::BYTE:   return GL_BYTE;
    case BufferElementType::UBYTE:  return GL_UNSIGNED_BYTE;
    case BufferElementType::INT:    return GL_INT;
    case BufferElementType::INT2:   return GL_INT;
    case BufferElementType::INT3:   return GL_INT;
    case BufferElementType::INT4:   return GL_INT;
    case BufferElementType::UINT:   return GL_UNSIGNED_INT;
    case BufferElementType::MAT4:   return GL_FLOAT;
    case BufferElementType::BOOL:   return GL_BOOL;
    case BufferElementType::NONE:   return GL_INVALID_ENUM;
    default: return GL_INVALID_ENUM;  // Catastrophic failure! 
    }
}

GLVertexArray::GLVertexArray()
{
    PROFILE_FUNCTION();
    glCreateVertexArrays(1, &m_glID);
}

GLVertexArray::~GLVertexArray()
{
    PROFILE_FUNCTION();
    glDeleteVertexArrays(1, &m_glID);
}

void GLVertexArray::Bind()
{
    PROFILE_FUNCTION();
    glBindVertexArray(m_glID);
}

void GLVertexArray::Unbind()
{
    PROFILE_FUNCTION();
    glBindVertexArray(0);
}

void GLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& buf)
{
    PROFILE_FUNCTION();
    Ref<GLVertexBuffer> vbuf = std::static_pointer_cast<GLVertexBuffer>(buf);
    VertexBufferLayout layout = vbuf->GetLayout();
    glVertexArrayVertexBuffer(m_glID, m_BufferCount, vbuf->GetGLID(), 0, layout.GetStride());
    u32 elementIndex = 0;
    
    for(const auto& element : layout)
    {
        glEnableVertexArrayAttrib(m_glID, elementIndex);
        glVertexArrayAttribFormat(m_glID, elementIndex, BufferElementComponentCount(element.Type), BufferToGLType(element.Type), element.Normalized, element.Offset);
        glVertexArrayAttribBinding(m_glID, elementIndex, m_BufferCount);
        elementIndex++;
    }

    m_BufferCount++;
    m_Buffers.push_back(buf);
}

void GLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& buf)
{
    PROFILE_FUNCTION();
    Ref<GLIndexBuffer> ibuf = std::static_pointer_cast<GLIndexBuffer>(buf);
    glVertexArrayElementBuffer(m_glID, ibuf->GetGLID());

    m_IndexBuffer = buf;
}

