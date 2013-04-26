#include <glen/Game/Component.hpp>
#include <glen/Game/Entity.hpp>

namespace glen
{

////////////////////////////////////////////////////
Component::Component(const std::string &label) :
	m_entity(NULL),
	m_label(label)
{
	
}

////////////////////////////////////////////////////
Component::~Component()
{
	
}

////////////////////////////////////////////////////
void Component::call(const Message &msg)
{
	call(msg.type, msg.data);
}

///////////////////////////////////////////1/////////
void Component::call(const std::string &type, boost::any data)
{
	m_entity->call(Message(type, data, this));
}

////////////////////////////////////////////////////
void Component::registerMessage(const std::string &trigger, MessageFunction function)
{
	m_entity->listen(trigger, function, this);
}

////////////////////////////////////////////////////
void Component::registerRequest(const std::string &trigger, RequestFunction function)
{
	m_entity->listen(trigger, function);
}

}