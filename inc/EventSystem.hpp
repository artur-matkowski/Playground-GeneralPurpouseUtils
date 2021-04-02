#ifndef H_EventSystem
#define H_EventSystem 
#include "ObjectSerialization/SerializerBase.hpp"
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
	public:
		struct NetworkReceiver
		{
			char* m_networkBuff = nullptr;
			char* m_eventID = nullptr;
			int sizeOfArgs = 0;
			std::vector<std::pair<char[16], uint16_t> > * p_propagationTargets;
		};

	protected: 
		NetworkReceiver networkReceiver;

		std::vector<CallbackData, custom_allocator<CallbackData>> callbacks;
		char* m_evID = nullptr;

		static bfu2::SerializerBase* serializer;
		friend EventSystem;


		Event( const char* desc = 0, bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock()
				, char* networkBuff = nullptr
				, int sizeOfArg = 0
				, std::vector<std::pair<char[16], uint16_t> > * p_propagationTargets = nullptr );
	public:
		~Event();

		void DispouseContent();

		void Invoke(void* invokeData);
		void RegisterCallback(void* receiver, Callback callback);
		void UnRegisterCallback(void* receiver);
		void UnRegisterCallback(Callback callback);

		inline const char* GetEventID(){ return m_evID; }
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


	public:
		void RegisterFastEvent( const char* desc = 0
								, bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock()
								, bool isNetworked = false
								, int sizeOfArg = 0 );
		void RegisterLateEvent( const char* desc = 0
								, bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock()
								, bool isNetworked = false
								, int sizeOfArg = 0 );
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
		inline void SetSerializer(bfu2::SerializerBase* p){ Event::serializer = p; }
		inline void PushPropagationTarget(const char* host, uint16_t port)
		{
			m_propagationTargets.emplace_back( std::pair<char[16], uint16_t>() );
			strncpy(m_propagationTargets.back().first, host, 16);
			m_propagationTargets.back().second = port;
		}
	};
}

#endif