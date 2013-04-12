#include <glen/System/SceneManager.hpp>
#include <glen/System/Scene.hpp>

#include <glen/System/AssetManager.hpp>

using namespace glen;

namespace
{
	ScenePtr	m_currentScene;
	ScenePtr	m_nextScene;
}

///////////////////////////////////////////////////////////
SceneManager::SceneManager()
{
}

///////////////////////////////////////////////////////////
void SceneManager::setScene(Scene* scene)
{
	assert(scene != NULL && "Scene cannot be null");

	m_nextScene.reset(scene);
}

///////////////////////////////////////////////////////////
void SceneManager::update()
{
	// If pending scene exists change to it
	if(m_nextScene)
	{
		_switchScene();
	}

	m_currentScene->updateClocks();
	m_currentScene->update();
}

///////////////////////////////////////////////////////////
void SceneManager::render()
{
	assert(m_currentScene && "Scene must be set");

	m_currentScene->render();
}

///////////////////////////////////////////////////////////
void SceneManager::_switchScene()
{
	// If scene already exists then handle unloading
	if(m_currentScene)
	{
		// Unload previous scene
		m_currentScene->unload();

		// Unload assets that were bound
		// to the old scene
		AssetManager::freeSceneAssets();

		// Release pointer
		m_currentScene.release();
	}

	// Move pointers
	m_currentScene = std::move(m_nextScene);

	// Initialize scene
	m_currentScene->load();
}
