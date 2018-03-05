#ifndef RXVERTEXBUFFER_H__
#define RXVERTEXBUFFER_H__

#include <bitcore/Config.h>
#include <vector>

namespace detail
{
	class GDI_IndexBuffer;
}

class RxVertexBufferImpl;

/**
    \class RxVertexBuffer
    \brief Set of vertex information for rendering
*/
class REX_API RxVertexBuffer
{
public:
    RxVertexBuffer();
    ~RxVertexBuffer();


private:
	detail::GDI_IndexBuffer* m_indexBuffer;
    RxVertexBufferImpl* m_vertexBuffer = nullptr;
};
#endif // RXVERTEXBUFFER_H__
