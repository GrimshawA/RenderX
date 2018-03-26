#ifndef REX_VK_SHARED_HPP_
#define REX_VK_SHARED_HPP_

namespace rex
{
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
}

#endif // REX_VK_SHARED_HPP_
