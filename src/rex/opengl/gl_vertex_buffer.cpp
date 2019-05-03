#include "gl_vertex_buffer.hpp"
#include "gl_helpers.hpp"

namespace rex {

namespace
{
    GLenum getGLUsageMode(gl_vertex_buffer::StorageMode mode)
    {
        GLenum usageMode;
        switch (mode)
        {
        case gl_vertex_buffer::StaticDraw: usageMode = GL_STATIC_DRAW; break;
        case gl_vertex_buffer::DynamicDraw: usageMode = GL_DYNAMIC_DRAW; break;
        case gl_vertex_buffer::StreamDraw: usageMode = GL_STREAM_DRAW; break;

#ifdef NEPHILIM_DESKTOP
        case GLVertexBuffer::StreamCopy: usageMode = GL_STREAM_COPY; break;
        case GLVertexBuffer::StreamRead: usageMode = GL_STREAM_READ; break;
        case GLVertexBuffer::DynamicCopy: usageMode = GL_DYNAMIC_COPY; break;
        case GLVertexBuffer::DynamicRead: usageMode = GL_DYNAMIC_READ; break;
        case GLVertexBuffer::StaticCopy: usageMode = GL_STATIC_COPY; break;
        case GLVertexBuffer::StaticRead: usageMode = GL_STATIC_READ; break;
#endif
        default: usageMode = GL_STATIC_DRAW; break;
        }
        return usageMode;
    }
}

gl_vertex_buffer::gl_vertex_buffer()
: mObject(0)
{
}

gl_vertex_buffer::~gl_vertex_buffer()
{
    destroy();
}

void gl_vertex_buffer::create()
{
    // Don't initialize unless there is nothing previously allocated
    if (mObject == 0)
    {
        glGenBuffers(1, &mObject);
    }
}


void gl_vertex_buffer::destroy()
{
    if (mObject)
    {
        glDeleteBuffers(1, &mObject);
        mObject = 0;
    }
}

void gl_vertex_buffer::bind()
{
    if (mObject)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mObject);
    }
}

gl_vertex_buffer::operator bool() const
{
    return (mObject > 0);
}

//void gl_vertex_buffer::upload(const GDI_VertexArray& vertexArray, StorageMode mode)
//{
//    if (mObject)
//    {
//        GLenum usageMode = getGLUsageMode(mode);

//        glBufferData(GL_ARRAY_BUFFER, vertexArray.getMemorySize(), &vertexArray._data[0], usageMode);
//    }
//}

void gl_vertex_buffer::resize(int32_t size, StorageMode mode)
{
    if (mObject)
    {
        GLenum usageMode = getGLUsageMode(mode);

        glBufferData(GL_ARRAY_BUFFER, size, NULL, usageMode);
    }
}

}

