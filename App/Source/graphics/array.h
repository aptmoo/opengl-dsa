#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "buffer.h"
#include <memory>

class VertexArray
{
public:
    virtual ~VertexArray() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer) = 0;
    virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) = 0;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
    virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

    static std::shared_ptr<VertexArray> Create();
};

#endif