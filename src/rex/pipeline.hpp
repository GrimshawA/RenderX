#ifndef REX_PIPELINE_HPP_
#define REX_PIPELINE_HPP_

#include <vector>
#include <string>
#include "vertex_decl.hpp"
#include "shader_lang.hpp"

namespace rex
{
    class pipeline;
    class device;

    class pipeline_builder
    {
    public:

        pipeline_builder& vertexShader(const std::string& vertexSrc);
        pipeline_builder& vertexShader(const rex::sl::module& shaderModule);

        pipeline_builder& fragmentShader(const std::string& fragSrc);
        pipeline_builder& fragmentShader(const rex::sl::module& shaderModule);
        pipeline_builder& vertexInput(const vertex_decl& decl);

        // Load an effect file with the shader sources
        pipeline_builder& programSourceFile(const std::string& filename);

        pipeline* build(device* dev);

    //private:
        rex::sl::module m_vertexModule;
        rex::sl::module m_fragModule;

        std::string vertexSource;
        std::string fragmentSource;
        vertex_decl m_vertexInput;
    };

	class pipeline
	{
    public:
        static pipeline_builder builder()
        {
            return pipeline_builder();
        }
	};
}

#endif // REX_PIPELINE_HPP_
