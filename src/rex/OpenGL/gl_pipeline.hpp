#ifndef REX_GL_PIPELINE_HPP_
#define REX_GL_PIPELINE_HPP_

#include "gl_shader.hpp"
#include <memory>

namespace rex
{
    class gl_pipeline
	{
	public:
        ~gl_pipeline();

        static gl_pipeline* make_default();

    public:
        gl_shader_program* program {nullptr};
	};
}

#endif // REX_GL_PIPELINE_HPP_
