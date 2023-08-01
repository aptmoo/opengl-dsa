#include "renderer.h"
#include "backend/gl/glrenderer.h"

Scope<Renderer> Renderer::Create()
{
    return MakeScope<GLRenderer>();
}