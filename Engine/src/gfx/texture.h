#ifndef GFX_TEXTURE_H
#define GFX_TEXTURE_H
#include "common/types.h"
#include "glm/glm.hpp"

enum class TextureWrapMode
{
    _DEFAULT = 0,
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
};

enum class ImageFormat
{
    _DEFAULT = 0,
    RGB8,
    RGBA8,
};

class Texture
{
public:
    virtual ~Texture() = default;

    /**
     * @brief Bind this texture to a certain bind slot.
     * 
     * @param slot 
     */
    virtual void Bind(u32 slot) = 0;

    /**
     * @brief Get the size of this texture, as a glm::vec2.
     * 
     * @return glm::vec2 
     */
    virtual glm::vec2 GetSize() = 0;

    /**
     * @brief Get the height of this texture.
     * 
     * @return u32 
     */
    virtual u32 GetHeight() = 0;

    /**
     * @brief Get the width of this texture.
     * 
     * @return u32 
     */
    virtual u32 GetWidth() = 0;

    /**
     * @brief Create a texture, using user supplied pixels.
     * Note that pixels should be texture data, not a path to an texture file!
     * 
     * @param pixels 
     * @param format 
     * @param wrapMode 
     * @return Ref<Texture> 
     */
    static Ref<Texture> Create(unsigned char *pixels, unsigned int width, unsigned int height, ImageFormat format, TextureWrapMode wrapMode);
};


#endif