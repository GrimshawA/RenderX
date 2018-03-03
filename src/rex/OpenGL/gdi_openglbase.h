#ifndef NephilimGDI_OpenGLBase_h__
#define NephilimGDI_OpenGLBase_h__

#include <bitcore/Config.h>
#include <RenderX/RxDevice.h>
#include <RenderX/OpenGL/GLShader.h>

NEPHILIM_NS_BEGIN

/**
	\class GDI_OpenGLBase
	\brief Provides the common functionality for the different GL implementations
*/
class DAEVA_API GDI_OpenGLBase : public RenderCore
{
public:
	/// Orders the driver to draw the index + vertex buffer
	virtual void DrawIndexed();
};

NEPHILIM_NS_END
#endif // NephilimGDI_OpenGLBase_h__
