#include <RenderX/OpenGL/GLHelpers.h>

void cglPrepareExtensions()
{
#if defined NEPHILIM_DESKTOP
	glewInit();
#endif
}
