#include <glen/Graphics/Scene.hpp>

namespace glen
{

//////////////////////////////////////////////////////////
Scene::Scene(void) :
	m_active(false),
	m_loaded(false)
{
}

//////////////////////////////////////////////////////////
Scene::~Scene(void)
{
	if(m_loaded)
	{
		//unload();
		m_loaded = false;
	}
}

}