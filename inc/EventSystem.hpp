#ifndef H_EventSystem
#define H_EventSystem 
#include "ObjectSerialization/SerializerBase.hpp"
#include <vector>
#include <map>
#include <string>

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
		std::vector<CallbackData, custom_allocator<CallbackData>> callbacks;
		char* descriptor = nullptr;

		static bfu2::SerializerBase* serializer;
		friend EventSystem;

	public:
		Event( const char* desc = 0, bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock(), bool isNetworked = false );
		~Event();

		void DispouseContent();

		void Invoke(void* invokeData);
		void RegisterCallback(void* receiver, Callback callback);
		void UnRegisterCallback(void* receiver);
		void UnRegisterCallback(Callback callback);

		inline const char* GetDescriptor(){ return descriptor; }
	};


	////////////////////////////////////////////////////////////

	class EventSystem
	{
		uint8_t 						m_lastFreeFastEvent = 0;
		Event 							m_fastEvents[256];

		std::map<bfu::string, Event*> 	m_lateEvents;
		std::map<bfu::string, Event*> 	m_networkEvents;

	public:
		void RegisterFastEvent( const char* desc = 0, bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock(), bool isNetworked = false );
		inline Event* GetFastEvent(int i){ return &(m_fastEvents[i]); }
		inline Event* GetFastEvent(const char* desc)
		{
			for(uint8_t i = 0; i<m_lastFreeFastEvent; ++i)
			{
				if( strcmp(desc, m_fastEvents[i].GetDescriptor())==0 )
					return &(m_fastEvents[i]);
			}
			return nullptr;
		}

		void DisableNetworkPropagation(Event*);
		inline void SetSerializer(bfu2::SerializerBase* p){ Event::serializer = p; }
	};
}

#endif