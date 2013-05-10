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

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_CUBE_MAP);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

}

////////////////////////////////////////////////////////////
bool Window::create(VideoMode mode, const std::string &title, uint32 style)
{
	// Set OpenGL context related settings
	m_settings.majorVersion = 3;
	m_settings.minorVersion = 2;

	m_settings.depthBits = 24;
	m_settings.stencilBits = 8;

	m_settings.antialiasingLevel = 4;

	// Create the window
	m_window.reset(new sf::Window(
		sf::VideoMode(mode.width, mode.height),
		title,
		style,
		m_settings
	));
	
	// Check if window initialization failed
	if(!m_window)
	{
		return false;
	}

	// Initialize GLEW now that window is open
	glewExperimental = GL_TRUE;

	GLenum code = glewInit();
	if(code != GLEW_OK)
	{
		err << "glewInit failed: " << glewGetErrorString(code) << ErrorStream::error;
		
		return false;
	}

	// See if correct context version was successfully loaded
	if(!GLEW_VERSION_3_2)
	{
		err << "OpenGL 3.2 API is not available" << ErrorStream::error;

		return false;
	}

	err << "GLEW_ARB_separate_shader_objects: " << (GLEW_ARB_separate_shader_objects ? "yes" : "no") << ErrorStream::console;

	_setDefaultGLStates();

	return true;
}

////////////////////////////////////////////////////////////
void Window::uninit()
{
	m_window->close();
}

////////////////////////////////////////////////////////////
void Window::clear(Color c)
{
	glClearColor(c.r / 255.f, c.g / 255.f, c.b / 255.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

////////////////////////////////////////////////////////////
void Window::display()
{
	m_window->display();
}

////////////////////////////////////////////////////////////
void Window::setTitle(const std::string &title)
{
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
void Window::setPosition(vec2i& pos)
{
	m_window->setPosition(sf::Vector2i(pos.x, pos.y));
}

////////////////////////////////////////////////////////////
void Window::setPosition(const int32 x, const int32 y)
{
	setPosition(vec2i(x, y));
}
	
////////////////////////////////////////////////////////////
vec2u Window::getDimensions()
{
	return vec2u(m_window->getSize().x, m_window->getSize().y);
}
	
////////////////////////////////////////////////////////////
float Window::getAspectRatio()
{
	return m_window->getSize().x / static_cast<float>(m_window->getSize().y);
}

////////////////////////////////////////////////////////////
sf::Window* Window::getWindow()
{
	return m_window.get();
}

////////////////////////////////////////////////////////////
vec2i Window::getOptimalResolution(const bool fullscreen)
{
	sf::VideoMode native = sf::VideoMode::getDesktopMode();
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	
	vec2i resolution(native.width, native.height);

	if(fullscreen && native == modes[0]) return resolution;

	float nativeRatio = native.width / static_cast<float>(native.height);
	float ratio;

	for(std::vector<sf::VideoMode>::iterator it = modes.begin(); it != modes.end(); ++it)
	{
		sf::VideoMode mode = *it;

		if(mode.bitsPerPixel != native.bitsPerPixel) continue;
		if(mode.width >= native.width) continue;

		ratio = mode.width / static_cast<float>(mode.height);

		if(fabs(nativeRatio-ratio) <= 0.05f)
		{
			resolution.x = mode.width;
			resolution.y = mode.height;

			break;
		}
	}

	return resolution;
}
