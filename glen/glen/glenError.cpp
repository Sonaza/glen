#include <glen/glenError.h>

#define GL_NO_ERROR 0
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_VALUE 0x0501
#define GL_INVALID_OPERATION 0x0502
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_OUT_OF_MEMORY 0x0505
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506

const char* glenErrStr(unsigned int error)
{
	switch(error)
	{
	case GL_INVALID_ENUM:					return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:					return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:				return "GL_INVALID_OPERATION";
	case GL_STACK_OVERFLOW:					return "GL_STACK_OVERFLOW";
	case GL_STACK_UNDERFLOW:				return "GL_STACK_UNDERFLOW";
	case GL_OUT_OF_MEMORY:					return "GL_OUT_OF_MEMORY";
	case GL_INVALID_FRAMEBUFFER_OPERATION:	return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case GL_NO_ERROR:						return "GL_NO_ERROR";
	}

	return "GlenErrStr: Invalid Error Code";
}