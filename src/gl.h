#pragma once

#include <GL/glew.h>


namespace gl
{


bool gl_init();
GLuint make_simple_texture(const char* path, int &w, int &h);

}