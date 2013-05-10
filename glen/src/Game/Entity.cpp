#include <glen/Game/Entity.hpp>
#include <glen/Game/Component.hpp>
#include <iostream>

#include <glen/System/ErrorStream.hpp>

#include <glen/Game/Component.hpp>
#include <glen/Game/Components/Transform.hpp>

using namespace glen;

////////////////////////////////////////////////////
Entity::Entity() :
	m_destroyed(false), m_draworder(0)
{
	
}

////////////////////////////////////////////////////
Entity::~Entity()
{
	for(ComponentList::iterator it = m_components.begin();
		it != m_components.end(); ++it)
	{
		delete it->second;
	}

	m_components.clear();
}

////////////////////////////////////////////////////
Component* Entity::attachComponent(Component* component)
{
	if(!hasComponent(component->m_label))
	{
		m_components.insert(std::make_pair(component->m_label, component));
		component->m_entity = this;

		component->attached();
	}

	return component;
}

////////////////////////////////////////////////////
void Entity::detachComponent(const std::string &label)
{
	ComponentList::iterator it = m_components.find(label);

	if(it != m_components.end())
	{
		// Free component from memory
		delete it->second;

		m_components.erase(it);
	}
}

////////////////////////////////////////////////////
bool Entity::hasComponent(const std::string &label)
{
	return m_components.find(label) != m_components.end();
}

////////////////////////////////////////////////////
Component* Entity::getComponent(const std::string &label)
{
	Component* result = NULL;

	ComponentList::iterator it = m_components.find(label);
	if(it != m_components.end())
	{
		result = it->second;
	}

	return result;
}

////////////////////////////////////////////////////
void Entity::updateComponents()
{
	for(ComponentList::iterator it = m_components.begin();
		it != m_components.end(); ++it)
	{
		//std::cout << it->second->m_label << std::endl;
		it->second->update();
	}
}

////////////////////////////////////////////////////
void Entity::updateComponent(const std::string &label)
{
	Component* temp = getComponent(label);
	assert(temp != NULL && "No component found using the label");

	if(temp != NULL)
	{
		temp->update();
	}
}

////////////////////////////////////////////////////
void Entity::call(const Message &msg)
{
	std::string temp = msg.type;

	// Transform string to lower
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

	// Attempt to find the trigger
	Listeners::iterator it = m_listeners.find(temp);
	if(it != m_listeners.end())
	{
		// Broadcast the message to all listeners
		for(MessageCallbacks::iterator cit = it->second.begin();
			cit != it->second.end(); ++cit)
		{
			try
			{
				// Don't send the message to the sender
				if(!msg.sender || msg.sender != (*cit).owner)
				{
					(*cit).function(msg);
				}
			}
			catch(std::bad_function_call &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
}

////////////////////////////////////////////////////
void Entity::call(const std::string &type)
{
	call(Message(type));
}

////////////////////////////////////////////////////
void Entity::call(const std::string &type, boost::any data)
{
	call(Message(type, data));
}

////////////////////////////////////////////////////
boost::any Entity::request(const std::string &type)
{
	std::string temp = type;

	// Transform string to lower
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

	// See if a trigger already exists
	Responders::iterator it = m_responders.find(temp);
	if(it != m_responders.end())
	{
		try
		{
			return it->second();
		}
		catch(std::bad_function_call &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	err << "No responder '" << type << "' registered" << ErrorStream::error;
	assert(false && "Something is wrong, we shouldn't ever reach this place");

	return NULL;
}

////////////////////////////////////////////////////
void Entity::listen(const std::string &trigger, MessageFunction function, Component* owner)
{
	std::string temp = trigger;

	// Transform string to lower
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

	// See if a trigger already exists
	Listeners::iterator it = m_listeners.find(temp);
	if(it == m_listeners.end())
	{
		m_listeners.insert(std::make_pair(temp, MessageCallbacks()));
		m_listeners[temp].push_back(MessageCallback(function, owner));
	}
	else
	{
		it->second.push_back(MessageCallback(function, owner));
	}
}

////////////////////////////////////////////////////
void Entity::listen(const std::string &trigger, RequestFunction function)
{
	std::string temp = trigger;

	// Transform string to lower
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

	// See if a trigger already exists
	Responders::iterator it = m_responders.find(temp);
	if(it == m_responders.end())
	{
		m_responders.insert(std::make_pair(temp, function));
	}
	else
	{
		err << "Responder '" << trigger << "' already exists" << ErrorStream::error;
		assert(false && "Responder already exists");
	}
}