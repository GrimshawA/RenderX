#ifndef REX_GL_DEVICE_HPP_
#define REX_GL_DEVICE_HPP_

#include "../config.hpp"
#include "../device.hpp"

namespace rex
{
    class gl_pipeline;
    class gl_vertex_buffer;

    /**
        \class gl_device
        \brief Wrapper around submitting work to the OpenGL driver
    */
    class REX_API gl_device : public device
    {
    public:
        explicit gl_device();

        void submit(const command_buffer& buffer) override;
        pipeline* createPipeline(const pipeline_builder& info) override;

        vertex_buffer* createVertexBuffer() override;
        void wait() {}

    public:

        void set_pipeline(gl_pipeline* p);
        void draw(gl_vertex_buffer* buffer);

    private:
        gl_pipeline* _pipeline {nullptr};
    };
}

#endif // REX_GL_DEVICE_HPP_
