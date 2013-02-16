#include <glen/System/SceneManager.hpp>
#include <glen/Graphics/Scene.hpp>

#include <cassert>

namespace glen
{

///////////////////////////////////////////////////////////
SceneManager::SceneManager(Core* c) :
	p_core(c)
{
}

///////////////////////////////////////////////////////////
SceneManager::~SceneManager(void)
{
	if(!m_scenes.empty())
	{
		/*for(SceneList::iterator it = m_scenes.begin();
			it != m_scenes.end(); ++it)
		{
			delete *it;
		}*/

		m_scenes.clear();
	}
}

///////////////////////////////////////////////////////////
void SceneManager::add(const SceneID &id, Scene* scene, bool active)
{
	assert(scene != NULL && "Scene cannot be null");

	// Initialize scene
	scene->init(p_core);

	if(active)
	{
		scene->activate();

		scene->load();
	}

	// Add the scene to the list
	m_scenes.insert(std::make_pair(id, ScenePtr(scene)));
}

///////////////////////////////////////////////////////////
void SceneManager::update()
{
	for(SceneList::iterator it = m_scenes.begin();
		it != m_scenes.end(); ++it)
	{
		(*it).second->update();
	}
}

///////////////////////////////////////////////////////////
void SceneManager::draw()
{
	for(SceneList::iterator it = m_scenes.begin();
		it != m_scenes.end(); ++it)
	{
		(*it).second->draw();
	}
}

}