#ifndef LAYOUT_H
#define LAYOUT_H
#include <string>
#include <vector>
#include <cstdint>

enum class BufferElementType : uint32_t
{
    _DEFAULT = 0,
    FLOAT, FLOAT2, FLOAT3, FLOAT4,
    INT, INT2, INT3, INT4,
    UINT,   // TODO: uint vecs
    CHAR,
    BOOL,
    MAT4,
    // TODO: add more types
};

/**
 * @brief Returns the size of this type.
 * 
 * @param type 
 * @return size_t 
 */
size_t BufferElementTypeSize(BufferElementType type);

/**
 * @brief Returns the amount of elements in a certain type.
 * 
 * @param type 
 * @return size_t 
 */
size_t BufferElementTypeComponents(BufferElementType type);

struct BufferElement
{
    std::string Name;
    size_t Size;
    size_t Components;
    size_t Offset;
    BufferElementType Type;
    bool Normalized;

    BufferElement(BufferElementType type, const std::string& name, bool normalized = false)
        : Name(name), Size(BufferElementTypeSize(type)), Components(BufferElementTypeComponents(type)), Type(type), Normalized(normalized){};
    
    BufferElement() = default;
};

/**
 * @brief A convenient interface for buffer layouts of all kinds.
 * @warning Please refrain from using mat4 types in a layout. It returns GL_INVALID_ENUM when converted to a gl type.
 * 
 */
class BufferLayout
{
public:
    BufferLayout(){};
    BufferLayout(std::initializer_list<BufferElement> elements)
        : m_Elements(elements)
    {
        CalculateStrideAndOffset();
    }

    // TODO: add AddElement function.

    /**
     * @brief Returns the stride(total size) of this layout.
     * 
     * @return size_t 
     */
    size_t GetStride() const { return m_Stride; };

    /**
     * @brief Returns a const ref vector of the elements.
     * 
     * @return const std::vector<BufferElement>& 
     */
    const std::vector<BufferElement>& GetElements() const { return m_Elements; };

    /* std iterator access */
    std::vector<BufferElement>::iterator begin()        { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end()          { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin()  const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end()    const { return m_Elements.end(); }
private: 
    /**
     * @brief Calculate element offsets and total strides.
     * Should be called after adding an element.
     * 
     */
    void CalculateStrideAndOffset()
    {
        m_Stride = 0;
        size_t offset = 0;
        for(BufferElement& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

    std::vector<BufferElement> m_Elements;

    /**
     * @brief Total size off all elements in this layout.
     * 
     */
    size_t m_Stride;
};

#endif