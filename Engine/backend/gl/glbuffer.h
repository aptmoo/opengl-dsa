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

// private:
    /* TODO: Getter and setter func? */
    u32 m_glID;
private:
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
    GLIndexBuffer(const void* data, u32 elements);

    /**
     * @brief See bas class.
     * 
     * @return u32 
     */
    virtual u32 GetElements() override;

    /**
     * @brief Destructor. 
     * Deletes buffer on the GPU.
     * 
     */
    virtual ~GLIndexBuffer();
    
// private:
    u32 m_glID;
private:
    u32 m_Elements;
};

#endif