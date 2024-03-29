#ifndef GL_BUFFER_H
#define GL_BUFFER_H
#include "gfx/buffer.h"

class GLVertexBuffer : public VertexBuffer
{
public:
    /**
     * @brief Constructor. See Create() on the base class.
     * 
     * @param data 
     * @param data_size 
     */
    GLVertexBuffer(const void* data, u32 data_size);

    /**
     * @brief Constructor. See Create() on the base class.
     * 
     * @param prealloc_size
     */
    GLVertexBuffer(u32 prealloc_size);

    /**
     * @brief OpenGL vertex buffer destructor. Deletes buffer on the GPU.
     * 
     */
    virtual ~GLVertexBuffer();

    virtual const VertexBufferLayout& GetLayout() override { return m_Layout; };
    virtual void SetLayout(const VertexBufferLayout& layout) override { m_Layout = layout; };

    /**
     * @brief Set new data on the gpu.
     * 
     * @param data 
     * @param data_size 
     */
    virtual void SetData(const void* data, u32 data_size) override;

    u32 GetGLID(){ return m_glID; };
    const u32 GetGLID() const { return m_glID; };

private:
    u32 m_glID;
    VertexBufferLayout m_Layout;
};

class GLIndexBuffer : public IndexBuffer
{
public:
    /**
     * @brief Constructor. see Create() on the base class.
     * 
     * @param data 
     * @param elements
     */
    GLIndexBuffer(const void* data, u32 elements, BufferElementType type);

    /**
     * @brief See base class.
     * 
     * @return u32 
     */
    virtual u32 GetElements() override;
    virtual BufferElementType GetType() override;

    /**
     * @brief Destructor. 
     * Deletes buffer on the GPU.
     * 
     */
    virtual ~GLIndexBuffer();
    
    u32 GetGlID() { return m_glID; };
    const u32 GetGLID() const { return m_glID; };

private:
    u32 m_glID;
    u32 m_Elements;
    // Hacky way of doing this
    BufferElementType m_Type;
};

#endif