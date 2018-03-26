#include "instance.hpp"
#include "vulkan/vk_instance.hpp"
#include "opengl/gl_instance.hpp"

namespace rex
{
    std::unique_ptr<instance> instance::make(api driver)
    {
        switch (driver)
        {
        case api::OpenGL:
            return std::make_unique<gl_instance>();

        case api::Vulkan:
        case api::Auto:
            return std::make_unique<vk_instance>();
        }
    }
}
