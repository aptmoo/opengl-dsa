#ifndef GL_ARRAY_H
#define GL_ARRAY_H
#include "gfx/vertexArray.h"

class GLVertexArray : public VertexArray
{
public:
    /**
     * @brief Constructor. Creates a vertex array on the GPU.
     * 
     */
    GLVertexArray();

    /**
     * @brief Destructor. Deletes the vertex array.
     * 
     */
    virtual ~GLVertexArray();

    /**
     * @brief Bind this vertex array for drawing.
     *
     */
    virtual void Bind() override;

    /**
     * @brief Unbind this vertex array.
     *
     */
    virtual void Unbind() override;

    /**
     * @brief Adds a vertex buffer.
     *
     * @param buf
     */
    virtual void AddVertexBuffer(const Ref<VertexBuffer> &buf) override;

    /**
     * @brief Set the Index buffer for this array.
     *
     * @param buf
     */
    virtual void SetIndexBuffer(const Ref<IndexBuffer> &buf) override;

    virtual Ref<IndexBuffer> GetIndexBuffer() override { return m_IndexBuffer; };

private:
    u32 m_glID;

    u32 m_BufferCount = 0;
    std::vector<Ref<VertexBuffer>> m_Buffers;
    Ref<IndexBuffer> m_IndexBuffer;

    friend class DrawCallCompare;
};

#endif