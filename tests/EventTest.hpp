#ifndef _H_EventTest
#define _H_EventTest
#include "bfu.hpp"


class EventArgs: public bfu::EventArgsBase
{
public:
	bfu::SerializableVar<int> m_var;


public:
	EventArgs()
		:bfu::EventArgsBase()
		,m_var("m_var",this)
	{
		m_var = 11;
	}

	EventArgs(const EventArgs& copy)
		:bfu::EventArgsBase()
		,m_var("m_var",this)
	{
		m_var = copy.m_var;
	}
};


bool EventTest(int argc, char** argv)
{

	int test = 5;
    bfu::CallbackId id;
    int result;

    bfu::EventSystem es;


	if(argc>1 && strcmp(argv[1], "sender") == 0 )
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
			log::info << "testEvent invoked " << test << std::endl;
	    });

    	es.Invoke<EventArgs>([&](EventArgs& args) 
	    {
	    	args.m_var = 11; 
	    });

	}
	else
	{
		
		result = fork();
		
		if(result==0)
		{
			char cmd[128] = {0};
			sprintf(cmd, "xterm -e \"%s sender\"", argv[0]);
			system(cmd);
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
				log::info << "testEvent invoked " << test << std::endl;
		    });

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			while(!es.ProcessNetworkQueuedEvents());
		}
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