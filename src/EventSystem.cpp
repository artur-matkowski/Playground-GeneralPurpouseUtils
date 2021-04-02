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
		uint32_t dataLength = _this->m_sizeOfArg;
		uint32_t dataLengthNet = htonl(dataLength);


		uint32_t evIDlength = strlen(_this->m_evID);
		uint32_t evIDlengthNet = htonl(evIDlength);

		char* networkBuff = _this->m_owner->m_networkBuff;

		//copy string length
		memcpy(networkBuff
				, &evIDlengthNet
				, sizeof(uint32_t));
		//copy string
		memcpy(networkBuff + sizeof(uint32_t)
				, _this->m_evID
				, evIDlength);
		networkBuff[ sizeof(uint32_t) + evIDlength] = '\0';

		//serialize data, if serializable
		if( _this->m_serializer!=0 )
		{	
			_this->m_serializer->clear();
			_this->m_serializer->Serialize( (bfu::SerializableClassInterface*) data );
			data = _this->m_serializer->data();
			dataLength = _this->m_serializer->size();
			dataLengthNet = htonl( dataLength );
		}

		memcpy(networkBuff + sizeof(uint32_t) + evIDlength + 1
				, &dataLengthNet
				, sizeof(uint32_t) );

		memcpy(networkBuff + sizeof(uint32_t)*2 + evIDlength + 1
				, data
				, dataLength );

		std::vector<std::pair<char[16], uint16_t> > &propagationTargets = _this->m_owner->m_propagationTargets;


		for(int i=0; i<propagationTargets.size(); ++i)
		{
			bfu::udp::Write(networkBuff
							, sizeof(uint32_t)*2 + evIDlength+1 + dataLength
							, propagationTargets[i].first
							, propagationTargets[i].second);
		}
	}



	Event::Event( const char* desc
				, int sizeOfArg
				, bfu::MemBlockBase* memBlock
				, EventSystem* owner
				, void* serializationCache )
		:callbacks( custom_allocator<CallbackData>(memBlock) )
		,m_owner(owner)
		,m_sizeOfArg(sizeOfArg)
		,p_serializationCache(serializationCache)
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






	void EventSystem::RegisterFastEvent( const char* desc, int sizeOfArg , bfu::MemBlockBase* memBlock, bool isNetworked, void* serializationCache)
	{
		Event* ev = &m_fastEvents[m_lastFreeFastEvent];

		(*ev).~Event();
		new (ev) Event(desc, sizeOfArg, memBlock, this, serializationCache );

		if(isNetworked)
		{
			m_networkEvents[desc] = ev;
			ev->RegisterCallback(ev, Event::PushEventThroutghNetwork );
		}
		++m_lastFreeFastEvent;
	}
	void EventSystem::RegisterLateEvent( const char* desc, int sizeOfArg , bfu::MemBlockBase* memBlock, bool isNetworked, void* serializationCache)
	{
		Event* ev = (Event*)memBlock->allocate(1, sizeof(Event), alignof(Event));
		new (ev) Event(desc, sizeOfArg, memBlock, this, serializationCache );
		
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
			uint32_t eventTypeSize = ntohl(*(uint32_t*)m_networkBuff);

			Event* ev = m_networkEvents[m_networkBuff+sizeof(uint32_t)];
			void* data = m_networkBuff+sizeof(uint32_t)+eventTypeSize+1;
			uint32_t dataTypeSize = ntohl(*(uint32_t*)data);
			data = m_networkBuff+sizeof(uint32_t)*2+eventTypeSize+1;



			if( ev->m_serializer!=0 )
			{	
				ev->m_serializer->clear();
				ev->m_serializer->assignData((char*)data, dataTypeSize);

				ev->m_serializer->Deserialize( (bfu::SerializableClassInterface*) ev->p_serializationCache );

				supresNetworkPropagation = true;
				ev->Invoke( ev->p_serializationCache );
				supresNetworkPropagation = false;
			}
			else
			{
				supresNetworkPropagation = true;
				ev->Invoke( data );
				supresNetworkPropagation = false;
			}


		}
		return processedEvents;
	}
}