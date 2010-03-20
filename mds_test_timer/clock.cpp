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
protected:
	virtual bool ProcessMessage(const mds::Message& message)
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
		return true;
	}
private:
	int number_;
	unsigned period_;

private:
	static int number;
};
int Clock::number = 0;

class TestSend
	: public mds::Object
{
public:
	TestSend(mds::MessageSystem& messageSystem)
		: Object(messageSystem),
		  number_(++number)
	{
	}
protected:
	virtual bool ProcessMessage(const mds::Message& message)
	{
		std::cout << "In TestSend #" << number_ << " ProcessMessage, message_id = " << message.get_message_id() << std::endl;
		if( message.get_message_id() > 4 )
		{
			SendSystemMessage(mds::Message(0, NULL));
		}
		else
		{
			Send(mds::Message(message.get_message_id()+1, NULL));
		}
		return true;
	}
private:
	int number_;
private:
	static int number;
};
int TestSend::number = 0;


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
	{
		ClockMessageSystem messageSystem;
		TestSend testSend1(messageSystem);
		TestSend testSend2(messageSystem);
		testSend1.Post(mds::Message(0, NULL), 100);
		testSend2.Post(mds::Message(0, NULL), 300);
		messageSystem.Loop();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}