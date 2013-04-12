#ifndef GLEN_OPENGL_HPP
#define GLEN_OPENGL_HPP

#pragma warning( push )

	// Disable macro redefinition warning
	// because compiler screams about APIENTRY and WINGDIAPI
	#pragma warning( disable : 4005 )
	
	#define _CRT_SECURE_NO_DEPRECATE

	#include <GL/glew.h>
	
	#define SFML_STATIC

	#include <SFML/Window.hpp>
	#include <SFML/OpenGL.hpp>

#pragma warning( pop ) 

// Outputs OpenGL error code as string
extern const char* glenErrorString(unsigned int error);

#if defined(DEBUG)

	#define glCheck(x) \
		do { \
			x; \
			GLenum glerr = glGetError(); \
			if (glerr != GL_NO_ERROR) { \
				printf("OpenGL error: 0x%x, %s\nFile: %s, line: %d\n\n", glerr, glenErrorString(glerr), __FILE__, __LINE__); \
			} \
		} while (0)

#else

	#define glCheck(x) x

#endif

// Use a Microsoft Visual Studio Compiler directive to
// force linkage to opengl32.lib import library.
#pragma comment(lib, "opengl32.lib")

#endif