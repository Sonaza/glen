#include <glen/System/Core.hpp>
#include <glen/System/Startup.hpp>

#include <glen/System/SceneManager.hpp>

namespace glen
{

	std::unique_ptr<Core> g_core;

	void run(Scene* scene)
	{
		g_core.reset(new(std::nothrow) glen::Core);

		assert(g_core != NULL && "Core memory allocation failed");

		// Hello world
		g_core->initialize();

		// Set scene
		SceneManager::setScene(scene);

		g_core->run();
	}

}