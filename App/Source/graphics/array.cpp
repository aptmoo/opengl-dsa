#include "array.h"
#include "opengl/glarray.h"

std::shared_ptr<VertexArray> VertexArray::Create()
{
    return std::make_shared<GLVertexArray>();
}