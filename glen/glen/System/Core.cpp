#include <glen/ogl.h>

#include <glen/System/Core.hpp>
#include <glen/Window/Window.hpp>

#include <glen/Window/MessageBox.hpp>
#include <glen/System/SceneManager.hpp>

#include <Scenes/TestScene.hpp>

#include <glen/Graphics/MeshLoader.hpp>
#include <glen/System/Vector3.hpp>

#include <glen/Graphics/MaterialFactory.hpp>

#include <iostream>
#include <cassert>
#include <stdexcept>

namespace glen
{

////////////////////////////////////////////////////////////
Core::Core(void)
{
}

////////////////////////////////////////////////////////////
Core::~Core(void)
{
	Window::deinit();
	MaterialFactory::deinit();

	if(m_sceneManager) { delete m_sceneManager; m_sceneManager = NULL; }
}

////////////////////////////////////////////////////////////
int Core::start()
{
	Window::create(VideoMode(1280, 720), "Derp", Style::Resize);

	init();

	loop();

	return 0;
}

////////////////////////////////////////////////////////////
void Core::init()
{
	m_sceneManager = new(std::nothrow) SceneManager(this);
	m_sceneManager->add("test", new(std::nothrow) TestScene, true);
}

////////////////////////////////////////////////////////////
void Core::loop()
{
	m_fpsTimer = m_lastTime = 0.f;

	m_running = true;
	while(m_running && Window::isOpen())
	{
		/*m_lastTime = m_fpsTimer;
		m_fpsTimer = GetTickCount() / 1000.f;

		if(m_outTimer < m_fpsTimer)
		{
			float fps = 1.f / (m_fpsTimer-m_lastTime);
			std::cout << fps << " FPS " << std::endl;
			m_outTimer = m_fpsTimer+1.f;
		}*/

		Window::clear(Color(240, 40, 150));
		//Window::clear(Color(95, 35, 17));

		if(glfwGetKey(GLFW_KEY_ESC))
			m_running = false;

		m_sceneManager->update();

		m_sceneManager->draw();

		Window::display();

		//sleep(milliseconds(5));
	}
}

}