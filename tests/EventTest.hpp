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
	SerializableVar<bool> m_var;
	SerializableVar<float> m_var2;



public:
	EventArgs()
		:EventArgsBase()
		,m_var("m_var",this)
		,m_var2("m_var2",this)
	{
		m_var = randb();
		m_var2 = randf();
	}

	EventArgs(const EventArgs& copy)
		:EventArgsBase()
		,m_var("m_var",this)
		,m_var2("m_var2",this)
	{
		m_var = copy.m_var;
		m_var2 = copy.m_var2;
	}
};

bool EventTest()
{
	float test = 5;

	EventSystem es;

    bfu::CallbackList ev;
    CallbackId id;


    es["testEvent"].RegisterCallback(id, [&](EventArgsBase& a) 
    {
    	EventArgs* args = (EventArgs*)&a;
    	test += args->m_var2; 
    });

    //es.UnregisterCallback(id);


    EventArgs args;

    es["testEvent"].Invoke(args);

    log::info << "lambda test " << test << std::endl;

	return false;
}

#endif