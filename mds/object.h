#pragma once
namespace mds
{
	class Message;
	class MessageSystem;

	class Object
	{
	public:
		Object(MessageSystem& messageSystem);
		virtual ~Object();
		virtual void ProcessMessage(const Message& message) = 0;
		void Post(const Message& message, unsigned delay); // message will be delivered not earlier than in [delay] milliseconds
		void PostSystemMessage(const Message& message, unsigned delay);
	private:
		Object(const Object&);
		Object& operator=(const Object&);
	private:
		MessageSystem& messageSystem_;
	};
}