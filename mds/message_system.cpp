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
	{
	}
	void MessageSystem::Loop()
	{
#pragma warning( disable : 4127 ) // warning C4127: conditional expression is constant
		while( true )
#pragma warning( default : 4127 )
		{
			if( !messageQueue_.empty() && messageQueue_.top().get_recieve_time() <= clock() )
			{
				Msg msg = messageQueue_.top();
				messageQueue_.pop();

				if( NULL == msg.get_reciever() )
				{
					if( SystemMessageTranslate(msg.get_message()) )
					{
						break;
					}
				}
				else
				{
					if( !PreTranslate(msg.get_message()) )
					{
						if( 1 == objects_.count(msg.get_reciever()) )
						{
							msg.get_reciever()->ProcessMessage(msg.get_message());
						}
						else
						{
							NonexistentObjectTranslate(msg.get_message());
						}
					}
				}
			}
			else
			{
				IdleProcessing();
			}
		}
	}
	void MessageSystem::PostSystemMessage(const Message &message, unsigned int delay)
	{
		PostMessage(NULL, message, delay);
	}
	MessageSystem::~MessageSystem()
	{
		ClearQueue();
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
	void MessageSystem::PostMessage(Object* reciever, const Message &message, unsigned delay)
	{
		Msg msg(reciever, message, clock()+delay*CLOCKS_PER_SEC/1000);
		messageQueue_.push(msg);
	}
	void MessageSystem::ClearQueue()
	{
		while( !messageQueue_.empty() )
		{
			DeletingMessage( messageQueue_.top().get_message() );
			messageQueue_.pop();
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