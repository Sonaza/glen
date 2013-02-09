#include <glen/Window/Window.hpp>
#include <glen/ogl.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace glen
{

////////////////////////////////////////////////////////////
Window::Window(void)
{
}

////////////////////////////////////////////////////////////
Window::~Window(void)
{
	glfwTerminate();
}

////////////////////////////////////////////////////////////
bool Window::create(uint32 width, uint32 height)
{
	// Attempt to initialize GLFW
	if(! glfwInit())
	{
		throw std::runtime_error("glfwInit failed");
		return false;
	}

	// Set GLFW window hints
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

#ifdef DEBUG
	glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	// Try to open the window itself
	if(! glfwOpenWindow(width, height, 8, 8, 8, 8, 0, 0, GLFW_WINDOW))
	{
		throw std::runtime_error("glfwOpenWindow failed");
	}
	
	// Initialize GLEW now that window is open
	glewExperimental = GL_TRUE;

	GLenum code = glewInit();
	if(code != GLEW_OK)
	{
		std::stringstream err;
		err << "glewInit failed: " << glewGetErrorString(code);

		throw std::runtime_error(err.str());
		return false;
	}
	
	if(!GLEW_VERSION_3_2)
	{
		throw std::runtime_error("OpenGL 3.2 API is not available");
		return false;
	}

	return true;
}

}