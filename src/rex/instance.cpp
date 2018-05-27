#include "instance.hpp"

#ifdef REX_USE_VULKAN
#include "vulkan/vk_instance.hpp"
#endif
#include "opengl/gl_instance.hpp"

namespace rex
{
    std::unique_ptr<instance> instance::make(api driver)
    {
        switch (driver)
        {
        case api::OpenGL:
            return std::make_unique<gl_instance>();
#ifdef REX_USE_VULKAN
        case api::Vulkan:
        case api::Auto:
            return std::make_unique<vk_instance>();
        }
#endif
    }
    }
}
