#ifndef GLEN_WORLD_HPP
#define GLEN_WORLD_HPP

#include <vector>
#include <cassert>
#include <glen/Game/Message.hpp>

namespace glen
{
	
	class Entity;

	typedef std::vector<Entity*> EntityList;

	namespace World
	{

		void init();
		void uninit();

		void callGlobal(const std::string &type, boost::any data);
		void callGlobal(const Message &msg);

		void addEntity(Entity*);

		/*template <class T>
		T* addEntity(T* e)
		{
			addEntity(e);
			return e;
		}*/

		void clear();

		void update();
		void render();

	}
	
}

#endif GLEN_WORLD_HPP
