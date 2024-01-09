#ifndef DEVICE_H
#define DEVICE_H
#include <memory>

class GraphicsDevice
{
public:
    virtual ~GraphicsDevice() = default;

    virtual void Init() = 0;
    virtual void Shutdown() = 0;

    /**
     * @brief Enables or disables depth testing.
     * 
     * @param enable 
     */
    virtual void SetDepthTest(bool enable) = 0;

    static std::unique_ptr<GraphicsDevice> Create(void* windowHandle);
};

#endif