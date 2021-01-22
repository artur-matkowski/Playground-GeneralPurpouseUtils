#ifndef _H_EventTest
#define _H_EventTest
#include "bfu.hpp"


class EventArgs: public bfu::EventArgsBase
{
public:
	bfu::SerializableVar<int> m_var;


public:
	EventArgs(bfu::MemBlockBase* mBlock)
		:bfu::EventArgsBase(mBlock)
		,m_var("m_var",this)
	{
		m_var = 11;
	}

	EventArgs(const EventArgs& copy)
		:bfu::EventArgsBase(copy.m_mBlock)
		,m_var("m_var", this)
	{
		m_var = copy.m_var;
	}
};


bool EventTest( bfu::MemBlockBase* mBlock )
{
	bfu::MonotonicMemBlock<1024*1024> memBlock;
	int test = 5;
    bfu::CallbackId id = 0;
    int result = 0;

    bfu::EventSystem es = bfu::EventSystem(&memBlock);


	if(fork() == 0)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		es.RegisterPropagationTarget("127.0.0.1", 8888);
		//es.UnregisterPropagationTarget("127.0.0.1", 8888);
    	es.InitEvent<EventArgs>("testEvent");
    	es.EnableNetworkBoadcast<EventArgs>();

    	es.RegisterCallback<EventArgs>(id, [&](bfu::EventArgsBase& a)
	    {
		    EventArgs* args = (EventArgs*)&a;
	    	test += args->m_var; 
			log::info << "testEvent invoked1 " << test << std::endl;
	    });

    	es.Invoke<EventArgs>([&](EventArgs& args) 
	    {
	    	args.m_var = 11; 
	    });

	    exit(0);
		
	}
	else
	{
		es.EnableNetworkListening(8888);
		es.InitEvent<EventArgs>("testEvent");
		es.EnableNetworkListen<EventArgs>();
		es.RegisterCallback<EventArgs>(id, [&](bfu::EventArgsBase& a)
	    {
		    EventArgs* args = (EventArgs*)&a;
	    	test += args->m_var; 
			log::info << "testEvent invoked2 " << test << std::endl;
	    });

		es.RegisterCallback<EventArgs>(id, [&](bfu::EventArgsBase& a)
	    {
			log::info << "testEvent invoked3 " << test << std::endl;
	    });


		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		while(!es.ProcessNetworkQueuedEvents());
	}
    



	if(result==0)
	{
    	log::info << "Test on sneder site, local invoke result: " << test << std::endl;
	}
	else
	{
		log::info << "Test on receiver site, remote invoke result: " << test << std::endl;
	}

    if( test==16 )
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