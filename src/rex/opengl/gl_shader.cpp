#include "gl_shader.hpp"

namespace rex
{
    gl_shader_program::gl_shader_program()
        : m_id(0)
    {
    }

    gl_shader_program::~gl_shader_program()
    {
        release();
    }

    void gl_shader_program::load(const std::vector<ShaderSource>& sources)
    {
//        for(auto& it : sources)
//        {
//            if (it.type == Shader::VERTEX_SHADER)
//                loadShader(GLShader::VertexUnit, it.source.c_str());
//            else if (it.type == Shader::FRAGMENT_SHADER)
//                loadShader(GLShader::FragmentUnit, it.source.c_str());
//        }

//        addAttributeLocation(0, "vertex");
//        addAttributeLocation(1, "color");
//        addAttributeLocation(2, "texCoord");

//        create();

//        bind();
    }

    void gl_shader_program::release()
    {
        if(m_id > 0)
        {
            // Attach compiled shaders
            for(std::vector<std::pair<ShaderTypes, unsigned int> >::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
            {
                glDeleteShader(static_cast<GLuint>(it->second));
            }

            glDeleteProgram(m_id);

            m_shaders.clear();
            m_attribs.clear();
            m_id = 0;
        }
    }

    void gl_shader_program::addAttributeLocation(unsigned int location, const std::string& name)
    {
        m_attribs.push_back(std::make_pair(location,name));
    }

    std::string getFileContents(const std::string& filename)
    {
        return std::string();
//        File myFile(filename, IODevice::TextRead);
//        if(!myFile)
//            return "";

//        String contents;

//        while(!myFile.atEnd())
//            contents += myFile.getChar();

//        contents += '\0';

//        return contents;
    }

    bool gl_shader_program::loadShaderFromFile(ShaderTypes type, const std::string& filename)
    {
        bool success = false;

        GLuint shader = 0;

        switch(type)
        {
        case VertexUnit:	shader = glCreateShader(GL_VERTEX_SHADER);	break;
        case FragmentUnit:	shader = glCreateShader(GL_FRAGMENT_SHADER);   break;
        }

        std::string shaderCode = getFileContents(filename);
        const char* source = shaderCode.c_str();

        if (shader)
        {
            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);
            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
                if (infoLen) {
                    char* buf = new char[infoLen];
                    if (buf) {
                        glGetShaderInfoLog(shader, infoLen, NULL, buf);
                        //PRINTLOG("GLSL", "Failed to load shader: %s\n", buf);
                        std::string mstr(buf);
//                        mstr.removeCharacter('\r');
//                        mstr.removeCharacter('\n');
//                        Log("Error: %s", mstr.c_str());
                        delete [] buf;
                    }
                    glDeleteShader(shader);
                    shader = 0;
                }
            }
            else
            {
                m_shaders.push_back(std::make_pair(type, static_cast<unsigned int>(shader)));
                success = true;
            }
        }

        return success;
    }

    bool gl_shader_program::loadShader(ShaderTypes type, const char* source)
    {
        bool success = false;

        GLuint shader = 0;

        switch(type)
        {
        case VertexUnit:	shader = glCreateShader(GL_VERTEX_SHADER);	break;
        case FragmentUnit:	shader = glCreateShader(GL_FRAGMENT_SHADER);   break;
        }

        if (shader) {
            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);
            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
                if (infoLen) {
                    char* buf = new char[infoLen];
                    if (buf) {
                        glGetShaderInfoLog(shader, infoLen, NULL, buf);
                        //PRINTLOG("GLSL", "Failed to load shader: %s\n", buf);
                        std::string mstr(buf);
//                        mstr.removeCharacter('\r');
//                        mstr.removeCharacter('\n');
//                        Log("Error: %s", mstr.c_str());
                        //std::cout << "GLSL: " << mstr << std::endl;
                        delete [] buf;
                    }
                    glDeleteShader(shader);
                    shader = 0;
                }
            }
            else
            {
                m_shaders.push_back(std::make_pair(type, static_cast<unsigned int>(shader)));
                success = true;
            }
        }

        return success;
    }

    void gl_shader_program::bind() const
    {
        glUseProgram(static_cast<GLuint>(m_id));
    }

    unsigned int gl_shader_program::getIdentifier()
    {
        return m_id;
    }

    bool gl_shader_program::create()
    {
        // There must be some shaders to create a program
        if(m_shaders.empty()) return false;

        bool success = false;

        GLuint id = glCreateProgram();
        if(id)
        {
            // Bind attribute locations
            for(std::vector<std::pair<unsigned int, std::string> >::iterator it = m_attribs.begin(); it != m_attribs.end(); ++it)
            {
                glBindAttribLocation(id, static_cast<GLuint>(it->first), static_cast<const GLchar*>(it->second.c_str()));
            }

            // Attach compiled shaders
            for(std::vector<std::pair<ShaderTypes, unsigned int> >::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
            {
                glAttachShader(id, static_cast<GLuint>(it->second));
            }

            // Link the program
            glLinkProgram(id);

            GLint linkStatus = GL_FALSE;
            glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
            if (linkStatus != GL_TRUE)
            {
                // -- re do
                GLint bufLength = 0;
                glGetProgramiv(id, GL_INFO_LOG_LENGTH, &bufLength);
                if (bufLength) {
                    char* buf = new char[bufLength+1];
                    if (buf) {
                        glGetProgramInfoLog(id, bufLength, NULL, buf);
                        buf[bufLength] = '\0';
                        std::string mstr(buf);
//                        mstr.removeCharacter('\r');
//                        mstr.removeCharacter('\n');
//                        Log("Error: %s", mstr.c_str());
                        //std::cout << "GLSL: " << mstr << std::endl;
                        //PRINTLOG("GLSL", "Failed to link shader program(%d): %s\n",mstr.length(), mstr.c_str());
                        delete [] buf;
                    }
                }
                // --

                glDeleteProgram(id);
                id = 0;
            }
            else success = true;
        }
        m_id = static_cast<unsigned int>(id);
        return success;
    }

    void gl_shader_program::setUniformi(const std::string& uniform, int value)
    {
        bind();
        GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
        if(uniform_id != -1)
        {
            glUniform1i(uniform_id, value);
        }
    }

    bool gl_shader_program::setUniformMatrix(const std::string& uniform, const float* values)
    {
        bind();
        GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
        if(uniform_id != -1)
        {
            glUniformMatrix4fv(uniform_id, 1, GL_FALSE, values);
            return true;
        }
        return false;
    }

    bool gl_shader_program::setUniformVec4(const std::string& uniform, const float* values)
    {
        bind();
        GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
        if(uniform_id != -1)
        {
            glUniform4fv(uniform_id, 1, values);
            return true;
        }
        return false;
    }

    bool gl_shader_program::setUniformVec3(const std::string& uniform, const float* values)
    {
        bind();
        GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
        if(uniform_id != -1)
        {
            glUniform3fv(uniform_id, 1, values);
            return true;
        }
        return false;
    }

    bool gl_shader_program::setUniformFloat(const std::string& uniform, float value)
    {
        bind();
        GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
        if(uniform_id != -1)
        {
            glUniform1f(uniform_id, value);
            return true;
        }
        return false;
    }

    bool gl_shader_program::setUniformTexture(const std::string& uniform, int textureUnit)
    {
        bind();
        GLint uniform_id = glGetUniformLocation(m_id, uniform.c_str());
        if(uniform_id != -1)
        {
            glUniform1i(uniform_id, textureUnit);
            return true;
        }
        return false;
    }

    bool gl_shader_program::isAvailable()
    {
        return true;
    }

    unsigned int gl_shader_program::getCurrentActiveProgram()
    {
        GLint id;
        glGetIntegerv(GL_CURRENT_PROGRAM, &id);
        return static_cast<unsigned int>(id);
    }

    std::string gl_shader_program::getVersion()
    {
        const GLubyte* str = glGetString(GL_SHADING_LANGUAGE_VERSION);
        return reinterpret_cast<const char*>(str);
    }
}
