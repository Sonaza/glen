#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <cassert>
#include <memory>

namespace glen
{

	class Scene;

	typedef std::unique_ptr<Scene> ScenePtr;

	class SceneManager
	{
	public:
		SceneManager();

		static void setScene(Scene* scene);

		static void update();

		static void render();

	private:

		static void _switchScene();

	};

}

#endif
