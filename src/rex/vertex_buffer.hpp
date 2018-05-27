#ifndef RXVERTEXBUFFER_H__
#define RXVERTEXBUFFER_H__

#include "config.hpp"
#include <vector>

namespace rex
{
    namespace detail
    {
        class GDI_IndexBuffer;
    }

    class RxVertexBufferImpl;

    /**
        \class RxVertexBuffer
        \brief Set of vertex information for rendering
    */
    class REX_API vertex_buffer
    {
    public:
        explicit vertex_buffer();
        virtual ~vertex_buffer();
    };
}

#endif // RXVERTEXBUFFER_H__
