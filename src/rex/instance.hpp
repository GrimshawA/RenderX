#ifndef REX_INSTANCE_HPP_
#define REX_INSTANCE_HPP_

#include <memory>

namespace rex
{
    enum class api
    {
        Auto,    ///< Choose the api to use based on the platform
        OpenGL,  ///< Use OpenGL as the underlying graphics library
        Vulkan   ///< Use Vulkan as the underlying graphics library
    };

    class device;

	/**
		Parent object of RenderX which encapsulates the API
	*/
    class instance
    {
    public:
        explicit instance() {}

        /*
         *  Get the number of physical devices in the platform
         */
        virtual std::size_t num_devices() = 0;

        /*
         * Create a default logical device to be used for rendering
         */
        virtual std::unique_ptr<device> createDefaultDevice() = 0;

    public:

        static std::unique_ptr<instance> make(api driver);
    };
}

#endif // REX_INSTANCE_HPP_
