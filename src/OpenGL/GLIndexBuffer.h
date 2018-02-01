#ifndef NephilimGL_IndexBuffer_h__
#define NephilimGL_IndexBuffer_h__

#include <Nephilim/GDI/GDI_GeometryBuffers.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API IndexBuffer : public GDI_IndexBuffer
{
public:
	/// Initializes the index buffer to an invalid state
	IndexBuffer();

	/// Make sure the opengl resource has been released and its data
	~IndexBuffer();

	/// Activate this index buffer
	void bind();

	/// Initializes the vertex buffer to a valid state
	void create();

	/// Eliminate the opengl resource and its data
	void destroy();

private:
	unsigned int mObject;
};

NEPHILIM_NS_END
#endif // NephilimGL_IndexBuffer_h__
