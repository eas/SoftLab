#pragma once
namespace mds
{
	class Message;
	class MessageSystem;

	class Object
	{
		friend class MessageSystem;
	public:
		Object(MessageSystem& messageSystem);
		virtual ~Object();

		void Send(const Message& message);
		void Post(const Message& message, unsigned delay); // message will be delivered not earlier than in [delay] milliseconds

		void SendSystemMessage(const Message& message);
		void PostSystemMessage(const Message& message, unsigned delay);
	protected:
		// you can use returned value for something like if( !Super::ProcessMessage() ) { do smth }
		virtual bool ProcessMessage(const Message& message) = 0;
	private:
		Object(const Object&);
		Object& operator=(const Object&);
	private:
		MessageSystem& messageSystem_;
	};
}