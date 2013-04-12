#include <glen/System/Scene.hpp>

using namespace glen;

//////////////////////////////////////////////////////////
Scene::Scene()
{
	m_deltaTimeClock.restart();
	m_totalTimeClock.restart();
}

//////////////////////////////////////////////////////////
Scene::~Scene(void)
{
	//unload();
}

////////////////////////////////////////////////////
void Scene::updateClocks()
{
	Time.delta = m_deltaTimeClock.getElapsedTime().asSeconds();
	Time.total = m_totalTimeClock.getElapsedTime().asSeconds();

	m_deltaTimeClock.restart();
}