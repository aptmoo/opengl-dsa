#ifndef DEVICE_H
#define DEVICE_H

class GraphicsDevice
{
public:
    virtual ~GraphicsDevice() = default;

    /**
     * @brief Enables or disables depth testing.
     * 
     * @param enable 
     */
    virtual void SetDepthTest(bool enable) = 0;
};

#endif