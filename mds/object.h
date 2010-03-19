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
		virtual void ProcessMessage(const Message& message);
		void Post(const Message& message, unsigned delay); // message will be delivered not earlier than in [delay] milliseconds
	private:
		Object(const Object&);
		Object& operator=(const Object&);
	private:
		MessageSystem& messageSystem_;
	};
}