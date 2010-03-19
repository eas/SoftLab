//#include <WinBase.h>
#include <iostream>
#include "mds/mds.h"

class MessageSystem
	: public mds::MessageSystem
{
public:
	virtual bool SystemMessageTranslate(const mds::Message&)
	{
		return true;
	}
	virtual void IdleProcessing()
	{
	}
};

class Clock
	: public mds::Object
{
public:
	Clock(MessageSystem& messageSystem)
		: Object(messageSystem)
	{
	}
	virtual void ProcessMessage(const mds::Message&)
	{
		//SystemTime systemTime;
		//GetSystemTime(&systemTime);
		std::cout << "Clock" << std::endl;
	}
};


int main()
{
	MessageSystem messagSystem;
	return 0;
}