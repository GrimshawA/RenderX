#ifndef REX_PIPELINE_HPP_
#define REX_PIPELINE_HPP_

namespace rex
{
    class pipeline_init_info
    {
    public:
        std::vector<char> vertex_shader_src = "shaders/vert.spv";
        std::vector<char> fragment_shader_src = "shaders/frag.spv";
    };

	class pipeline
	{

	};
}

#endif // REX_PIPELINE_HPP_
