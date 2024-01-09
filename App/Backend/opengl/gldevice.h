#ifndef GL_DEVICE_H
#define GL_DEVICE_H
#include "graphics/device.h"

class GLGraphicsDevice : public GraphicsDevice
{
public:
    GLGraphicsDevice(void* handle);
    virtual ~GLGraphicsDevice() override;

    virtual void Init() override;
    virtual void Shutdown() override;

    virtual void SetDepthTest(bool enable) override;
private:
    void* m_Handle;
};

#endif