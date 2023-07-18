#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "common/types.h"

#include "buffer.h"

class VertexArray
{
public:
    /**
     * @brief Default destructor. Should probably be overridden.
     * 
     */
    virtual ~VertexArray() = default;

    /* Virtual functions */

    /**
     * @brief Bind this vertex array for drawing.
     * 
     */
    virtual void Bind() = 0;

    /**
     * @brief Unbind this vertex array.
     * This is optional, since OpenGL automatically unbinds 
     * the old buffer when binding a new one.
     * 
     */
    virtual void Unbind() = 0;

    /**
     * @brief Adds a vertex buffer.
     * You probably only need to do this once, since there is usually one vertex buffer per index buffer.
     * 
     * @param buf 
     */
    virtual void AddVertexBuffer(const Ref<VertexBuffer>& buf) = 0;

    /**
     * @brief Set the Index buffer for this array.
     * Note that this sets, not adds, an index buffer.
     * You can only use one index buffer per vertex array.
     * 
     * @param buf 
     */
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& buf) = 0;

    static Ref<VertexArray> Create();
};

#endif