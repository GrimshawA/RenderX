#ifndef REX_GL_PIPELINE_HPP_
#define REX_GL_PIPELINE_HPP_

#include "gl_helpers.hpp"
#include "gl_shader.hpp"
#include "../pipeline.hpp"
#include <memory>

namespace rex
{
    class gl_pipeline : public pipeline
	{
	public:
        explicit gl_pipeline(const pipeline_builder& info);
        ~gl_pipeline();

        gl_shader_program shaderProgram;

        struct vertex_attribute
        {
            int index;
            int size;
            GLenum type; // GL_FLOAT for example
            bool normalized;
            int stride;
            int offset;
        };

        GLenum primitive = GL_TRIANGLES;

        std::vector<vertex_attribute> vertexAttribs;
	};
}

#endif // REX_GL_PIPELINE_HPP_
