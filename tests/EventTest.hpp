#ifndef _H_EventTest
#define _H_EventTest
#include "bfu.hpp"

template<typename Func>
void LambdaTest(Func f) {
    f(10);
}

class EventArgs: public EventArgsBase
{
public:
	SerializableVar<int> m_var;



public:
	EventArgs()
		:EventArgsBase()
		,m_var("m_var",this)
	{
		m_var = 11;
	}

	EventArgs(const EventArgs& copy)
		:EventArgsBase()
		,m_var("m_var",this)
	{
		m_var = copy.m_var;
	}
};

bool EventTest(int argc, char** argv)
{

	int test = 5;

	EventSystem es;

    CallbackId id;

    EventArgs args;

	if(argc>1 && strcmp(argv[1], "sender") == 0 )
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		log::info << "Invoking Remote Event" << std::endl;

		es.EnableNetworkPropagation<EventArgs>("testEvent");
		es.RegisterPropagationTarget("127.0.0.1", 8888);
    	es["testEvent"].Invoke(args);

    	//while(1);
    	exit(0);
	}
	else
	{		
		int result = 1;
		//result = fork();
		
		if(result==0)
		{
			char cmd[128] = {0};
			sprintf(cmd, "xterm -e \"%s sender\"", argv[0]);
			system(cmd);
			exit(0);
		}
		else
		{
			es.EnableNetworkListening( 8888 );
			es.EnableNetworkPropagation<EventArgs>("testEvent");

			es["testEvent"].RegisterCallback(id, [&](EventArgsBase& a) 
		    {
		    	EventArgs* args = (EventArgs*)&a;
		    	test += args->m_var; 
    			log::info << "testEvent invoked " << test << std::endl;
		    });

			while(!es.processNetworkQueuedEvents());
		}
	}



    

    //es.UnregisterCallback(id);




    log::info << "lambda test " << test << std::endl;

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