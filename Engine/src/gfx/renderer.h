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
     * @brief Sets a clear color.
     * 
     * @param r 
     * @param g 
     * @param b 
     * @param a 
     */
    virtual void SetClearColor(float r, float g, float b, float a) = 0;

    /**
     * @brief Clear. Does not set a clear color.
     *
     */
    virtual void Clear() = 0;

    /**
     * @brief Clear using a specific color.
     * 
     * @param r 
     * @param g 
     * @param b 
     * @param a 
     */
    virtual void Clear(float r, float g, float b, float a) = 0;

    /**
     * @brief Enables or disables depth testing.
     * 
     * @param value 
     */
    virtual void SetDepthTest(bool value) = 0;
    
    /**
     * @brief Draw an vertex array.
     * 
     * @param array
     */
    virtual void DrawIndexed(const Ref<VertexArray>& array) = 0;

    /**
     * @brief Draw a vertex array, using a seperate index buffer.
     * TODO: This should probably not exist?
     * TODO: Testing has revealed this is slower since we have to swap pointers around.
     * 48 us for the regular function vs 63 us for this function, on my laptop.
     * Maybe this function should stay if i ever(probably not) implement other backends?
     * 
     * @param array 
     * @param buffer 
     */
    virtual void DrawIndexed(const Ref<VertexArray>& array, const Ref<IndexBuffer>& buffer) = 0;

    /* Creation functions */
    /**
     * @brief Create a renderer.
     * 
     * @return Scope<Renderer> 
     */
    static Scope<Renderer> Create();
};

#endif