#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#include "gfx/texture.h"

class GLTexture : public Texture
{
public:
    GLTexture(unsigned char *pixels, unsigned int width, unsigned int height, ImageFormat format, TextureWrapMode wrapMode);
    virtual ~GLTexture();

    virtual void Bind(u32 slot) override;

    virtual glm::vec2 GetSize() override;
    virtual u32 GetHeight() override;
    virtual u32 GetWidth() override;

private:
    u32 m_glID;
};

#endif