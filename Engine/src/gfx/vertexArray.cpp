#include "vertexArray.h"
#include "backend/gl/glarray.h"

Ref<VertexArray> VertexArray::Create()
{
    return MakeRef<GLVertexArray>();
}