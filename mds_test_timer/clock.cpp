#if !defined NDEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#pragma warning( disable : 4985 )
#include <crtdbg.h>
#pragma warning( default : 4985 )
#endif

#include <windows.h>
#include <iostream>
#include "mds/mds.h"



class ClockMessageSystem
	: public mds::MessageSystem
{
public:
	virtual ~ClockMessageSystem()
	{
	}
protected:
	virtual bool SystemMessageTranslate(const mds::Message&)
	{
		return true;
	}
	virtual void IdleProcessing()
	{
		int i=2;
	}
	virtual void DeletingMessage(const mds::Message& message)
	{
		delete reinterpret_cast<int*>(message.get_data());
	}
	virtual void NonexistentObjectTranslate(const mds::Message& message)
	{
		delete reinterpret_cast<int*>(message.get_data());
	}
};

class Clock
	: public mds::Object
{
public:
	Clock(ClockMessageSystem& messageSystem, unsigned period)
		: Object(messageSystem),
		  number_(++number),
		  period_(period)
	{
	}
	virtual void ProcessMessage(const mds::Message& message)
	{
		delete reinterpret_cast<int*>(message.get_data());
		static int i=0;
		++i;
		if( i>15 )
		{
			PostSystemMessage( mds::Message(0, NULL), 0 );
		}
		SYSTEMTIME time;
		GetSystemTime(&time);
		std::cout << "Clock" << number_ << " call# " << i <<"\t" << time.wHour+6 << " " << time.wMinute << " " << time.wSecond << " " << std::endl;
		this->Post( mds::Message(0, new int(number_*100+i)), period_ );
	}
private:
	int number_;
	unsigned period_;

private:
	static int number;
};
int Clock::number = 0;


int main()
{
	{ // code block, need it to testing memory leaks
		ClockMessageSystem messageSystem;
		Clock clock1(messageSystem, 200);
		Clock clock2(messageSystem, 700);
		{
			Clock clock3(messageSystem, 900);
			clock3.Post(mds::Message(0, new char(0)), 0);
		}
		clock1.Post(mds::Message(0, NULL), 0);
		clock2.Post(mds::Message(0, NULL), 0);
		messageSystem.Loop();
		//messageSystem.ClearQueue();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}