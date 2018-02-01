#ifndef NephilimGDI_OpenGL3_h__
#define NephilimGDI_OpenGL3_h__

#include <RenderX/RxDevice.h>
#include <RenderX/OpenGL/GDI_OpenGLBase.h>
#include <RenderX/OpenGL/GLShader.h>

class RxFramebufferImpl;

/**
	\class RendererOpenGL
	\brief Renderer specialization for desktop platform's OpenGL
*/
class DAEVA_API GDI_GL3 : public GDI_OpenGLBase
{
public:

	/// All functional shader programs are kept here for safe destruction
	std::vector<detail::GDI_ShaderProgram*> _shaderPrograms;

public:

	/// Initialize OpenGL renderer
	GDI_GL3();

	virtual void init();

	/// Get the name of the adapter
	virtual const char* getAdapterName();

	/// This function will create a new shader program from the raw code
	/// It runs a preprocessing step to identify what portions belong to what shader
	virtual detail::GDI_ShaderProgram* createShader(const String& code);

	/// Create a framebuffer compatible with the renderer
    virtual RxFramebufferImpl* createFramebuffer();

	/// Create a 2D texture compatible with the renderer
    virtual RxTextureImpl* createTexture2D();

	/// Push client-side geometry to the GPU
	/// This is usually slower than using a VBO because the data is uploaded to the GPU every time
	/// Note: This will eventually be the only way to render client-side data
	virtual void draw(const RxVertexArray& vertexData);

	/// Draw a vertex array
	virtual void draw(const VertexArray2D& varray);

	/// This will cancel all shader-related settings and activate the default shader/fixed pipeline
	virtual void setDefaultShader();

        void setTexture(RxTexture* texture) override;

	/// Sets the current render target, nullptr is interpreted as activating a default target
        virtual void setFramebuffer(RxFramebuffer* fbuffer);

	/// Activates the shader for the next drawing calls
	virtual void setShader(detail::GDI_ShaderProgram* program);

	/// Activate a projection matrix
	virtual void setProjectionMatrix(const mat4& projection);

	/// Activate a view matrix
	virtual void setViewMatrix(const mat4& view);

	/// Activate a model matrix
	virtual void setModelMatrix(const mat4& model);

private:
	GLShader m_defaultShader;
};

NEPHILIM_NS_END
#endif // NephilimGDI_OpenGL3_h__
