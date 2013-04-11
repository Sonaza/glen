#include <glen/opengl.hpp>
#include <glen/Window/Window.hpp>
#include <glen/Graphics/Camera.hpp>
#include <glen/System/ErrorStream.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace glen
{

namespace
{

	glen::VideoMode m_videoMode;

	///////////////////////////////////////////////////////////////
	bool _initGLEW()
	{
		// Initialize GLEW now that window is open
		glewExperimental = GL_TRUE;

		GLenum code = glewInit();
		if(code != GLEW_OK)
		{
			err << "glewInit failed: " << glewGetErrorString(code) << ErrorStream::error;
			return false;
		}

		if(!GLEW_VERSION_3_2)
		{
			err << "OpenGL 3.2 API is not available" << ErrorStream::error;
			return false;
		}

		return true;
	}

	///////////////////////////////////////////////////////////////
	void GLFWCALL _glfwResizeCallback(int width, int height)
	{
		std::cout << "Window resized: " << width << " x " << height << std::endl;

		m_videoMode = VideoMode(width, height);
		glViewport(0, 0, width, height);

		Camera::refreshProjection();
	}

	///////////////////////////////////////////////////////////////
	void _setDefaultGLStates()
	{
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

}

namespace Window
{

	////////////////////////////////////////////////////////////
	void deinit()
	{
		glfwTerminate();
	}

	////////////////////////////////////////////////////////////
	void clear(Color c)
	{
		glClearColor(c.r / 255.f, c.g / 255.f, c.b / 255.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	////////////////////////////////////////////////////////////
	void display()
	{
		glfwSwapBuffers();
	}

	////////////////////////////////////////////////////////////
	void setTitle(const std::string &title)
	{
		glfwSetWindowTitle(title.c_str());
	}

	////////////////////////////////////////////////////////////
	bool isOpen()
	{
		return glfwGetWindowParam(GLFW_OPENED) == 1;
	}


	////////////////////////////////////////////////////////////
	void setPosition(Vector2i& pos)
	{
		glfwSetWindowPos(pos.x, pos.y);
	}

	////////////////////////////////////////////////////////////
	void setPosition(const int32 x, const int32 y)
	{
		setPosition(Vector2i(x, y));
	}
	
	////////////////////////////////////////////////////////////
	Vector2u getDimensions()
	{
		return Vector2u(m_videoMode.width, m_videoMode.height);
	}
	
	////////////////////////////////////////////////////////////
	float getAspectRatio()
	{
		return m_videoMode.width / static_cast<float>(m_videoMode.height);
	}

	////////////////////////////////////////////////////////////
	bool create(VideoMode mode, const std::string &title, uint16 style)
	{
		// Attempt to initialize GLFW
		if(! glfwInit())
		{
			err << "glfwInit failed" << ErrorStream::error;
			return false;
		}

		m_videoMode = mode;

		// Choose window settings according to input parameters
		int32 windowMode = GLFW_WINDOW;
		switch(style)
		{
		case Style::Resize:
			glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_FALSE);
			break;
		case Style::Normal:
			glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
			break;
		case Style::Fullscreen:
			windowMode = GLFW_FULLSCREEN;
			break;
		}

		// Set the rest window hints
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);

		glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

		//glfwSwapInterval(1);

		#ifdef DEBUG
			glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		#endif

		// Try to open the window itself
		if(! glfwOpenWindow(mode.width, mode.height, 8, 8, 8, 8, 24, 0, windowMode))
		{
			err << "glfwOpenWindow failed" << ErrorStream::error;
		}

		// Set resize event callback
		glfwSetWindowSizeCallback(_glfwResizeCallback);

		setTitle(title);

		// Center window on screen
		VideoMode desktop = VideoMode::getDesktopMode();

		setPosition(
			static_cast<int32>(desktop.width / 2.f - mode.width / 2.f),
			static_cast<int32>(desktop.height / 2.f - mode.height / 2.f)
		);

		_initGLEW();

		_setDefaultGLStates();

		return true;
	}

}

}