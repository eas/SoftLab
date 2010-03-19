#include "memory_leaks_detection.h"

#include "message.h"



namespace mds
{
	Message::Message(MessageId messageId, void* data)
		: messageId_(messageId),
		  data_(data)
	{
	}
	Message::MessageId Message::get_message_id() const
	{
		return messageId_;
	}
	Message::Data Message::get_data() const
	{
		return data_;
	}
}