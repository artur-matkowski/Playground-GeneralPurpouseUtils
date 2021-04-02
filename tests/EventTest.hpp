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
	bool result = true;

	//Local event test
	{
		bfu::EventSystem es;
		Receiver receiver;


		es.RegisterFastEvent("test event", mBlock, false);
		bfu::Event* ev = es.GetFastEvent("test event");

		ev->RegisterCallback(&receiver, Receiver::alter);

		int arg = (int)'r';
		ev->Invoke(&arg);

		result |= receiver.i==(int)'r';
		log::debug << "Local event callback arg: int="<<arg<<" result="<< receiver.i << std::endl;
	}

	//remote event test
	{
		bfu::EventSystem es;
		Receiver receiver;

		es.PushPropagationTarget("127.0.0.1", 8888);


		es.RegisterFastEvent("test event", mBlock, true);
		bfu::Event* ev = es.GetFastEvent("test event");

		ev->RegisterCallback(&receiver, Receiver::alter);

		int arg = (int)'r';
		ev->Invoke(&arg);

		result |= receiver.i==(int)'r';
		log::debug << "Local event callback arg: int="<<arg<<" result="<< receiver.i << std::endl;
	}





    if( result )
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