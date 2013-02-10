#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

namespace glen
{

	class Component;

	class Entity
	{
	public:
		Entity(void);
		~Entity(void);

		template <class TYPE>
		TYPE* getComponent() const;

	private:

		std::vector<Component*>		m_components;

	};

}

#endif