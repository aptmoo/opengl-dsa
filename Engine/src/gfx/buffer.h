#ifndef GFX_BUFFER_H
#define GFX_BUFFER_H
#include "common/types.h"

class VertexBuffer
{
public:
    /**
     * @brief Default destructor. Should probably be overridden.
     * 
     */
    virtual ~VertexBuffer() = default;

    /* Virtual functions */
    /**
     * @brief Push data to the GPU. 
     * Data must be a valid pointer to some data.
     * data_size should be the physical size of the data, not the amount of vertices.
     * 
     * @param data A pointer to vertex data.
     * @param data_size The physical size of that data.
     */
    virtual void SetData(const void* data, u32 data_size) = 0;

    /* Creation functions */
    /**
     * @brief Create a vertex buffer object appropriate for the current platform.
     * Data must be a valid pointer to some data.
     * data_size should be the physical size of the data, not the amount of vertices.
     * 
     * @param data A pointer to vertex data.
     * @param data_size The physical size of that data.
     * @return Ref<VertexBuffer> 
     */
    static Ref<VertexBuffer> Create(const void* data, u32 data_size);

    /**
     * @brief Create a vertex buffer, and preallocate some space on the GPU.
     * 
     * @param prealloc_size 
     * @return Ref<VertexBuffer> 
     */
    static Ref<VertexBuffer> Create(u32 prealloc_size);
};

#endif