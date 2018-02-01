#include <RenderX/OpenGL/GDI_OpenGLBase.h>
#include <RenderX/RxVertexBuffer.h>
#include <RenderX/OpenGL/GLHelpers.h>

void GDI_OpenGLBase::DrawIndexed()
{
	glDrawElements(GL_UNSIGNED_SHORT, 19, 10, 0);
}