#include "bufferlayout.h"

size_t BufferElementTypeSize(BufferElementType type)
{
    switch(type)
    {
        case BufferElementType::_DEFAULT:   return 0;

        case BufferElementType::FLOAT:      return 4;
        case BufferElementType::FLOAT2:     return 4 * 2;
        case BufferElementType::FLOAT3:     return 4 * 3;
        case BufferElementType::FLOAT4:     return 4 * 4;

        case BufferElementType::INT:        return 4;
        case BufferElementType::INT2:       return 4 * 2;
        case BufferElementType::INT3:       return 4 * 3;
        case BufferElementType::INT4:       return 4 * 4;

        case BufferElementType::MAT4:       return 4 * 4 * 4;

        case BufferElementType::BOOL:       return 1;
        case BufferElementType::CHAR:       return 1;

        default: return 0;
    }

    return 0;
}

size_t BufferElementTypeComponents(BufferElementType type)
{
    switch(type)
    {
        case BufferElementType::_DEFAULT:   return 0;

        case BufferElementType::FLOAT:      return 1;
        case BufferElementType::FLOAT2:     return 2;
        case BufferElementType::FLOAT3:     return 3;
        case BufferElementType::FLOAT4:     return 4;

        case BufferElementType::INT:        return 1;
        case BufferElementType::INT2:       return 2;
        case BufferElementType::INT3:       return 3;
        case BufferElementType::INT4:       return 4;

        case BufferElementType::MAT4:       return 4 * 4;

        case BufferElementType::BOOL:       return 1;
        case BufferElementType::CHAR:       return 1;

        default: return 0;
    }

    return 0;
}