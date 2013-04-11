#ifndef GLEN_MESSAGE_HPP
#define GLEN_MESSAGE_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

#include <boost/any.hpp>

namespace glen
{

	class Component;

	struct Message
	{
		Message(const std::string &t) : type(t), sender(NULL) {}
		Message(const std::string &t, boost::any d) : type(t), data(d), sender(NULL) {}
		Message(const std::string &t, boost::any d, Component* s) : type(t), data(d), sender(s) {}

		std::string		type;
		boost::any		data;
		Component*		sender;
	};

	typedef std::function<void(const Message &)> MessageFunction;

	struct MessageCallback
	{
		MessageCallback(MessageFunction f) : function(f), owner(NULL) {}
		MessageCallback(MessageFunction f, Component* o) : function(f), owner(o) {}

		MessageFunction function;
		Component*		owner;
	};

	typedef std::vector<MessageCallback> MessageCallbacks;
	typedef std::map<const std::string, MessageCallbacks> Listeners;

	typedef std::function<boost::any(void)> RequestFunction;
	
	typedef std::map<const std::string, RequestFunction> Responders;

}

#endif