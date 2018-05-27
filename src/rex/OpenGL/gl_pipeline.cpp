#include "gl_pipeline.hpp"

namespace rex
{
    gl_pipeline::gl_pipeline(const pipeline_builder& info)
    {
        shaderProgram.loadShader(gl_shader_program::VertexUnit, info.vertexSource.c_str());
        shaderProgram.loadShader(gl_shader_program::FragmentUnit, info.fragmentSource.c_str());
        shaderProgram.addAttributeLocation(0, "vertex");
        shaderProgram.addAttributeLocation(1, "color");
        shaderProgram.addAttributeLocation(2, "texCoord");
        shaderProgram.create();
        shaderProgram.bind();
    }

    gl_pipeline::~gl_pipeline()
    {

    }

//    gl_pipeline* gl_pipeline::make_default()
//    {
//        //    m_defaultShader.loadShader(GLShader::VertexUnit, gVertexSource);
//        //    m_defaultShader.loadShader(GLShader::FragmentUnit, gFragmentSource);
//        //    m_defaultShader.addAttributeLocation(0, "vertex");
//        //    m_defaultShader.addAttributeLocation(1, "color");
//        //    m_defaultShader.addAttributeLocation(2, "texCoord");
//        //    m_defaultShader.create();
//        //    m_defaultShader.bind();
//        return nullptr;
//    }
}
