#pragma once

namespace mds
{
	class Message
	{
	public:
		typedef void* Data;
		typedef int MessageId;
		
	public:
		Message(MessageId messageId, Data data);

		MessageId get_message_id() const;
		Data get_data() const;
	private:
		MessageId messageId_;
		Data data_;
	};
}