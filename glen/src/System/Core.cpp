#include <glen/System/Core.hpp>
#include <glen/System/InputManager.hpp>

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
	Window::create(VideoMode(1280, 720), "Derp", Style::Default);
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
	while(m_running)
	{
		/*m_lastTime = m_fpsTimer;
		m_fpsTimer = GetTickCount() / 1000.f;

		if(m_outTimer < m_fpsTimer)
		{
			float fps = 1.f / (m_fpsTimer-m_lastTime);
			std::cout << fps << " FPS " << std::endl;
			m_outTimer = m_fpsTimer+1.f;
		}*/
		
		events();

		update();

		render();

		sleep(milliseconds(5));
	}
}

////////////////////////////////////////////////////////////
void Core::events()
{
	#ifdef SFML_SYSTEM_WINDOWS

	// Fix for windows taskbar lag in SFML
	MSG msg;
	while(PeekMessage(&msg, NULL, 0xc042, 0xc042, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	#endif

	sf::Window* win = Window::getWindow();
	sf::Event event;

	while(win->pollEvent(event))
	{
		// Update input manager
		Input::updateInputs(event);

		switch(event.type)
		{
		case sf::Event::Resized:
			std::cout << "Resized: " << event.size.width << ", " << event.size.height << std::endl;
			Camera::refreshProjection();
			glViewport(0, 0, event.size.width, event.size.height);
				//event.size.width / static_cast<float>(event.size.height)
			break;
		case sf::Event::Closed:
			m_running = false;
			break;
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Escape) m_running = false;
			break;
		}
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
	//Window::clear(Color(250, 100, 50));
	Window::clear(Color(90, 180, 250));

	// Render all world entities
	World::render();

	// Render scene
	SceneManager::render();

	Window::display();
}