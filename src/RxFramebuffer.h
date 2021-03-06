#ifndef RENDERXFRAMEBUFFER_H__
#define RENDERXFRAMEBUFFER_H__

#include <bitcore/Config.h>

class RxTexture;
class RxFramebufferImpl;

/**
	\class DvFramebuffer
	\brief A graphical frame buffer to render things on
*/
class DAEVA_API RxFramebuffer
{
public:
    RxFramebuffer();
    virtual ~RxFramebuffer();

	virtual void activate();

	virtual void setRenderbuffer();
	virtual void setTexture(const RxTexture& texture);
	virtual void setDepthBuffer(int width, int height);

private:
    RxFramebufferImpl* m_impl = nullptr;
};

#endif // RENDERXFRAMEBUFFER_H__
