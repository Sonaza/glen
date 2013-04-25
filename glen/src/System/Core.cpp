#include <glen/System/Core.hpp>


#include <glen/Window/Window.hpp>

#include <glen/Game/World.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/InputManager.hpp>
#include <glen/System/SceneManager.hpp>

#include <glen/Graphics/ShaderManager.hpp>

#include <glen/Graphics/Camera.hpp>

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
bool Core::initialize()
{
	vec2i reso = Window::getOptimalResolution();
	std::cout << reso.x << " x " << reso.y << std::endl;
	return Window::create(VideoMode(reso.x, reso.y), "Derp", Style::Default);
}

////////////////////////////////////////////////////////////
void Core::uninitialize()
{
	AssetManager::unload();
	ShaderManager::unload();

	Window::uninit();
}

////////////////////////////////////////////////////////////
void Core::loop()
{
	sf::Clock deltaclock, fpsupdateclock;

	m_running = true;
	while(m_running)
	{
		/*float delta = deltaclock.restart().asSeconds();
		if(fpsupdateclock.getElapsedTime().asSeconds() >= 1.f)
		{
			std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2)
					  <<  (1.f / delta) << " fps" << std::endl;

			fpsupdateclock.restart();
		}*/

		events();

		update();

		render();

		sf::sleep(sf::milliseconds(5));
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