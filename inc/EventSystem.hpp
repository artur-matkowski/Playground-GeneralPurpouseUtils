#ifndef H_EventSystem
#define H_EventSystem 
#include "ObjectSerialization/SerializerBase.hpp"
#include "udp.hpp"
#include <vector>
#include <map>
#include <string>

#define PACKAGESIZE 65507

namespace bfu
{


	typedef void (*Callback)(void* receiver, void* data);

	struct CallbackData
	{
		void* receiver;
		Callback callback;

		CallbackData(void* _receiver, Callback _callback): receiver(_receiver), callback(_callback) {};
	};


	////////////////////////////////////////////////////////////

	class EventSystem;

	class Event
	{
	protected: 
		std::vector<CallbackData, custom_allocator<CallbackData>> callbacks;
		char* 							m_evID = nullptr;
		EventSystem* 					m_owner = nullptr;
		int 							m_sizeOfArg = 0;
		void*							p_serializationCache = nullptr;
		bfu2::SerializerBase* 			m_serializer = nullptr;

		friend EventSystem;

		Event(){};
		Event( const char* desc
				, int sizeOfArg
				, bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock()
				, EventSystem* owner = nullptr
				, void* serializationCache = nullptr);
	public:
		~Event();

		void DispouseContent();

		void Invoke(void* invokeData);
		void RegisterCallback(void* receiver, Callback callback);
		void UnRegisterCallback(void* receiver);
		void UnRegisterCallback(Callback callback);

		inline const char* GetEventID(){ return m_evID; }
		static void PushEventThroutghNetwork(void* receiver, void* data);

		inline void SetSerializer(bfu2::SerializerBase* p){ m_serializer = p; }
		inline bfu2::SerializerBase* GetSerializer(bfu2::SerializerBase* p){ return m_serializer; }
	};


	////////////////////////////////////////////////////////////
	struct cmp_str
	{
	   bool operator()(char const *a, char const *b) const
	   {
	      return std::strcmp(a, b) < 0;
	   }
	};

	class EventSystem
	{
		uint8_t 						m_lastFreeFastEvent = 0;
		Event 							m_fastEvents[256];

		std::map<const char*, Event*, cmp_str> 	m_lateEvents;

		std::map<const char*, Event*, cmp_str> 	m_networkEvents;

		std::vector<std::pair<char[16], uint16_t> > m_propagationTargets;
		char 							m_networkBuff[PACKAGESIZE];


		friend Event;

		bfu::udp						m_udp;

	public:
		void RegisterFastEvent( const char* desc 
								, int sizeOfArg 
								, bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock()
								, bool isNetworked = false
								, void* serializationCache = nullptr );
		void RegisterLateEvent( const char* desc
								, int sizeOfArg
								, bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock()
								, bool isNetworked = false
								, void* serializationCache = nullptr );
		inline Event* GetFastEvent(int i){ return &(m_fastEvents[i]); }
		inline Event* GetFastEvent(const char* desc)
		{
			for(uint8_t i = 0; i<m_lastFreeFastEvent; ++i)
			{
				if( strcmp(desc, m_fastEvents[i].GetEventID())==0 )
					return &(m_fastEvents[i]);
			}
			return nullptr;
		}

		void DisableNetworkPropagation(Event*);
		inline void PushPropagationTarget(const char* host, uint16_t port)
		{
			m_propagationTargets.emplace_back( std::pair<char[16], uint16_t>() );
			strncpy(m_propagationTargets.back().first, host, 16);
			m_propagationTargets.back().second = port;
		}

		int PullNetworkEvents();
		inline bool StartListening(int port){ return m_udp.StartListening(port); }
		inline char* GetNetworkBuffer(){ return m_networkBuff; }
	};
}

#endif