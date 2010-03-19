#pragma once
#include <queue>
#include <set>
#include <functional>
#include <time.h>

#include "message.h"

namespace mds
{
	class Object;
	class Msg
	{
	public:
		struct less;
		typedef time_t Time;
	public:
		Msg(Object* reciever, const Message& message, Time recieveTime);
		Object* get_reciever() const;
		Message get_message() const;
		Time get_recieve_time() const;
	private:
		Object* reciever_;
		Message message_;
		Time recieveTime_;
	};

	struct Msg::less
		: public std::binary_function<Msg, Msg, bool>
	{
		bool operator()(const Msg& lhs, const Msg& rhs) const
		{	
			return lhs.get_recieve_time() < rhs.get_recieve_time();
		}
	};

	class MessageSystem
	{
		friend class Object;

		typedef std::priority_queue<Msg, std::vector<Msg>, Msg::less> MessageQueue;
		typedef std::set<Object*> Objects;
	public:
		MessageSystem();
		void Loop();
		virtual ~MessageSystem();

		//message will not send to object if returned value is true
		virtual bool PreTranslate(const Message& message);

		//end loop if returned value is true
		virtual bool SystemMessageTranslate(const Message& message) = 0; // = 0 because we need to stop loop, how must we do it?

		//called if reciever has died, override if you need some special activity in this situation
		virtual void NonexistentObjectTranslate(const Message& message); // require overriding, if message contains dynamically allocated memory

		//called during clearing message queue
		virtual void DeletingMessage(const Message& message); // override, if message contains dynamically allocated memory

		//called if there is no message which must be delivered
		virtual void IdleProcessing() = 0;
	private:
		void RegisterObject(Object* object);
		void UnregisterObject(Object* object);
		void PostMessage(Object* reciever, const Message& message, unsigned delay);
		void ClearQueue();
	private:
		MessageSystem(const MessageSystem&);
		MessageSystem& operator=(const MessageSystem&);

	private:
		MessageQueue messageQueue_;
		Objects objects_;
	};
}