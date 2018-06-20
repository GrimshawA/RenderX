#include "pipeline.hpp"
#include "device.hpp"
#include "shader_parser.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>

namespace rex
{
    pipeline_builder& pipeline_builder::vertexShader(const std::string& vertexSrc)
    {
        vertexSource = vertexSrc;
        return *this;
    }

    pipeline_builder& pipeline_builder::vertexShader(const rex::sl::module& shaderModule)
    {
        m_vertexModule = shaderModule;
        return *this;
    }

    pipeline_builder& pipeline_builder::fragmentShader(const std::string& fragSrc)
    {
        fragmentSource = fragSrc;
        return *this;
    }

    pipeline_builder& pipeline_builder::fragmentShader(const rex::sl::module& shaderModule)
    {
        m_fragModule = shaderModule;
        return *this;
    }

    pipeline_builder& pipeline_builder::vertexInput(const vertex_decl& decl)
    {
        m_vertexInput = decl;
        return *this;
    }

    pipeline_builder& pipeline_builder::programSourceFile(const std::string& filename)
    {
        std::ifstream t(filename);
        std::string str;

        t.seekg(0, std::ios::end);
        str.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        str.assign((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

        std::cout << "Original effect sources:" << str << std::endl;

        sl::module ast = sl::parser::build(str);

        // Build both shaders from the same program sources
        m_vertexModule = ast;
        m_fragModule = ast;

        return *this;
    }

    pipeline* pipeline_builder::build(device* dev)
    {
        return dev->createPipeline(*this);
    }
}
