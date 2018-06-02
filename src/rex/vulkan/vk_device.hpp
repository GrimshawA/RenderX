#ifndef REX_VK_DEVICE_HPP_
#define REX_VK_DEVICE_HPP_

#include "../device.hpp"
#include "../command_buffer.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace rex
{
    class vk_device : public device
	{
	public:
        explicit vk_device();
        explicit vk_device(VkDevice device);
        virtual ~vk_device();

        void submit(const command_buffer& buffer) override;
        virtual pipeline* createPipeline(const pipeline_builder& info) override
        {
            return nullptr;
        }
        vertex_buffer* createVertexBuffer() override
        {
            return nullptr;
        }
        texture* createTexture() override
        {
            return nullptr;
        }

        void wait() override;

//        void createRenderPass() {
//            VkAttachmentDescription colorAttachment = {};
//            colorAttachment.format = swapChainImageFormat;
//            colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
//            colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//            colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//            colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//            colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//            colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//            colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

//            VkAttachmentReference colorAttachmentRef = {};
//            colorAttachmentRef.attachment = 0;
//            colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

//            VkSubpassDescription subpass = {};
//            subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
//            subpass.colorAttachmentCount = 1;
//            subpass.pColorAttachments = &colorAttachmentRef;

//            VkSubpassDependency dependency = {};
//            dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
//            dependency.dstSubpass = 0;
//            dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//            dependency.srcAccessMask = 0;
//            dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//            dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

//            VkRenderPassCreateInfo renderPassInfo = {};
//            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
//            renderPassInfo.attachmentCount = 1;
//            renderPassInfo.pAttachments = &colorAttachment;
//            renderPassInfo.subpassCount = 1;
//            renderPassInfo.pSubpasses = &subpass;
//            renderPassInfo.dependencyCount = 1;
//            renderPassInfo.pDependencies = &dependency;

//            if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
//                throw std::runtime_error("failed to create render pass!");
//            }
//        }

//        void createCommandPool() {
//            QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

//            VkCommandPoolCreateInfo poolInfo = {};
//            poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
//            poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;

//            if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
//                throw std::runtime_error("failed to create command pool!");
//            }
//        }

//        void createCommandBuffers() {
//            commandBuffers.resize(swapChainFramebuffers.size());

//            VkCommandBufferAllocateInfo allocInfo = {};
//            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//            allocInfo.commandPool = commandPool;
//            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//            allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

//            if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
//                throw std::runtime_error("failed to allocate command buffers!");
//            }

//            for (size_t i = 0; i < commandBuffers.size(); i++) {
//                VkCommandBufferBeginInfo beginInfo = {};
//                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//                beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

//                vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

//                VkRenderPassBeginInfo renderPassInfo = {};
//                renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//                renderPassInfo.renderPass = renderPass;
//                renderPassInfo.framebuffer = swapChainFramebuffers[i];
//                renderPassInfo.renderArea.offset = {0, 0};
//                renderPassInfo.renderArea.extent = swapChainExtent;

//                VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
//                renderPassInfo.clearValueCount = 1;
//                renderPassInfo.pClearValues = &clearColor;

//                vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

//                    vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

//                    vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

//                vkCmdEndRenderPass(commandBuffers[i]);

//                if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
//                    throw std::runtime_error("failed to record command buffer!");
//                }
//            }
//        }

        

//        void drawFrame() {
//            uint32_t imageIndex;
//            vkAcquireNextImageKHR(device, swapChain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

//            VkSubmitInfo submitInfo = {};
//            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

//            VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
//            VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
//            submitInfo.waitSemaphoreCount = 1;
//            submitInfo.pWaitSemaphores = waitSemaphores;
//            submitInfo.pWaitDstStageMask = waitStages;

//            submitInfo.commandBufferCount = 1;
//            submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

//            VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
//            submitInfo.signalSemaphoreCount = 1;
//            submitInfo.pSignalSemaphores = signalSemaphores;

//            if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
//                throw std::runtime_error("failed to submit draw command buffer!");
//            }

//            VkPresentInfoKHR presentInfo = {};
//            presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

//            presentInfo.waitSemaphoreCount = 1;
//            presentInfo.pWaitSemaphores = signalSemaphores;

//            VkSwapchainKHR swapChains[] = {swapChain};
//            presentInfo.swapchainCount = 1;
//            presentInfo.pSwapchains = swapChains;

//            presentInfo.pImageIndices = &imageIndex;

//            vkQueuePresentKHR(presentQueue, &presentInfo);

//            vkQueueWaitIdle(presentQueue);
//        }

    private:
        VkDevice _device;

        VkRenderPass renderPass;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
	};
}

#endif // REX_VK_DEVICE_HPP_
