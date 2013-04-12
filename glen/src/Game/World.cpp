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
void World::sendGlobal(const std::string &type, boost::any data)
{
	sendGlobal(Message(type, data));
}

////////////////////////////////////////////////////
void World::sendGlobal(const Message &msg)
{
	for(EntityList::iterator it = m_entities.begin();
		it != m_entities.end();)
	{
		(*it)->send(msg);
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
		(*it)->send("draw");
	}
}

