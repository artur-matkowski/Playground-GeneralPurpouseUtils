#include "EventSystem.hpp"
#include "udp.hpp"

namespace bfu
{

	void PushEventThroutghNetwork(void* receiver, void* data)
	{

	}



	Event::Event( const char* desc, bfu::MemBlockBase* memBlock, bool isNetworked )
		:callbacks( custom_allocator<CallbackData>(memBlock) )
	{
		if(desc != 0)
		{
			int length = strlen(desc);
			descriptor = (char*)memBlock->allocate(length, sizeof(char), alignof(char) );
			strncpy(descriptor, desc, length);

			if(isNetworked)
			{
				RegisterCallback(descriptor, PushEventThroutghNetwork);
			}
		}
	}
	Event::~Event() 
		// we are be "dropping the ball" on aplication close, to make it a bit faster. 
		//Assumption is that events are not destroyed during aplication livetime
	{}
	bfu2::SerializerBase* Event::serializer = nullptr;

	void Event::DispouseContent()
		// However if we need to destroy event we can do so too
	{
		callbacks.clear();

		if( descriptor!=0 )
			MemBlockBase::DeallocateUnknown(descriptor);		
	}


	void Event::Invoke(void* invokeData)
	{
		const int size = callbacks.size();
		
		for(int i=0; i<size; ++i)
		{
			CallbackData& cb = callbacks[i];
			cb.callback( cb.receiver, invokeData );
		}
	}
	void Event::RegisterCallback(void* receiver, Callback callback)
	{
		callbacks.emplace_back(receiver, callback);
	}
	void Event::UnRegisterCallback(void* receiver)
	{
		for(auto it = callbacks.begin(); it!=callbacks.end(); ++it)
		{
			if( it->receiver==receiver )
			{
				callbacks.erase(it);
				break;
			}
		}
	}
	void Event::UnRegisterCallback(Callback callback)
	{
		for(auto it = callbacks.begin(); it!=callbacks.end(); ++it)
		{
			if( it->callback==callback )
			{
				callbacks.erase(it);
				break;
			}
		}
	}






	void EventSystem::RegisterFastEvent( const char* desc , bfu::MemBlockBase* memBlock, bool isNetworked )
	{
		m_fastEvents[m_lastFreeFastEvent].~Event();
		new (&m_fastEvents[m_lastFreeFastEvent]) Event(desc, memBlock, isNetworked);
		++m_lastFreeFastEvent;
	}
	void EventSystem::DisableNetworkPropagation(Event* ev)
	{
		ev->UnRegisterCallback(PushEventThroutghNetwork);
	}
}