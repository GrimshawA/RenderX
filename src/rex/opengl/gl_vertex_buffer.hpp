#ifndef RENDERXGLVERTEXBUFFER_HPP_
#define RENDERXGLVERTEXBUFFER_HPP_

#include <stdint.h>
#include "../vertex_buffer.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>

namespace rex
{
    /**
        \class gl_vertex_buffer
        \brief OpenGL Vertex Buffer implementation for GDI_VertexBuffer
    */
    class REX_API gl_vertex_buffer : public vertex_buffer
    {
    public:

        enum StorageMode
        {
            StaticDraw,
            StaticCopy,
            StaticRead,
            DynamicDraw,
            DynamicCopy,
            DynamicRead,
            StreamDraw,
            StreamCopy,
            StreamRead
        };

        /// Initializes the vertex buffer to an invalid state
        gl_vertex_buffer();

        /// Make sure the opengl resource has been released and its data
        ~gl_vertex_buffer();

        /// Activate this VBO as current
        void bind();

        /// Initializes the vertex buffer to a valid state
        void create();

        /// Eliminate the opengl resource and its data
        void destroy();

        /// Initializes GPU memory with <size> bytes and the desired access mode
        void resize(int32_t size, StorageMode mode);

        /// Upload a VertexArray to the GPU memory
        //void upload(const rex::vertex_data& vertexArray, StorageMode mode);

        /// Check if the VBO is valid (initialized)
        operator bool() const;

    //private:
        unsigned int mObject;
    };

}

#endif // RENDERXGLVERTEXBUFFER_HPP_
