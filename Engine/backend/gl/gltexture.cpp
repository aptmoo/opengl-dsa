#include "gltexture.h"
#include "glad/gl.h"
#include "common/instrumentor.h"

static GLenum InternalImageFormatToGL(ImageFormat format)
{
    switch(format)
    {
    case ImageFormat::RGB8:     return GL_RGB8;
    case ImageFormat::RGBA8:    return GL_RGBA8;
    case ImageFormat::_DEFAULT: return GL_RGBA8;
    default:                    return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

static GLenum ImageFormatToGL(ImageFormat format)
{
    switch(format)
    {
    case ImageFormat::RGB8:     return GL_RGB;
    case ImageFormat::RGBA8:    return GL_RGBA;
    case ImageFormat::_DEFAULT: return GL_RGBA;
    default:                    return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

static GLenum TextureWrapModeToGL(TextureWrapMode wrapMode)
{
    switch(wrapMode)
    {
    case TextureWrapMode::REPEAT:           return GL_REPEAT;
    case TextureWrapMode::MIRRORED_REPEAT:  return GL_MIRRORED_REPEAT;
    case TextureWrapMode::CLAMP_TO_BORDER:  return GL_CLAMP_TO_BORDER;
    case TextureWrapMode::CLAMP_TO_EDGE:    return GL_CLAMP_TO_EDGE;
    case TextureWrapMode::_DEFAULT:         return GL_REPEAT;
    default:                                return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

GLTexture::GLTexture(unsigned char *pixels, unsigned int width, unsigned int height, ImageFormat format, TextureWrapMode wrapMode)
{
    PROFILE_FUNCTION();
    glCreateTextures(GL_TEXTURE_2D, 1, &m_glID);
    glTextureParameteri(m_glID, GL_TEXTURE_WRAP_S, TextureWrapModeToGL(wrapMode));
    glTextureParameteri(m_glID, GL_TEXTURE_WRAP_T, TextureWrapModeToGL(wrapMode));

    // TODO: FilterMode enum    
    glTextureParameteri(m_glID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(m_glID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureStorage2D(m_glID, 1, InternalImageFormatToGL(format), width, height);
    glTextureSubImage2D(m_glID, 0, 0, 0, width, height, ImageFormatToGL(format), GL_UNSIGNED_BYTE, pixels);

    glGenerateTextureMipmap(m_glID);
}

GLTexture::~GLTexture()
{
    PROFILE_FUNCTION();
    glDeleteTextures(1, &m_glID);
}

void GLTexture::Bind(u32 slot)
{
    PROFILE_FUNCTION();
    glBindTextureUnit(slot, m_glID);
}

glm::vec2 GLTexture::GetSize()
{
    // TODO: implement
    return glm::vec2(0.0f);
}

u32 GLTexture::GetHeight(){ return 0; };
u32 GLTexture::GetWidth(){ return 0; };