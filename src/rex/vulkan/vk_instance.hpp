#ifndef REX_VK_INSTANCE_HPP_
#define REX_VK_INSTANCE_HPP_

#include <vector>
#include <iostream>
#include "instance.hpp"
#include "vk_includes.hpp"
#include "vk_shared.hpp"

namespace rex
{

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;

    bool isComplete() {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};

class vk_instance : public instance
{
public:
    explicit vk_instance();

    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void setupDebugCallback();
    void createLogicalDevice();
    VkPhysicalDevice pickDefaultPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    std::unique_ptr<device> createDefaultDevice() override;
    std::size_t num_devices() override;

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
        std::cout << "validation layer: " << msg << std::endl;

        return VK_FALSE;
    }

private:
    VkInstance instance;
    VkDebugReportCallbackEXT callback;
};
}

#endif // REX_VK_INSTANCE_HPP_
