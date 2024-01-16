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

    /**
     * @brief Get the layout of this buffer.
     * 
     * @return const BufferLayout& 
     */
    virtual const BufferLayout& GetLayout() const = 0;

    /**
     * @brief Set the layout. Probably not a good idea to do this during rendering, or at all.
     * 
     * @param layout 
     */
    virtual void SetLayout(const BufferLayout& layout) = 0;

    static std::shared_ptr<VertexBuffer> Create(const BufferLayout& layout, void* data, size_t size);
};

class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;

    /**
     * @brief Returns the amount of index elements.
     * 
     * @return size_t 
     */
    virtual size_t GetIndexCount() = 0;

    /**
     * @brief Get the type.
     * 
     * @return BufferElementType 
     */
    virtual BufferElementType GetType() = 0;

    static std::shared_ptr<IndexBuffer> Create(BufferElementType type, void* data, size_t count);
};

#endif