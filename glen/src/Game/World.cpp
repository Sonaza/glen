#include <glen/Game/World.hpp>

#include <glen/Game/Entity.hpp>
#include <glen/Game/Component.hpp>

using namespace glen;

namespace
{

	EntityList	m_entities;

}

////////////////////////////////////////////////////
void World::init()
{
	
}

////////////////////////////////////////////////////
void World::uninit()
{
	clear();
}

////////////////////////////////////////////////////
void World::callGlobal(const std::string &type, boost::any data)
{
	callGlobal(Message(type, data));
}

////////////////////////////////////////////////////
void World::callGlobal(const Message &msg)
{
	for(EntityList::iterator it = m_entities.begin();
		it != m_entities.end();)
	{
		(*it)->call(msg);
	}
}

////////////////////////////////////////////////////
void World::addEntity(Entity* entity)
{
	assert(entity != NULL && "Entity must not be null");

	m_entities.push_back(entity);
}

////////////////////////////////////////////////////
void World::clear()
{
	for(EntityList::iterator it = m_entities.begin(); it != m_entities.end();)
	{
		delete *it;
		it = m_entities.erase(it);
	}
}

////////////////////////////////////////////////////
void World::update()
{
	Entity* entity = NULL;
	for(EntityList::iterator it = m_entities.begin(); it != m_entities.end();)
	{
		entity = *it;

		if(!entity->isDestroyed())
		{
			entity->updateComponents();
			++it;
		}
		else
		{
			delete *it;
			it = m_entities.erase(it);
		}
	}
}

////////////////////////////////////////////////////
void World::render()
{
	for(EntityList::iterator it = m_entities.begin();
		it != m_entities.end(); ++it)
	{
		(*it)->call("draw");
	}
}

