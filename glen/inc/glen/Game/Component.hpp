#ifndef GLEN_COMPONENT_HPP
#define GLEN_COMPONENT_HPP

#include <cassert>
#include <string>

#include <glen/Game/Message.hpp>
#include <glen/Game/Entity.hpp>

namespace glen
{
	
	//class Entity;

	class Component
	{
		friend class Entity;

	public:
		Component(const std::string &label);
		virtual ~Component();

		virtual void attached() =0;
		virtual void update() {}
		
		void send(const Message &msg);
		void send(const std::string &type, boost::any data);

		template <class T>
		T request(const std::string &type);

		template <class T>
		void listen(const std::string &trigger, void (T::*f)(const Message &));

		template <class T>
		void listen(const std::string &trigger, boost::any (T::*f)(void));

	protected:

		// Component's parent entity
		Entity*			m_entity;
		
		std::string		m_label;

		void registerMessage(const std::string &trigger, MessageFunction function);
		void registerRequest(const std::string &trigger, RequestFunction function);
		
	};

	////////////////////////////////////////////////////
	template <class T>
	T Component::request(const std::string &type)
	{
		return m_entity->request<T>(type);
	}

	////////////////////////////////////////////////////
	template <class T>
	void Component::listen(const std::string &trigger, void (T::*f)(const Message &))
	{
		registerMessage(trigger, std::bind(f, (T*)(this), std::placeholders::_1));
	}

	////////////////////////////////////////////////////
	template <class T>
	void Component::listen(const std::string &trigger, boost::any (T::*f)(void))
	{
		registerRequest(trigger, std::bind(f, (T*)(this)));
	}
	
}

#endif GLEN_COMPONENT_HPP
