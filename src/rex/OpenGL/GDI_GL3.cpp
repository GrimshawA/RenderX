#include <bitcore/Config.h>

#ifdef NEPHILIM_DESKTOP
#include <RenderX/OpenGL/GDI_GL3.h>
#include <RenderX/OpenGL/GLFramebuffer.h>
#include <RenderX/Impl/OpenGL/RxTextureGL.h>
#include <RenderX/OpenGL/GLHelpers.h>
#include <RenderX/RxTexture.h>

#include <bitcore/Logger.h>
#include <bitcore/math/Math.h>
#include <bitcore/math/Matrix.h>
//#include <bitcore/Graphics/View.h>
#include <iostream>

NEPHILIM_NS_BEGIN

static const char gVertexSource[] =
        "#version 120\n"
        "attribute vec4 vertex;\n"
        "attribute vec4 color;\n"
        "attribute vec2 texCoord;\n"
        "uniform mat4 projection = mat4(1);\n"
        "uniform mat4 model = mat4(1);\n"
        "uniform mat4 view = mat4(1);\n"
        "varying vec4 outColor;\n"
        "varying vec2 texUV;\n"
        "void main() {\n"
        "  gl_Position = projection * view * model * vertex;\n"
        "  outColor = color;\n"
        "  texUV = texCoord;\n"
        "}\n";

static const char gFragmentSource[] =
        "#version 120\n"
        "uniform sampler2D texture;\n"
        "varying vec4 outColor;\n"
        "varying vec2 texUV;\n"
        "void main() {\n"
        " if(texture2D(texture,texUV).a == 0) discard;"
        "   gl_FragColor = texture2D(texture, texUV) * outColor;\n"
        "   vec4 c = texture2D(texture, texUV) * outColor;"
        "   gl_FragColor = c * c.a;"
        "}\n";


GDI_GL3::GDI_GL3()
    : GDI_OpenGLBase()
{
    cglPrepareExtensions();

    m_shaderUsageHint = true;
    m_type = OpenGL;
    m_name = "OpenGL";

    m_defaultShader.loadShader(GLShader::VertexUnit, gVertexSource);
    m_defaultShader.loadShader(GLShader::FragmentUnit, gFragmentSource);
    m_defaultShader.addAttributeLocation(0, "vertex");
    m_defaultShader.addAttributeLocation(1, "color");
    m_defaultShader.addAttributeLocation(2, "texCoord");
    m_defaultShader.create();
    m_defaultShader.bind();

    glDisable(GL_LIGHTING);
}

void GDI_GL3::init()
{
    RenderCore::init();
}

const char* GDI_GL3::getAdapterName()
{
    return (char *)glGetString(GL_RENDERER);
}

/// This function will create a new shader program from the raw code
/// It runs a preprocessing step to identify what portions belong to what shader
detail::GDI_ShaderProgram* GDI_GL3::createShader(const String& code)
{
    GLShader* shaderProgram = new GLShader;

    String _vertex;
    String _frag;

    int current_type = 0;
    std::size_t i = 0;
    while (i < code.size())
    {
        if (code[i] == '#' && code.substr(i + 1, 6) == "VERTEX")
        {
            current_type = 1;
            i += 7;
        }
        else if (code[i] == '#' && code.substr(i + 1, 5) == "PIXEL")
        {
            current_type = 2;
            i += 6;
        }
        else if (current_type == 0)
        {
            ++i;
        }
        else
        {
            // add the char to the sources
            if (current_type == 1)
            {
                _vertex += code[i++];
            }
            else if (current_type == 2)
            {
                _frag += code[i++];
            }
        }
    }


    shaderProgram->loadShader(GLShader::VertexUnit, _vertex);
    shaderProgram->loadShader(GLShader::FragmentUnit, _frag);
    shaderProgram->addAttributeLocation(0, "vertex");
    shaderProgram->addAttributeLocation(1, "color");
    shaderProgram->addAttributeLocation(2, "texCoord");
    shaderProgram->addAttributeLocation(3, "normal");
    if (shaderProgram->create())
    {
        Log("SUCCESS CREATESHADER");
    }

    /*std::cout << "Vertex " << std::endl
        << _vertex << std::endl;

    std::cout << "Pixel " << std::endl
        << _frag << std::endl;*/

    _shaderPrograms.push_back(shaderProgram);

    return shaderProgram;
}

void GDI_GL3::setFramebuffer(RxFramebuffer* fbuffer)
{
    if (fbuffer)
    {
        //static_cast<GLFramebuffer*>(fbuffer)->activate();
    }
    else
    {
        glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, 0);
    }
}

void GDI_GL3::setTexture(RxTexture* texture)
{
    static_cast<RxTextureGL*>(texture->_impl)->bind();
}

RxFramebufferImpl* GDI_GL3::createFramebuffer()
{
    GLFramebuffer* fbo = new GLFramebuffer();
    if (!fbo->create())
    {
        Log("Failed to create FBO");
    }
    m_framebuffers.push_back(fbo);
    return fbo;
}

RxTextureImpl* GDI_GL3::createTexture2D()
{
    RxTextureGL* texture = new RxTextureGL();
    m_textures.push_back(texture);
    return texture;
}

void GDI_GL3::activate(pipeline p)
{
    // In OpenGL, activating a pipeline only means keeping state around for using in rendering
    _pipeline = p;
}

void GDI_GL3::apply(command_buffer buffer)
{
    commands = resource_cast<gl_command_buffer>(buffer);

    for (std::size_t i = 0; i < commands.size(); ++i)
    {
        gl_command& cmd = commands[i];

        switch (cmd.type)
        {
            case DRAW_BUFFER: draw(buffer);
            case SET_PIPELINE: activate(pipeline);
        }
    }
}

void GDI_GL3::draw(const RxVertexArray& vertexData)
{
    // draw should activate a pipeline and draw the array
    auto buffer = resource_cast<gl_buffer>(vertexData);
}

void GDI_GL3::draw(const VertexArray2D& varray)
{
    const char* data  = reinterpret_cast<const char*>(&varray.m_vertices[0]);

    if(m_activeShader)
    {
        enableVertexAttribArray(0);
        enableVertexAttribArray(1);
        enableVertexAttribArray(2);

        setVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(VertexArray2D::Vertex), data + 0);
        setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, sizeof(VertexArray2D::Vertex), data + 8);
        setVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(VertexArray2D::Vertex), data + 12);

        drawArrays(varray.geometryType, 0, varray.m_vertices.size());

        disableVertexAttribArray(0);
        disableVertexAttribArray(1);
        disableVertexAttribArray(2);
    }
    else
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(2, GL_FLOAT, sizeof(VertexArray2D::Vertex), data + 0);
        glColorPointer(4, GL_UNSIGNED_BYTE,sizeof(VertexArray2D::Vertex), data + 8);
        glTexCoordPointer(2, GL_FLOAT, sizeof(VertexArray2D::Vertex), data + 12);

        drawArrays(varray.geometryType, 0, varray.m_vertices.size());

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void GDI_GL3::setDefaultShader()
{
    if(m_shaderUsageHint)
    {
        m_activeShader = &m_defaultShader;
        m_defaultShader.bind();
    }
    else
    {
        m_activeShader = NULL;
        glUseProgram(0);
    }
}

void GDI_GL3::setShader(detail::GDI_ShaderProgram* program)
{
    m_activeShader = static_cast<GLShader*>(program);
    if (m_activeShader)
    {
        static_cast<GLShader*>(program)->bind();
    }
}

void GDI_GL3::setProjectionMatrix(const mat4& projection)
{
    RenderCore::setProjectionMatrix(projection);
    if(m_activeShader)
        static_cast<GLShader*>(m_activeShader)->setUniformMatrix("projection", projection.get());
}

void GDI_GL3::setViewMatrix(const mat4& view)
{
    RenderCore::setViewMatrix(view);
    if(m_activeShader)
        static_cast<GLShader*>(m_activeShader)->setUniformMatrix("view", view.get());
}

void GDI_GL3::setModelMatrix(const mat4& model)
{
    RenderCore::setModelMatrix(model);
    if(m_activeShader)
        static_cast<GLShader*>(m_activeShader)->setUniformMatrix("model", model.get());
}

NEPHILIM_NS_END
#endif
