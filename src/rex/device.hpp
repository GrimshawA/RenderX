#ifndef REX_DEVICE_HPP_
#define REX_DEVICE_HPP_

#include "config.hpp"
#include "command_buffer.hpp"
#include <map>
#include <stack>

namespace rex
{
    class vertex_buffer;
    class pipeline;
    class pipeline_builder;

    /**
        \class device
        \brief Wraps a logical device and provides rendering functionality

        Implementations are graphics renderers, they are able to emit draw calls to an underlying rendering system,
        as well as setting state of the renderer.

        Drawing Vertex Array based drawable with custom shaders:
        - Vertex attributes are activated at location 0, 1 and 2, respectively for Position, Color and Texture coordinates.
        - Have model and projection matrices in your vertex shader if you want them to be set with the camera and world transform of
          the drawable
        - Textures are activated at texture unit 0, as default
        - Whether the vertex array is textured or not, a uniform int textured variable will be set with 1 or 0, for true or false.
    */
    class REX_API device
    {
    public:
        virtual void submit(const command_buffer& buffer) = 0;
        virtual void wait() = 0;
        virtual pipeline* createPipeline(const pipeline_builder& info) = 0;
        virtual vertex_buffer* createVertexBuffer() = 0;

    public:
        void setClearColor(float r, float g, float b, float a)
        {
            _r = r;
            _g = g;
            _b = b;
            _a = a;
        }

    protected:
        float _r, _g, _b, _a;

    };
}

#endif // REX_DEVICE_HPP_
