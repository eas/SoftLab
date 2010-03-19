#include <windows.h>
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
	Clock(MessageSystem& messageSystem, int number, unsigned period)
		: Object(messageSystem),
		  number_(number),
		  period_(period)
	{
	}
	virtual void ProcessMessage(const mds::Message&)
	{
		static int i=0;
		++i;
		if( i>15 )
		{
			PostSystemMessage( mds::Message(0, NULL), 0 );
		}
		SYSTEMTIME time;
		GetSystemTime(&time);
		std::cout << "Clock" << number_ << " call# " << i <<"\t" << time.wHour+6 << " " << time.wMinute << " " << time.wSecond << " " << std::endl;
		this->Post( mds::Message(0, NULL), period_ );
	}
private:
	int number_;
	unsigned period_;
};


int main()
{
	MessageSystem messageSystem;
	Clock clock1(messageSystem, 1, 2000);
	Clock clock2(messageSystem, 2, 7000);
	clock1.Post(mds::Message(0, NULL), 0);
	clock2.Post(mds::Message(0, NULL), 0);
	messageSystem.Loop();
	return 0;
}