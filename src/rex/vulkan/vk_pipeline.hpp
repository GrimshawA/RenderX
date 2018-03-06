#ifndef REX_VK_PIPELINE_HPP_
#define REX_VK_PIPELINE_HPP_

#include "../pipeline.hpp"
#include "vk_includes.hpp"

namespace rex
{
    class vk_pipeline
    {
    public:

        explicit vk_pipeline(const vk_device& device, const pipeline_init_info& info);
        ~vk_pipeline();

        void build(VkDevice device, const pipeline_init_info& info);

        VkShaderModule createShaderModule(const std::vector<char>& code);

    private:
        VkPipelineLayout pipelineLayoutInfo;
        VkPipeline       graphicsPipeline;
    };
}

#endif // REX_VK_PIPELINE_HPP_
