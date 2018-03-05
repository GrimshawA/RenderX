//#ifndef NephilimGraphicsGLVertexBuffer_h__
//#define NephilimGraphicsGLVertexBuffer_h__

//#include <RenderX/RxVertexBuffer.h>
//#include <RenderX/RxGlobal.h>

//class RxVertexArray;

///**
//	\class GLVertexBuffer
//	\brief OpenGL Vertex Buffer implementation for GDI_VertexBuffer
//*/
//class REX_API GLVertexBuffer : public RxVertexBufferImpl
//{
//public:

//	enum StorageMode
//	{
//		StaticDraw,
//		StaticCopy,
//		StaticRead,
//		DynamicDraw,
//		DynamicCopy,
//		DynamicRead,
//		StreamDraw,
//		StreamCopy,
//		StreamRead
//	};

//	/// Initializes the vertex buffer to an invalid state
//	GLVertexBuffer();

//	/// Make sure the opengl resource has been released and its data
//	~GLVertexBuffer();

//	/// Activate this VBO as current
//	void bind();

//	/// Initializes the vertex buffer to a valid state
//	void create();

//	/// Eliminate the opengl resource and its data
//	void destroy();

//	/// Initializes GPU memory with <size> bytes and the desired access mode
//	void resize(int32_t size, StorageMode mode);

//	/// Upload a VertexArray to the GPU memory
//    void upload(const RxVertexArray& vertexArray, StorageMode mode);

//	/// Check if the VBO is valid (initialized)
//	operator bool() const;

//private:
//	unsigned int mObject;
//};

//#endif // NephilimGraphicsGLVertexBuffer_h__
