#ifndef PARABOLA_RENDERERGLES_H
#define PARABOLA_RENDERERGLES_H

#include <Nephilim/Platform.h>
#include <Nephilim/GDI/GDI_GraphicsDevice.h>

#ifdef PARABOLA_ANDROID
#include <GLES/gl.h>
#include <GLUES/glu.h>
#endif

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class RendererGLES
	\brief Renderer specialization for OpenGL ES 1.1
*/
class NEPHILIM_API RendererGLES : public RenderCore
{
public:
	RendererGLES();


	/// Draw a vertex array
	virtual void draw(const VertexArray2D& varray);

	/// Clear the bound buffer
	virtual void clear();

	void applyView(const View &view);
	/// Anything that inherits Drawable can be drawn using a renderer
	virtual void draw(Drawable &drawable);

	virtual void prepare(int w, int h);
	//virtual void drawDebugQuad(float x, float y, float angle, float width, float height, Color color);
	virtual void display();
	virtual void drawDebugTriangleFan(Vector2* vlist, int vcount, Color color);
	//virtual void drawDebugCircle(Vector2 center, float radius, Vector2 axis, Color color);
	virtual void drawVertexArray(VertexArray2D &vertexArray);
	void drawDebugLine(Vector2 begin, Vector2 end, Color color);
};

NEPHILIM_NS_END

#endif