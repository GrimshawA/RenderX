#include "gl_helpers.hpp"
#include <iostream>

void cglPrepareExtensions()
{
    auto r = glewInit();

	if (r != GL_NO_ERROR)
		std::cout << "Couldn't load GLEW: " << r << std::endl;

	std::cout << "glCreateShader " << glCreateShader << std::endl;
}
