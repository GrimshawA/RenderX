#ifndef REX_PIPELINE_HPP_
#define REX_PIPELINE_HPP_

#include <vector>
#include <string>

namespace rex
{
    class pipeline;
    class device;

    class pipeline_builder
    {
    public:

        pipeline_builder& vertexShader(const std::string& vertexSrc);
        pipeline_builder& fragmentShader(const std::string& fragSrc);

        pipeline* build(device* dev);

    //private:
        std::string vertexSource;
        std::string fragmentSource;
    };

	class pipeline
	{
    public:
        static pipeline_builder builder()
        {
            return pipeline_builder();
        }
	};
}

#endif // REX_PIPELINE_HPP_
