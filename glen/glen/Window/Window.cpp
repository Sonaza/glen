#include <glen/Window/Window.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{

	glen::VideoMode* p_videoMode = NULL;

	///////////////////////////////////////////////////////////////
	bool _initGLEW()
	{
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

	///////////////////////////////////////////////////////////////
	void GLFWCALL _glfwResizeCallback(int width, int height)
	{
		std::cout << "Window resized: " << width << " x " << height << std::endl;
		//*p_videoMode = glen::VideoMode(width, height);

		glViewport(0, 0, width, height);
	}

}

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
bool Window::create(VideoMode mode, const std::string &title, uint16 style)
{
	// Attempt to initialize GLFW
	if(! glfwInit())
	{
		throw std::runtime_error("glfwInit failed");
		return false;
	}

	m_videoMode = mode;
	p_videoMode = &m_videoMode;

	// Choose window settings according to input parameters
	int32 windowMode = GLFW_WINDOW;
	switch(style)
	{
	case style::Resize:
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_FALSE);
		break;
	case style::Normal:
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
		break;
	case style::Fullscreen:
		windowMode = GLFW_FULLSCREEN;
		break;
	}

	// Set the rest window hints
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);

	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

#ifdef DEBUG
	glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	// Set resize event callback
	glfwSetWindowSizeCallback(_glfwResizeCallback);

	// Try to open the window itself
	if(! glfwOpenWindow(mode.width, mode.height, 8, 8, 8, 8, 24, 0, windowMode))
	{
		throw std::runtime_error("glfwOpenWindow failed");
	}

	setTitle(title);

	// Center window on screen
	VideoMode desktop = VideoMode::getDesktopMode();

	glfwSetWindowPos(
		static_cast<int32>(desktop.width / 2.f - mode.width / 2.f),
		static_cast<int32>(desktop.height / 2.f - mode.height / 2.f)
	);

	_initGLEW();

	_setDefaultGLStates();

	return true;
}

////////////////////////////////////////////////////////////
void Window::clear(Color c)
{
	glClearColor(c.r / 255.f, c.g / 255.f, c.b / 255.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

////////////////////////////////////////////////////////////
void Window::display()
{
	glfwSwapBuffers();
}

////////////////////////////////////////////////////////////
void Window::setTitle(const std::string &title)
{
	glfwSetWindowTitle(title.c_str());
}

////////////////////////////////////////////////////////////
void Window::_setDefaultGLStates()
{
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

}