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
void Component::send(const Message &msg)
{
	send(msg.type, msg.data);
}

////////////////////////////////////////////////////
void Component::send(const std::string &type, boost::any data)
{
	m_entity->send(Message(type, data, this));
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