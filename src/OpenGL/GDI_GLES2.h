#ifndef NephilimRendererGLES2_h__
#define NephilimRendererGLES2_h__

#include <Nephilim/GDI/GL/GDI_OpenGLBase.h>
#include <Nephilim/GDI/GDI_GraphicsDevice.h>
#include <Nephilim/GDI/GL/GLShader.h>

NEPHILIM_NS_BEGIN

class GLShader;

/**
	\class RendererGLES2
	\brief Renderer specialization for OpenGL ES 2.0
*/
class NEPHILIM_API RendererGLES2 : public GDI_OpenGLBase
{
public:
	RendererGLES2();

	/// Draw a vertex array
	virtual void draw(const VertexArray2D& varray);

	/// This will cancel all shader-related settings and activate the default shader/fixed pipeline
	virtual void setDefaultShader();

	virtual void reloadDefaultShader();

	/// Set the current projection matrix
	virtual void setProjectionMatrix(const mat4& projection);

	/// Set the current view matrix
	virtual void setViewMatrix(const mat4& view);

	/// Set the current model matrix
	virtual void setModelMatrix(const mat4& model);

	//void drawDebugCircle(Vector2 center, float radius, Vector2 axis, Color color);
	void applyView(const View &view);

	GLShader m_defaultShader;

};


NEPHILIM_NS_END

#endif // NephilimRendererGLES2_h__
