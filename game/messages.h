#pragma once
#include "mds/message.h"

namespace game
{
	const mds::Message::MessageId M_MOVE = 1;
	const mds::Message::MessageId M_OBJECT_MOVED = 2;
	const mds::Message::MessageId M_EXIT = 3;
	const mds::Message::MessageId M_CHANGE_DIRECTION = 4;
	const mds::Message::MessageId M_VIEW_UPDATE = 5;
}