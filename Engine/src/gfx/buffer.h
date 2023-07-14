#ifndef GFX_BUFFER_H
#define GFX_BUFFER_H
#include "common/types.h"

enum class BufferElementType
{
    NONE = 0, FLOAT, FLOAT2, FLOAT3, FLOAT4, INT, INT2, INT3, INT4, MAT4, BOOL
};

/**
 * @brief The size of this type on the GPU.
 * 
 * @param type 
 * @return usize 
 */
static usize BufferElementTypeSize(const BufferElementType type)
{
    switch (type)
    {
    case BufferElementType::FLOAT:  return 4;   // TODO: Should sizeof(float) be used? 
    case BufferElementType::FLOAT2: return 4 * 2;
    case BufferElementType::FLOAT3: return 4 * 3;
    case BufferElementType::FLOAT4: return 4 * 4;
    case BufferElementType::INT:    return 4;
    case BufferElementType::INT2:   return 4 * 2;
    case BufferElementType::INT3:   return 4 * 3;
    case BufferElementType::INT4:   return 4 * 4;
    case BufferElementType::MAT4:   return 4 * 4 * 4;
    case BufferElementType::BOOL:   return 4;   // Bools have the same size as ann uint.
                                                // TODO: GLSL supports bool vec types(bvecN). We should probably support that.
                                                // TODO: Double precision types might also be nice.
    case BufferElementType::NONE:   return 0;
    default: return 0;  // Catastrophic failure! 
    }
}

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


class IndexBuffer
{
public:
    /**
     * @brief Default destructor. Should probably be overridden.
     *
     */
    virtual ~IndexBuffer() = default;

    /* Virtual funcions */
    // TODO: Do index buffers even need functions in DSA bindless opengl?

    /* Creation functions */
    static Ref<IndexBuffer> Create(const void* data, u32 data_size);
};

#endif