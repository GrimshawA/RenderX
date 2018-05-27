#ifndef REX_SHADER_HPP_
#define REX_SHADER_HPP_

#include "config.hpp"

namespace rex
{
	class shader
	{
	public:
		explicit shader()
		{
			
		}
	};
}

namespace detail
{
class GDI_ShaderProgram;
}

class REX_API ShaderSource
{
public:
    std::string source;
    int type;
};

/**
    \class Shader
    \brief Encapsulates a shader program
*/
class REX_API Shader
{
public:
    enum Types
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        GEOMETRY_SHADER
    };

public:
    Shader();
    Shader(const Shader& other);
    ~Shader();

    // Compile the shader from source
    void load(const std::vector<ShaderSource>& sources);

    Shader& operator=(const Shader& other);

    void release();

private:
    detail::GDI_ShaderProgram* m_impl;
};

namespace detail {

    /**
        \class GDI_ShaderProgram
        \brief Interface for implementing shader programs for different graphics API's
    */
    class REX_API GDI_ShaderProgram
    {
    public:

        virtual void load(const std::vector<ShaderSource>& sources) = 0;

        /// Check if the program has a geometry shader
        virtual bool hasGeometryShader(){
            return false;
        }

        /// Check if the program has a domain shader
        virtual bool hasDomainShader(){
            return false;
        }

        /// Check if the program has a hull shader
        virtual bool hasHullShader(){
            return false;
        }

        /// Check if the program has a tesselation shader
        virtual bool hasTesselationShader(){
            return false;
        }


        int refCount;
    };
}
#endif // REX_SHADER_HPP_
