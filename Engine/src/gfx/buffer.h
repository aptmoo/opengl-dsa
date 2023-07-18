#ifndef GFX_BUFFER_H
#define GFX_BUFFER_H
#include "common/types.h"
#include <vector>

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
static u32 BufferElementTypeSize(const BufferElementType type)
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

/**
 * @brief Get the amount of components of a certain type.
 * 
 * @param type 
 * @return usize 
 */
static usize BufferElementComponentCount(const BufferElementType type)
{
    switch (type)
    {
    case BufferElementType::FLOAT:  return 1;
    case BufferElementType::FLOAT2: return 1 * 2;
    case BufferElementType::FLOAT3: return 1 * 3;
    case BufferElementType::FLOAT4: return 1 * 4;
    case BufferElementType::INT:    return 1;
    case BufferElementType::INT2:   return 1 * 2;
    case BufferElementType::INT3:   return 1 * 3;
    case BufferElementType::INT4:   return 1 * 4;
    case BufferElementType::MAT4:   return 1 * 4 * 4;
    case BufferElementType::BOOL:   return 1;
    case BufferElementType::NONE:   return 1;
    default: return 0;  // Catastrophic failure! 
    }
}

struct VertexBufferElement
{
    BufferElementType Type;
    u32 Offset;
    u32 Size;
    bool Normalized;

    VertexBufferElement(BufferElementType type, u32 size, bool normalized = false)
        : Type(type), Size(size), Normalized(normalized)
    {}
};

struct VertexBufferLayout
{
    /**
     * @brief Add an element to this layout.
     * 
     * @param type 
     * @param normalized 
     */
    void AddElement(BufferElementType type, bool normalized = false);

    /**
     * @brief Get the internal elements vector.
     * 
     * @return const std::vector<VertexBufferElement> 
     */
    inline const std::vector<VertexBufferElement> GetElements() { return m_Elements; }

    /**
     * @brief Iterators. Needed for for loops.
     * 
     * @return std::vector<VertexBufferElement>::iterator 
     */
    std::vector<VertexBufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<VertexBufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<VertexBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<VertexBufferElement>::const_iterator end() const { return m_Elements.end(); }

    u32 GetStride();

private:
    u32 m_Stride = 0;
    std::vector<VertexBufferElement> m_Elements;
};

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


    /**
     * @brief Get the internal layout. This layout must be private in a implementation subclass.
     * This is done to avoid making "brittle bases".
     * 
     * @return const VertexBufferLayout& 
     */
    virtual const VertexBufferLayout& GetLayout() = 0;

    /**
     * @brief Set the layout of this buffer.
     * 
     * @param layout 
     */
    virtual void SetLayout(const VertexBufferLayout& layout) = 0;

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