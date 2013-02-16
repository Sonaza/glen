#ifndef GLEN_OGL_H
#define GLEN_OGL_H

#include <GL/glew.h>
#include <GL/glfw.h>

#if defined(WIN32)
	#undef APIENTRY
	#undef WINGDIAPI
#endif

#include <glen/glenError.h>

#if defined(DEBUG)

	#define glCheck(x) \
		do { \
			x; \
			GLenum glerr = glGetError(); \
			if (glerr != GL_NO_ERROR) { \
				printf("OpenGL error: 0x%x, %s\nFile: %s, line: %d\n\n", glerr, glenErrStr(glerr), __FILE__, __LINE__); \
			} \
		} while (0)

#else

	#define glCheck(x) x

#endif

// Use a Microsoft Visual Studio Compiler directive to
// force linkage to opengl32.lib import library.
#pragma comment(lib, "opengl32.lib")

#endif