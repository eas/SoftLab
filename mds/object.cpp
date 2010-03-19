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
		messageSystem_.PostMessage(this, message, delay);
	}
	void Object::PostSystemMessage(const Message &message, unsigned int delay)
	{
		messageSystem_.PostSystemMessage(message, delay);
	}
}