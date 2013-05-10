#include <glen/Game/World.hpp>

#include <glen/Game/Entity.hpp>
#include <glen/Game/Component.hpp>

#include <glen/opengl.hpp>

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

		entity->update();

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

namespace
{
	bool drawsort_compare(Entity* first, Entity* second)
	{
		return first->m_draworder < second->m_draworder;
	}
}

////////////////////////////////////////////////////
void World::render()
{
	std::vector<Entity*> ent = m_entities;
	std::sort(ent.begin(), ent.end(), drawsort_compare);

	for(EntityList::iterator it = ent.begin(); it != ent.end(); ++it)
	{
		Entity* e = *it;

		if(e == ent.back())
		{
			glDepthRange(1, 1);
			glDepthFunc(GL_LEQUAL);
		}

		e->call("draw");
	}

	glDepthRange(0, 1);
	glDepthFunc(GL_LESS);
}

