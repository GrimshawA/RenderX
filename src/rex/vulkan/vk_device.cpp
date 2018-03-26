#include "vk_device.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

namespace rex
{
    vk_device::vk_device()
    {

    }

    vk_device::vk_device(VkDevice device)
    {

    }

    vk_device::~vk_device()
    {
        vkDestroyDevice(_device, nullptr);
    }

    void vk_device::submit(const command_buffer& buffer)
    {
//        VkCommandBufferBeginInfo beginInfo = {};
//        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

//        vkBeginCommandBuffer(commandBuffers[0], &beginInfo);

//        VkRenderPassBeginInfo renderPassInfo = {};
//        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//        renderPassInfo.renderPass = renderPass;
//        renderPassInfo.framebuffer = swapChainFramebuffers[0];
//        renderPassInfo.renderArea.offset = {0, 0};
//        renderPassInfo.renderArea.extent = swapChainExtent;

//        VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
//        renderPassInfo.clearValueCount = 1;
//        renderPassInfo.pClearValues = &clearColor;

//        vkCmdBeginRenderPass(commandBuffers[0], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

//        for (std::size_t i = 0; i < buffer._cmds.size(); ++i)
//        {
//            auto& cmd = buffer._cmds[i];

//            switch (cmd.type)
//            {
//                case command_type::BIND_INDEX_BUFFER:
//                case command_type::BIND_VERTEX_BUFFER:
//                    VkBuffer vertexBuffers[] = {vertexBuffer};
//                    VkDeviceSize offsets[] = {0};
//                    vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
//                case command_type::CLEAR_COLOR:
//                case command_type::CLEAR_DEPTH:
//                case command_type::DISPATCH:
//                case command_type::DISPATCH_INDIRECT:
//                case command_type::DRAW:
//                    vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(vertices.size()), 1, 0, 0);
//                case command_type::DRAW_INDEXED:
//                case command_type::DRAW_INDEXED_INDIRECT:
//                case command_type::DRAW_INDIRECT:
//                case command_type::SET_PIPELINE:
//                    vkCmdBindPipeline(commandBuffers[0], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
//                break;
//                case command_type::SET_BLEND_CONSTANTS:
//                case command_type::SET_LINE_WIDTH:
//                case command_type::SET_SCISSOR:
//                    vkCmdSetScissor(commandBuffers[0], 0, 0, 0);
//                case command_type::SET_VIEWPORT:
//                default:;
//            }
//        }

//        vkCmdEndRenderPass(commandBuffers[0]);

//        if (vkEndCommandBuffer(commandBuffers[0]) != VK_SUCCESS) {
//            throw std::runtime_error("failed to record command buffer!");
//        }
    }

    void vk_device::wait()
    {
        vkDeviceWaitIdle(_device);
    }
}

