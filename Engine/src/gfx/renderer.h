#ifndef GFX_RENDERER_H
#define GFX_RENDERER_H
#include "gfx/buffer.h"
#include "gfx/vertexArray.h"
#include "gfx/shader.h"

class Renderer
{
public:
    /**
     * @brief Empty virtual destructor.
     * 
     */
    virtual ~Renderer() = default;

    /**
     * @brief Start rendering.
     * 
     */
    virtual void Begin() = 0;

    /**
     * @brief Finish up drawing.
     * Calling this is required on some platforms.
     * 
     */
    virtual void End() = 0;
    
    /**
     * @brief Draw an vertex array using a shader.
     * 
     * @param shader 
     * @param array 
     */
    virtual void Draw(const Ref<Shader>& shader, const Ref<VertexArray> array) = 0;

    /* Creation functions */
    /**
     * @brief Create a renderer.
     * 
     * @return Ref<Renderer> 
     */
    static Scope<Renderer> Create();
};

#endif