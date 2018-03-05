#ifndef REX_VK_SURFACE_HPP_
#define REX_VK_SURFACE_HPP_

#include "vk_includes.hpp"

namespace rex
{
    /*
     *  vk_surface
     *
     *  Encapsulates a vulkan surface which represents a screen
     *  or a subset of it, to render into.
     *
     *  Once the surface is created, it can have a swap chain associated with it
     *  which have a set of images we can render graphics to.
     */
    class vk_surface
    {
    public:

        ~vk_surface()
        {
            for (auto imageView : swapChainImageViews) {
                vkDestroyImageView(device, imageView, nullptr);
            }

            vkDestroySwapchainKHR(device, swapChain, nullptr);
            vkDestroyDevice(device, nullptr);
            DestroyDebugReportCallbackEXT(instance, callback, nullptr);
            vkDestroySurfaceKHR(instance, surface, nullptr);
            vkDestroyInstance(instance, nullptr);
        }

    private:
         VkSurfaceKHR surface;
         VkSwapchainKHR swapChain;

         std::vector<VkImage> swapChainImages;
         VkFormat swapChainImageFormat;
         VkExtent2D swapChainExtent;
         std::vector<VkImageView> swapChainImageViews;
         std::vector<VkFramebuffer> swapChainFramebuffers;
    };
}

#endif // REX_VK_SURFACE_HPP_
