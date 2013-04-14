#include <glen/opengl.hpp>

#include <glen/Window/Window.hpp>
#include <glen/Graphics/Camera.hpp>
#include <glen/System/ErrorStream.hpp>

#include <memory>

using namespace glen;

namespace
{

	std::unique_ptr<sf::Window>		m_window;
	sf::ContextSettings				m_settings;

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
	/*void GLFWCALL _glfwResizeCallback(int width, int height)
	{
		std::cout << "Window resized: " << width << " x " << height << std::endl;

		m_videoMode = VideoMode(width, height);
		glViewport(0, 0, width, height);

		Camera::refreshProjection();
	}*/

	///////////////////////////////////////////////////////////////
	void _setDefaultGLStates()
	{
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		//glEnable(GL_ALPHA_TEST);
		//glAlphaFunc(GL_GREATER, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

}

////////////////////////////////////////////////////////////
void Window::uninit()
{
	//glfwTerminate();
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
	m_window->display();
}

////////////////////////////////////////////////////////////
void Window::setTitle(const std::string &title)
{
	//glfwSetWindowTitle(title.c_str());
	m_window->setTitle(title);
}

////////////////////////////////////////////////////////////
bool Window::isOpen()
{
	return m_window->isOpen();
}

////////////////////////////////////////////////////////////
bool Window::isActive()
{
	// Windows implementation
	return m_window->getSystemHandle() == GetActiveWindow();
}

////////////////////////////////////////////////////////////
void Window::setPosition(Vector2i& pos)
{
	m_window->setPosition(sf::Vector2i(pos.x, pos.y));
}

////////////////////////////////////////////////////////////
void Window::setPosition(const int32 x, const int32 y)
{
	setPosition(Vector2i(x, y));
}
	
////////////////////////////////////////////////////////////
Vector2u Window::getDimensions()
{
	return Vector2u(m_window->getSize().x, m_window->getSize().y);
}
	
////////////////////////////////////////////////////////////
float Window::getAspectRatio()
{
	return m_window->getSize().x / static_cast<float>(m_window->getSize().y);
}

////////////////////////////////////////////////////////////
bool Window::create(VideoMode mode, const std::string &title, uint32 style)
{
	m_settings.antialiasingLevel = 4;
	m_settings.depthBits = 24;
	m_settings.majorVersion = 3;
	m_settings.minorVersion = 2;
	
	m_window.reset(new sf::Window(
		sf::VideoMode(mode.width, mode.height),
		title,
		style,
		m_settings
	));

	_initGLEW();

	_setDefaultGLStates();

	return true;
}

////////////////////////////////////////////////////////////
sf::Window* Window::getWindow()
{
	return m_window.get();
}
