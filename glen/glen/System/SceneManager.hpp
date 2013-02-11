#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <memory>
#include <map>
#include <string>

namespace glen
{

	class Core;
	class Scene;

	typedef std::string SceneID;
	typedef std::shared_ptr<Scene> ScenePtr;
	typedef std::map<SceneID, ScenePtr> SceneList;

	class SceneManager
	{
	public:
		SceneManager(Core* c);
		~SceneManager(void);

		void add(const SceneID &id, Scene* scene, bool active = false);

		void update();

		// Draw scenes
		void draw();

	private:

		Core*			p_core;

		SceneList		m_scenes;

	};

}

#endif
