#include <glen/Game/World.hpp>

#include <glen/Game/Entity.hpp>
#include <glen/Game/Component.hpp>

using namespace glen;

namespace
{

	EntityList	_entities;

	float		_worldScale		= 30.f;

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
float World::getWorldScale()
{
	return _worldScale;
}

////////////////////////////////////////////////////
void World::sendGlobal(const std::string &type, boost::any data)
{
	sendGlobal(Message(type, data));
}

////////////////////////////////////////////////////
void World::sendGlobal(const Message &msg)
{
	for(EntityList::iterator it = _entities.begin();
		it != _entities.end();)
	{
		(*it)->send(msg);
	}
}

////////////////////////////////////////////////////
void World::addEntity(Entity* entity)
{
	assert(entity != NULL && "Entity must not be null");

	_entities.push_back(entity);
}

////////////////////////////////////////////////////
void World::clear()
{
	for(EntityList::iterator it = _entities.begin(); it != _entities.end();)
	{
		delete *it;
		it = _entities.erase(it);
	}
}

////////////////////////////////////////////////////
void World::update()
{
		Entity* entity = NULL;
	for(EntityList::iterator it = _entities.begin(); it != _entities.end();)
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
			it = _entities.erase(it);
		}
	}
}

////////////////////////////////////////////////////
void World::render()
{
	for(EntityList::iterator it = _entities.begin();
		it != _entities.end(); ++it)
	{
		(*it)->send("draw", NULL);
	}
}

