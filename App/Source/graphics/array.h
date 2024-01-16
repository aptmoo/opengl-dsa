#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "buffer.h"
#include <memory>

class VertexArray
{
public:
    virtual ~VertexArray() = default;

    /**
     * @brief Bind or unbind this vertexarray.
     * 
     */
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    /**
     * @brief Adds a vertex buffer.
     * Its not that common to use multiple buffers, so there is no guarantee that it keeps working.
     * 
     * @param buffer 
     */
    virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer) = 0;

    /**
     * @brief Set the index buffer.
     * There can only be one index buffer.
     * 
     * @param buffer 
     */
    virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) = 0;

    /**
     * @brief Returns a vector containing the vertex buffers used by this vertexArray.
     * 
     * @return const std::vector<std::shared_ptr<VertexBuffer>>& 
     */
    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;

    /**
     * @brief Returns the index buffer.
     * 
     * @return const std::shared_ptr<IndexBuffer>& 
     */
    virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

    static std::shared_ptr<VertexArray> Create();
};

#endif