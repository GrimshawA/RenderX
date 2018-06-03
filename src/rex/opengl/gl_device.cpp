#include "gl_device.hpp"
#include "gl_pipeline.hpp"
#include "gl_vertex_buffer.hpp"
#include "gl_default_shaders.hpp"
#include "gl_texture.hpp"

namespace rex
{
    gl_device::gl_device()
    {
        cglPrepareExtensions();
    }

    void gl_device::submit(const command_buffer& buffer)
    {
        for (std::size_t i = 0; i < buffer._cmds.size(); ++i)
        {
            auto& cmd = buffer._cmds[i];

            switch(cmd.type)
            {
                case command_type::CLEAR_COLOR:
                    glClearColor(_r, _g, _b, _a);
                    glClear(GL_COLOR_BUFFER_BIT);
                break;

                case command_type::LOAD_GEOMETRY: {
                    auto* gl_vbo = (gl_vertex_buffer*)cmd.vertexUpload.vbo;
                    glBindBuffer(GL_ARRAY_BUFFER, gl_vbo->mObject);
                    glBufferData(GL_ARRAY_BUFFER, cmd.vertexUpload.size, cmd.vertexUpload.data, GL_STATIC_DRAW);
                    break;
                }

                case command_type::DRAW: {

                    auto* gl_vbo = (gl_vertex_buffer*)cmd.arrayDraw.vbo;
                    gl_vbo->bind();
                    glCullFace(GL_NONE);
                    glDrawArrays(_pipeline->primitive, cmd.arrayDraw.offset, cmd.arrayDraw.size);
                    break;
                }

                case command_type::SET_PIPELINE: {
                    gl_pipeline& pipe = static_cast<gl_pipeline&>(*cmd.pipe);
                    _pipeline = &pipe;
                    pipe.shaderProgram.bind();

                    for (int i = 0; i < pipe.vertexAttribs.size(); ++i)
                    {
                        auto& attrib = pipe.vertexAttribs[i];
                        glEnableVertexAttribArray(i);
                        glVertexAttribPointer(i, attrib.size, attrib.type, attrib.normalized,
                                              attrib.stride, (void*) attrib.offset);
                    }
                    break;
                }
            }
        }
    }

    pipeline* gl_device::createPipeline(const pipeline_builder& info)
    {
        gl_pipeline* p = new gl_pipeline(info);
        return p;
    }

    vertex_buffer* gl_device::createVertexBuffer()
    {
        gl_vertex_buffer* vbo = new gl_vertex_buffer;
        vbo->create();
        return vbo;
    }

    texture* gl_device::createTexture()
    {
        return new gl_texture();
    }

    void gl_device::set_pipeline(gl_pipeline* p)
    {
        _pipeline = p;

        // Activate the program the pipeline contains
        //glUseProgram(p->program->m_id);
    }

    void gl_device::draw(gl_vertex_buffer* buffer)
    {
//        glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId1);         // for vertex coordinates
//        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vboId2); // for indices

//        // do same as vertex array except pointer
//        glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
//        glVertexPointer(3, GL_FLOAT, 0, 0);               // last param is offset, not ptr

//        // draw 6 quads using offset of index array
//        glDrawElements(_pipeline.primitive, 24, GL_UNSIGNED_BYTE, 0);

//        glDisableClientState(GL_VERTEX_ARRAY);            // deactivate vertex array

//        // bind with 0, so, switch back to normal pointer operation
//        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
//        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }
}

///// This function will create a new shader program from the raw code
///// It runs a preprocessing step to identify what portions belong to what shader
//detail::GDI_ShaderProgram* gl_device::createShader(const String& code)
//{
//    GLShader* shaderProgram = new GLShader;

//    String _vertex;
//    String _frag;

//    int current_type = 0;
//    std::size_t i = 0;
//    while (i < code.size())
//    {
//        if (code[i] == '#' && code.substr(i + 1, 6) == "VERTEX")
//        {
//            current_type = 1;
//            i += 7;
//        }
//        else if (code[i] == '#' && code.substr(i + 1, 5) == "PIXEL")
//        {
//            current_type = 2;
//            i += 6;
//        }
//        else if (current_type == 0)
//        {
//            ++i;
//        }
//        else
//        {
//            // add the char to the sources
//            if (current_type == 1)
//            {
//                _vertex += code[i++];
//            }
//            else if (current_type == 2)
//            {
//                _frag += code[i++];
//            }
//        }
//    }


//    shaderProgram->loadShader(GLShader::VertexUnit, _vertex);
//    shaderProgram->loadShader(GLShader::FragmentUnit, _frag);
//    shaderProgram->addAttributeLocation(0, "vertex");
//    shaderProgram->addAttributeLocation(1, "color");
//    shaderProgram->addAttributeLocation(2, "texCoord");
//    shaderProgram->addAttributeLocation(3, "normal");
//    if (shaderProgram->create())
//    {
//        Log("SUCCESS CREATESHADER");
//    }

//    /*std::cout << "Vertex " << std::endl
//        << _vertex << std::endl;

//    std::cout << "Pixel " << std::endl
//        << _frag << std::endl;*/

//    _shaderPrograms.push_back(shaderProgram);

//    return shaderProgram;
//}

//void gl_device::setFramebuffer(RxFramebuffer* fbuffer)
//{
//    if (fbuffer)
//    {
//        //static_cast<GLFramebuffer*>(fbuffer)->activate();
//    }
//    else
//    {
//        glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, 0);
//    }
//}

//void gl_device::setTexture(rex::texture* texture)
//{
//    static_cast<rex::textureGL*>(texture->_impl)->bind();
//}

//RxFramebufferImpl* gl_device::createFramebuffer()
//{
//    GLFramebuffer* fbo = new GLFramebuffer();
//    if (!fbo->create())
//    {
//        Log("Failed to create FBO");
//    }
//    m_framebuffers.push_back(fbo);
//    return fbo;
//}

//rex::textureImpl* gl_device::createTexture2D()
//{
//    rex::textureGL* texture = new rex::textureGL();
//    m_textures.push_back(texture);
//    return texture;
//}

//void gl_device::draw(const VertexArray2D& varray)
//{
//    const char* data  = reinterpret_cast<const char*>(&varray.m_vertices[0]);

//    if(m_activeShader)
//    {
//        enableVertexAttribArray(0);
//        enableVertexAttribArray(1);
//        enableVertexAttribArray(2);

//        setVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(VertexArray2D::Vertex), data + 0);
//        setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, sizeof(VertexArray2D::Vertex), data + 8);
//        setVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(VertexArray2D::Vertex), data + 12);

//        drawArrays(varray.geometryType, 0, varray.m_vertices.size());

//        disableVertexAttribArray(0);
//        disableVertexAttribArray(1);
//        disableVertexAttribArray(2);
//    }
//    else
//    {
//        glEnableClientState(GL_VERTEX_ARRAY);
//        glEnableClientState(GL_COLOR_ARRAY);
//        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//        glVertexPointer(2, GL_FLOAT, sizeof(VertexArray2D::Vertex), data + 0);
//        glColorPointer(4, GL_UNSIGNED_BYTE,sizeof(VertexArray2D::Vertex), data + 8);
//        glTexCoordPointer(2, GL_FLOAT, sizeof(VertexArray2D::Vertex), data + 12);

//        drawArrays(varray.geometryType, 0, varray.m_vertices.size());

//        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//        glDisableClientState(GL_COLOR_ARRAY);
//        glDisableClientState(GL_VERTEX_ARRAY);
//    }
//}
