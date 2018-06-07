#include "pipeline.hpp"
#include "device.hpp"

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

    pipeline_builder& pipeline_builder::vertexInput(const vertex_decl& decl)
    {
        m_vertexInput = decl;
        return *this;
    }

    pipeline* pipeline_builder::build(device* dev)
    {
        return dev->createPipeline(*this);
    }
}
