#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

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
};

#endif