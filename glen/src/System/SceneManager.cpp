#include <glen/System/SceneManager.hpp>
#include <glen/System/Scene.hpp>

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
	
}

///////////////////////////////////////////////////////////
void SceneManager::setScene(Scene* scene)
{
	assert(scene != NULL && "Scene cannot be null");

	m_currentScene.reset(scene);

	// Initialize scene
	scene->init(p_core);
	scene->activate();
	scene->load();
}

///////////////////////////////////////////////////////////
void SceneManager::update()
{
	if(m_currentScene)
	{
		m_currentScene->update();
	}
}

///////////////////////////////////////////////////////////
void SceneManager::draw()
{
	m_currentScene->draw();
}

}