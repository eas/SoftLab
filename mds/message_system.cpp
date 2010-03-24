#include "memory_leaks_detection.h"


#include <assert.h>
#include <time.h>
#include "message.h"
#include "object.h"
#include "message_system.h"



namespace mds
{
	Msg::Msg(Object *reciever, const Message& message, Msg::Time recieveTime)
		: reciever_(reciever),
		  message_(message),
		  recieveTime_(recieveTime)
	{
	}
	Msg::Time Msg::get_recieve_time() const
	{
		return recieveTime_;
	}
	Message Msg::get_message() const
	{
		return message_;
	}
	Object* Msg::get_reciever() const
	{
		return reciever_;
	}


	MessageSystem::MessageSystem()
		: isLoopFinished_(true)
	{
	}
	void MessageSystem::Loop()
	{
		try
		{
			isLoopFinished_ = false;
			while( !isLoopFinished_ )
			{
				if( !messageQueue_.empty() && messageQueue_.top().get_recieve_time() <= clock() )
				{
					Msg msg = messageQueue_.top();
					messageQueue_.pop();
					MessageProcessing(msg.get_reciever(), msg.get_message());
				}
				else
				{
					IdleProcessing();
				}
			}
		}
		catch(...)
		{
			ClearQueue();
			throw;
		}
		ClearQueue();
	}
	void MessageSystem::PostMessage(const Message &message, unsigned int delay)
	{
		PostMessageTo(NULL, message, delay);
	}
	void MessageSystem::SendMessage(const Message& message)
	{
		SendMessageTo(NULL, message);
	}
	MessageSystem::~MessageSystem()
	{
		assert( messageQueue_.empty() );
	}

	void MessageSystem::RegisterObject(Object* object)
	{
		assert( 0 == objects_.count(object) );
		if( false == objects_.insert(object).second )
		{
			throw std::exception("can't register object");
		}
	}
	void MessageSystem::UnregisterObject(Object* object)
	{
		assert( 1 == objects_.count(object) );
		objects_.erase(object);
	}
	void MessageSystem::PostMessageTo(Object* reciever, const Message& message, unsigned delay)
	{
		Msg msg(reciever, message, clock()+delay*CLOCKS_PER_SEC/1000);
		messageQueue_.push(msg);
	}
	void MessageSystem::SendMessageTo(Object* reciever, const Message& message)
	{
		MessageProcessing(reciever, message);
	}
	void MessageSystem::ClearQueue()
	{
		while( !messageQueue_.empty() )
		{
			DeletingMessage( messageQueue_.top().get_message() );
			messageQueue_.pop();
		}
	}
	void MessageSystem::MessageProcessing(Object* reciever, const Message& message)
	{
		if( NULL == reciever )
		{
			if( SystemMessageProcess(message) )
			{
				isLoopFinished_ = true;
			}
		}
		else
		{
			if( !PreTranslate(message) )
			{
				if( 1 == objects_.count(reciever) )
				{
					reciever->ProcessMessage(message);
				}
				else
				{
					NonexistentObjectTranslate(message);
				}
			}
		}
	}

	//if user doesn't want to define these methods
	bool MessageSystem::PreTranslate(const Message&)
	{
		return false;
	}
	void MessageSystem::DeletingMessage(const Message&)
	{
	}
	void MessageSystem::IdleProcessing()
	{
	}
	void MessageSystem::NonexistentObjectTranslate(const Message&)
	{
	}
}