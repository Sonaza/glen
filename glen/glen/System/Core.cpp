#include <glen/ogl.h>

#include <glen/System/Core.hpp>
#include <glen/Window/Window.hpp>

#include <iostream>
#include <cassert>
#include <stdexcept>

#include <glen/Window/MessageBox.hpp>
#include <glen/System/SceneManager.hpp>

#include <Scenes/TestScene.hpp>

#include <glen/Graphics/MeshLoader.hpp>
#include <glen/System/Vector3.hpp>

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

	if(m_sceneManager) { delete m_sceneManager; m_sceneManager = NULL; }
}

////////////////////////////////////////////////////////////
int Core::start()
{
	try
	{
		Window::create(VideoMode(1280, 720), "Derp", Style::Resize);
	}
	catch(std::exception &e) { msgError("Exception", e.what()); }

	init();

	loop();

	return 0;
}

////////////////////////////////////////////////////////////
void Core::init()
{
	m_sceneManager = new(std::nothrow) SceneManager(this);

	m_sceneManager->add("test", new(std::nothrow) TestScene, true);

	MeshData mesh;
	MeshLoader::loadMesh("cube.obj", &mesh);

	Vector3f asd = Vector3f::up;
	std::cout << asd.x << ", " << asd.y << ", " << asd.z << std::endl;
}

////////////////////////////////////////////////////////////
void Core::loop()
{
	m_running = true;
	while(m_running && Window::isOpen())
	{
		Window::clear(Color::LimeGreen);

		m_sceneManager->update();

		m_sceneManager->draw();

		Window::display();

		sleep(milliseconds(5));
	}
}

}