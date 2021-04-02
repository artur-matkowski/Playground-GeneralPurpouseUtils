#include "EventSystem.hpp"
#include "udp.hpp"

namespace bfu
{

	void PushEventThroutghNetwork(void* receiver, void* data)
	{
		Event::NetworkReceiver* receiverData = (Event::NetworkReceiver*)receiver;

		uint32_t evIDlength = strlen(receiverData->m_eventID);

		memcpy(receiverData->m_networkBuff, &evIDlength, sizeof(uint32_t));
		memcpy(receiverData->m_networkBuff + sizeof(uint32_t)
				, receiverData->m_eventID
				, evIDlength);
		memcpy(receiverData->m_networkBuff + sizeof(uint32_t) + evIDlength
				, receiverData->m_eventID
				, receiverData->sizeOfArgs);

		std::vector<std::pair<char[16], uint16_t> > &propagationTargets = *receiverData->p_propagationTargets;


		for(int i=0; i<propagationTargets.size(); ++i)
		{
			bfu::udp::Write(receiverData->m_networkBuff
							, sizeof(uint32_t) + evIDlength + receiverData->sizeOfArgs
							, propagationTargets[i].first
							, propagationTargets[i].second);
		}
	}



	Event::Event( const char* desc, bfu::MemBlockBase* memBlock
				, char* networkBuff
				, int sizeOfArg
				, std::vector<std::pair<char[16], uint16_t> > * p_propagationTargets )
		:callbacks( custom_allocator<CallbackData>(memBlock) )
	{
		if(desc != 0)
		{
			int length = strlen(desc);
			m_evID = (char*)memBlock->allocate(length+1, sizeof(char), alignof(char) );
			strncpy(m_evID, desc, length);
			m_evID[length] = '\0';

			if(networkBuff!=nullptr)
			{
				networkReceiver.m_networkBuff = networkBuff;
				networkReceiver.m_eventID = m_evID;
				networkReceiver.sizeOfArgs = sizeOfArg;
				networkReceiver.p_propagationTargets = p_propagationTargets;
				RegisterCallback(&networkReceiver, PushEventThroutghNetwork);
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

		if( m_evID!=0 )
			MemBlockBase::DeallocateUnknown(m_evID);		
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






	void EventSystem::RegisterFastEvent( const char* desc , bfu::MemBlockBase* memBlock, bool isNetworked, int sizeOfArg )
	{
		m_fastEvents[m_lastFreeFastEvent].~Event();
		new (&m_fastEvents[m_lastFreeFastEvent]) Event(desc, memBlock, isNetworked ? m_networkBuff : nullptr, sizeOfArg, &m_propagationTargets);
		++m_lastFreeFastEvent;
	}
	void EventSystem::RegisterLateEvent( const char* desc , bfu::MemBlockBase* memBlock, bool isNetworked, int sizeOfArg)
	{
		Event* ev = (Event*)memBlock->allocate(1, sizeof(Event), alignof(Event));
		new (ev) Event(desc, memBlock, isNetworked ? m_networkBuff : nullptr, sizeOfArg, &m_propagationTargets );
		
		m_lateEvents[ desc ] = ev;
	}
	void EventSystem::DisableNetworkPropagation(Event* ev)
	{
		ev->UnRegisterCallback(PushEventThroutghNetwork);
	}
}