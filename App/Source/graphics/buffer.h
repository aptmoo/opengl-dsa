#ifndef BUFFER_H
#define BUFFER_H
#include <memory>
#include "bufferlayout.h"

class VertexBuffer
{

    virtual std::shared_ptr<VertexBuffer> Create(void* data, )
};

#endif