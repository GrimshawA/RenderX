#ifndef REX_GL_SHADER_HPP_
#define REX_GL_SHADER_HPP_

#include "../config.hpp"
#include "gl_helpers.hpp"
#include <vector>
#include <string>

namespace rex
{

    /**
        \class gl_shader_program
        \brief Single shader program (OpenGL Shader: GLSL)
    */
    class REX_API gl_shader_program
    {
    public:
        /// Constructs an uninitialized shader
        /// The program identifier is initialized at 0.
        /// This means an invalid shader, which causes, not guaranteed, that the fixed-pipeline is activated
        explicit gl_shader_program();

        /// Safe release
        ~gl_shader_program();

    public: // Shader API

        using ShaderSource = std::string;

        void load(const std::vector<ShaderSource>& sources);

        /// Reverts the shader back to an unitialized state
        void release();

        /// Binds variables in the program to predefined location index
        /// Just pass the location you want to be assigned to the variable name
        /// Calling this function only makes sense BEFORE calling create().
        void addAttributeLocation(unsigned int location, const std::string& name);

        /// Creates and links the program from previously compiled unit processors
        bool create();

        enum ShaderTypes
        {
            VertexUnit = 0,
            FragmentUnit = 1
        };

        /// Compiles a shader to be linked when create() is called
        bool loadShader(ShaderTypes type, const char* source);

        /// Compiles a shader to be linked when create() is called, from a source file
        bool loadShaderFromFile(ShaderTypes type, const std::string& filename);

        /// Binds the shader to the GPU
        void bind() const;

        /// Returns whether or not shaders can be used at the moment
        /// The result of this function depends primarily on the machine you're running the program on
        static bool isAvailable();

        /// Returns the internal id of the currently in-use program by OpenGL
        /// Returns 0 if none is active.
        static unsigned int getCurrentActiveProgram();

        /// Returns the string
        static std::string getVersion();

        void setUniformi(const std::string& uniform, int value);

        bool setUniformMatrix(const std::string& uniform, const float* values);
        bool setUniformTexture(const std::string& uniform, int textureUnit);

        bool setUniformVec4(const std::string& uniform, const float* values);
        bool setUniformVec3(const std::string& uniform, const float* values);
        bool setUniformFloat(const std::string& uniform, float value);

        unsigned int getIdentifier();

    public:
        unsigned int m_id; ///< Internal shader identifier
        std::vector<std::pair<ShaderTypes, unsigned int> > m_shaders; ///< List of compiled shaders
        std::vector<std::pair<unsigned int, std::string> > m_attribs; ///< List of pre-binded attribute locations
    };
}

#endif // REX_GL_SHADER_HPP_
