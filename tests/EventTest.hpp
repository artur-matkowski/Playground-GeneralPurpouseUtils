#ifndef _H_EventTest
#define _H_EventTest
#include "bfu.hpp"



struct Receiver
{
	int i = -1;
	static void alter(void* target, void* data)
	{
		int* arg = (int*)data;
		Receiver* _this = (Receiver*)target;
		_this->i = *arg;
	}
};

bool EventTest( bfu::MemBlockBase* mBlock )
{
	bfu::EventSystem es;
	Receiver receiver;

	es.RegisterFastEvent("test event", mBlock, false);
	bfu::Event* ev = es.GetFastEvent("test event");

	ev->RegisterCallback(&receiver, Receiver::alter);

	int arg = 43;
	ev->Invoke(&arg);


    if( receiver.i==43 )
	{
		log::warning << "<<<<<<<<<<<<<<<< Event Test concluded : SUCCES\n" << std::endl;
		return true;
	}
	else
	{
		log::error << "<<<<<<<<<<<<<<<< Event Test concluded : FAILED\n" << std::endl;
		return false;		
	}
}

#endif