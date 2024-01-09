#include "device.h"
#include "opengl/gldevice.h"

std::unique_ptr<GraphicsDevice> GraphicsDevice::Create(void* handle)
{
    return std::make_unique<GLGraphicsDevice>(handle);
}