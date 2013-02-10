#include <glen/System/SceneManager.hpp>
#include <glen/Graphics/Scene.hpp>

namespace glen
{

///////////////////////////////////////////////////////////
SceneManager::SceneManager(void)
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
void SceneManager::update()
{
	for(SceneList::iterator it = m_scenes.begin();
		it != m_scenes.end(); ++it)
	{
		(*it).second->update();
	}
}

}