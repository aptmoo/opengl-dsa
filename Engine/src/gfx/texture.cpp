#include "texture.h"
#include "backend/gl/gltexture.h"

Ref<Texture> Texture::Create(unsigned char *pixels, unsigned int width, unsigned int height, ImageFormat format, TextureWrapMode wrapMode)
{
    return MakeRef<GLTexture>(pixels, width, height, format, wrapMode);
}