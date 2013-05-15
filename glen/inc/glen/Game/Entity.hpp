#ifndef GLEN_ENTITY_HPP
#define GLEN_ENTITY_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

#include <glen/Game/Message.hpp>

namespace glen
{
	typedef std::map<std::string, Component*> ComponentList;

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		// Attaches the component to the entity and returns
		// pointer to the attached instance
		Component* attachComponent(Component* component);

		// Detaches component by label
		void detachComponent(const std::string &label);

		bool hasComponent(const std::string &label);

		Component* getComponent(const std::string &label);

		template <class T>
		T* getComponent(const std::string &label);

		// Entity update
		virtual void update() {}

		void updateComponents();
		
		void call(const Message &msg);
		void call(const std::string &type);
		void call(const std::string &type, boost::any data);

		template <class T>
		T request(const std::string &type);

		boost::any request(const std::string &type);

		/*
		template <const char *>
		void send(boost::any data);*/

		void listen(const std::string &trigger, MessageFunction function, Component* owner = NULL);
		void listen(const std::string &trigger, RequestFunction function);

		// Changes whether entity is enabled, disabled entities
		// don't update or respond to calls
		void setEnabled(bool enabled);

		// Returns if the entity is enabled or disabled
		bool isEnabled() const;

		// Sets entity up for destroying
		void destroyEntity();

		// Returns whether the entity is due for removal
		bool isDestroyed() const;

		unsigned int	m_draworder;
		bool			m_drawable;

	protected:

		bool	m_isDestroyed;
		bool	m_isEnabled;

		ComponentList	m_components;
		Listeners		m_listeners;
		Responders		m_responders;

	};
	
	/////////////////////////////////////////////
	template <class T>
	T* Entity::getComponent(const std::string &label)
	{
		Component* temp = getComponent(label);
		assert(temp);

		T* result = NULL;
		if(temp != NULL) result = dynamic_cast<T*>(temp);

		return result;
	}

	/////////////////////////////////////////////
	template <class T>
	T Entity::request(const std::string &type)
	{
		//try
		//{
			return boost::any_cast<T>(request(type));
		//}
		/*catch(boost::bad_any_cast &e)
		{
			
		}*/
	}

	/*
	/////////////////////////////////////////////
	template <const char *type>
	void Entity::send(boost::any data)
	{
		send(type, data);
	}*/

}

#endif GLEN_ENTITY_HPP
