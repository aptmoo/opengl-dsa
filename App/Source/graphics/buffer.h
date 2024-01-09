#ifndef BUFFER_H
#define BUFFER_H
#include <memory>
#include "bufferlayout.h"

class VertexBuffer
{
public: 
    virtual ~VertexBuffer() = default;

    /**
     * @brief Sets the data.
     * Wipes the old data stored on the gpu.
     * 
     * @param data 
     * @param size 
     */
    virtual void SetData(void* data, size_t size) = 0;

    virtual const BufferLayout& GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout& layout) = 0;

    static std::shared_ptr<VertexBuffer> Create(const BufferLayout& layout, void* data, size_t size);
};

class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;

    virtual size_t GetIndexCount() = 0;
    virtual BufferElementType GetType() = 0;

    static std::shared_ptr<IndexBuffer> Create(BufferElementType type, void* data, size_t count);
};

#endif