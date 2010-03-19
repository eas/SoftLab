#pragma once

namespace mds
{
	class Message
	{
		typedef int MessageId;
		typedef void* Data;
	public:
		Message(MessageId messageId, Data data);

		MessageId get_message_id() const;
		Data get_data() const;
	private:
		MessageId messageId_;
		Data data_;
	};
}