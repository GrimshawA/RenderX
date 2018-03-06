#ifndef REX_VK_BUFFER_HPP_
#define REX_VK_BUFFER_HPP_

namespace rex
{
    class vk_buffer
    {
    public:
        explicit vk_buffer();
        ~vk_buffer();

    private:
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
    };
}

#endif // REX_VK_BUFFER_HPP_
