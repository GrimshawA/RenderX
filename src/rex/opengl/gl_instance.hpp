#ifndef REX_GL_INSTANCE_HPP_
#define REX_GL_INSTANCE_HPP_

#include "instance.hpp"
#include "device.hpp"

namespace rex
{
	class gl_instance : public instance
	{
	public:
		explicit gl_instance()
		{
			
		}

        std::unique_ptr<device> createDefaultDevice() override
        {
            return nullptr;
        }

        std::size_t num_devices() override
        {
            return 0;
        }
	};
}

#endif // REX_GL_INSTANCE_HPP_
