#include "memory_leaks_detection.h"


#include "object.h"
#include "message_system.h"



namespace mds
{
	Object::Object(MessageSystem &messageSystem)
		: messageSystem_(messageSystem)
	{
		messageSystem_.RegisterObject(this);
	}
	Object::~Object()
	{
		messageSystem_.UnregisterObject(this);
	}
	void Object::Post(const Message &message, unsigned int delay)
	{
		messageSystem_.PostMessageTo(this, message, delay);
	}
	void Object::Send(const Message &message)
	{
		messageSystem_.SendMessageTo(this, message);
	}

	void Object::PostSystemMessage(const Message &message, unsigned int delay)
	{
		messageSystem_.PostMessage(message, delay);
	}
	void Object::SendSystemMessage(const Message& message)
	{
		messageSystem_.SendMessage(message);
	}
}