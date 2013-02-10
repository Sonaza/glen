#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <memory>
#include <map>
#include <string>

namespace glen
{

	class Scene;

	typedef std::string SceneID;
	typedef std::shared_ptr<Scene> ScenePtr;
	typedef std::map<SceneID, ScenePtr> SceneList;

	class SceneManager
	{
	public:
		SceneManager(void);
		~SceneManager(void);

		inline void add(const SceneID &id, Scene* scene) { m_scenes.insert(std::make_pair(id, ScenePtr(scene))); }

	private:

		SceneList		m_scenes;

	};

}

#endif
