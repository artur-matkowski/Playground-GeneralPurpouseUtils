#include "EventSystem.hpp"
#include "log.hpp"


namespace bfu
{
	bool supresNetworkPropagation = false; //set to true while invoking from network, so event wont bounce beck


	void Event::PushEventThroutghNetwork(void* receiver, void* data)
	{
		if(supresNetworkPropagation)
			return;

		Event* _this = (Event*)receiver;

		uint32_t evIDlength = strlen(_this->m_evID);

		char* networkBuff = _this->m_owner->m_networkBuff;

		memcpy(networkBuff, &evIDlength, sizeof(uint32_t));
		memcpy(networkBuff + sizeof(uint32_t)
				, _this->m_evID
				, evIDlength);
		networkBuff[ sizeof(uint32_t) + evIDlength] = '\0';
		memcpy(networkBuff + sizeof(uint32_t) + evIDlength + 1
				, data
				, _this->m_sizeOfArg);

		std::vector<std::pair<char[16], uint16_t> > &propagationTargets = _this->m_owner->m_propagationTargets;


		for(int i=0; i<propagationTargets.size(); ++i)
		{
			bfu::udp::Write(networkBuff
							, sizeof(uint32_t) + evIDlength+1 + _this->m_sizeOfArg
							, propagationTargets[i].first
							, propagationTargets[i].second);
		}
		log::info << "KURWAAAAAAAAAAAAAAAAAA" << std::endl;
	}



	Event::Event( const char* desc
				, int sizeOfArg
				, bfu::MemBlockBase* memBlock
				, EventSystem* owner)
		:callbacks( custom_allocator<CallbackData>(memBlock) )
		,m_owner(owner)
		,m_sizeOfArg(sizeOfArg)
	{
		if(desc != 0)
		{
			int length = strlen(desc);
			m_evID = (char*)memBlock->allocate(length+1, sizeof(char), alignof(char) );
			strncpy(m_evID, desc, length);
			m_evID[length] = '\0';	
		}
	}
	Event::~Event() 
		// we are be "dropping the ball" on aplication close, to make it a bit faster. 
		//Assumption is that events are not destroyed during aplication livetime
	{}


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






	void EventSystem::RegisterFastEvent( const char* desc, int sizeOfArg , bfu::MemBlockBase* memBlock, bool isNetworked)
	{
		Event* ev = &m_fastEvents[m_lastFreeFastEvent];

		(*ev).~Event();
		new (ev) Event(desc, sizeOfArg, memBlock, this );

		if(isNetworked)
		{
			m_networkEvents[desc] = ev;
			ev->RegisterCallback(ev, Event::PushEventThroutghNetwork );
		}
		++m_lastFreeFastEvent;
	}
	void EventSystem::RegisterLateEvent( const char* desc, int sizeOfArg , bfu::MemBlockBase* memBlock, bool isNetworked)
	{
		Event* ev = (Event*)memBlock->allocate(1, sizeof(Event), alignof(Event));
		new (ev) Event(desc, sizeOfArg, memBlock, this );
		
		m_lateEvents[ desc ] = ev;
	}
	void EventSystem::DisableNetworkPropagation(Event* ev)
	{
		ev->UnRegisterCallback(Event::PushEventThroutghNetwork);
	}


	int EventSystem::PullNetworkEvents()
	{
		char remoteHost[16];
		int processedEvents = 0;
		while( m_udp.Read( m_networkBuff, PACKAGESIZE, remoteHost, 16, false) > 0 )
		{
			++processedEvents;
			log::debug << "Received udp event from host: "<< remoteHost << std::endl;
			uint32_t eventTypeSize = *(uint32_t*)m_networkBuff;

			Event* ev = m_networkEvents[m_networkBuff+sizeof(uint32_t)];

			supresNetworkPropagation = true;
			ev->Invoke(m_networkBuff+sizeof(uint32_t)+eventTypeSize+1);
			supresNetworkPropagation = false;

		}
		return processedEvents;
	}
}