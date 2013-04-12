#include <glen/System/Core.hpp>

using namespace glen;

////////////////////////////////////////////////////////////
Core::Core(void)
{
}

////////////////////////////////////////////////////////////
Core::~Core(void)
{
	
}

////////////////////////////////////////////////////////////
void Core::run()
{
	loop();
}

////////////////////////////////////////////////////////////
void Core::initialize()
{
	Window::create(VideoMode(1280, 720), "Derp", Style::Resize);
}

////////////////////////////////////////////////////////////
void Core::uninitialize()
{
	Window::uninit();

	AssetManager::unload();
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

		//Window::clear(Color(240, 40, 150));
		Window::clear(Color(40, 150, 240));

		if(glfwGetKey(GLFW_KEY_ESC))
			m_running = false;

		update();

		render();

		Window::display();

		sleep(milliseconds(5));
	}
}

////////////////////////////////////////////////////////////
void Core::update()
{
	// Update scene
	SceneManager::update();

	// Update world
	World::update();
}

////////////////////////////////////////////////////////////
void Core::render()
{
	// Render all world entities
	World::render();

	// Render scene
	SceneManager::render();
}