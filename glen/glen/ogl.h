#ifndef GLEN_OGL_H
#define GLEN_OGL_H

#include <GL/glew.h>
#include <GL/glfw.h>

#if defined(WIN32)
	#undef APIENTRY
	#undef WINGDIAPI
#endif

/// Use a Microsoft Visual Studio Compiler directive to
/// force linkage to opengl32.lib import library.
/// (Alternatively, one can link to this from command line or from VC project properties)
#pragma comment(lib, "opengl32.lib")

#endif