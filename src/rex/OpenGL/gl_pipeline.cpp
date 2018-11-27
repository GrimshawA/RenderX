#include "gl_pipeline.hpp"
#include "gl_shader_compiler.hpp"

#include <iostream>

namespace rex
{
    gl_pipeline::gl_pipeline(const pipeline_builder& info)
    {
        gl_shader_compiler cv {gl_shader_compiler::vertex_mode};
        gl_shader_compiler cf {gl_shader_compiler::fragment_mode};

        std::string vertexShaderSrc = cv.build(info.m_vertexModule);
        std::string fragShaderSrc = cf.build(info.m_fragModule);

        std::cout << "VERTEX SHADER IS:" << std::endl << vertexShaderSrc << std::endl;

        std::cout << "FRAG SHADER IS:" << std::endl << fragShaderSrc << std::endl;

        shaderProgram.loadShader(gl_shader_program::VertexUnit, info.vertexSource.c_str());
        //shaderProgram.loadShader(gl_shader_program::VertexUnit, vertexShaderSrc.c_str());

        //shaderProgram.loadShader(gl_shader_program::FragmentUnit, fragShaderSrc.c_str());
        shaderProgram.loadShader(gl_shader_program::FragmentUnit, info.fragmentSource.c_str());

        shaderProgram.addAttributeLocation(0, "vertex");
        shaderProgram.addAttributeLocation(1, "color");
        shaderProgram.addAttributeLocation(2, "texCoord");
        shaderProgram.create();
        shaderProgram.bind();

        vertexAttribs.resize(info.m_vertexInput.attributes.size());

        int currOffset = 0;
        for (int i = 0; i < info.m_vertexInput.attributes.size(); ++i)
        {
            vertexAttribs[i].index = i;
            vertexAttribs[i].normalized = false;
            vertexAttribs[i].size = info.m_vertexInput.attributes[i].numComponents;
            vertexAttribs[i].stride = sizeof(float) * 7;
            vertexAttribs[i].type = GL_FLOAT;
            vertexAttribs[i].offset = currOffset;

            currOffset += sizeof(float) * vertexAttribs[i].size;
        }
    }

    gl_pipeline::~gl_pipeline()
    {

    }
}
