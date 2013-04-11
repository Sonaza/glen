#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <memory>
#include <map>
#include <string>

namespace glen
{

	class Core;
	class Scene;

	typedef std::unique_ptr<Scene> ScenePtr;

	class SceneManager
	{
	public:
		SceneManager(Core* c);
		~SceneManager(void);

		void setScene(Scene* scene);

		void update();

		// Draw scenes
		void draw();

	private:

		Core*			p_core;

		ScenePtr		m_currentScene;

	};

}

#endif
