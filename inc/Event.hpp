#ifndef _H_Event2
#define _H_Event2
#include <vector>
#include <map>
#include <cstring>
#include "udp.hpp"
#include "log.hpp"
#include "SerializableVarVector.hpp"


namespace bfu{

	class EventArgsBase: public bfu::SerializableClassBase
	{
	public:
		bool isComingFromNetwork = false;
	};


	class CallbackBase
	{
	public:
		virtual void Execute(EventArgsBase& data) = 0;
	};


	typedef CallbackBase* CallbackId;


	template<typename Func>
	class Callback: public CallbackBase
	{
		Func m_callback;
	public:
		Callback(Func callback)
			:m_callback(callback)
		{}

		virtual void Execute(EventArgsBase& data)
		{
			m_callback(data);
		}
	};

	class CallbackList
	{
	protected:
		std::vector< CallbackBase* > m_callbacks;

	public:

		~CallbackList()
		{
			for(int i=0; i<m_callbacks.size(); ++i)
			{
				delete m_callbacks[i];
			}
		}

		inline void Invoke(EventArgsBase& args)
		{
			for(int i=0; i<m_callbacks.size(); ++i)
			{
				m_callbacks[i]->Execute(args);
			}
		}

		template<typename Func>
		inline void RegisterCallback(CallbackId& callbackId, Func f)
		{
			callbackId = new Callback<Func>(f);
			m_callbacks.push_back( callbackId );
		}

		inline void UnregisterCallback(CallbackId& callbackId)
		{
			for (std::vector< CallbackBase* >::iterator it = m_callbacks.begin() ; it != m_callbacks.end(); ++it)
			{
				if(*it == callbackId)
				{
					delete *it;
					m_callbacks.erase(it);
					break;
				}
			}
		}
	};

	class EventSystem;

	class EventBase
	{
		friend EventSystem;


		virtual void Init(const char* token, 
							std::vector<std::pair<std::string, int>>* propagationTarget,
							bfu::udp* _udp) = 0;

		virtual void Invoke(bfu::JSONStream& stream) = 0;
	};

	template<class ArgT>
	class Event: public EventBase
	{
		CallbackList 									m_callbacks;
		EventArgsBase* 									m_arg = 0;
		char* 											m_token = 0;

		//do not delete thouse pointers
		std::vector<std::pair<std::string, int>>* 		m_propagationTargets = 0;
		bfu::udp* 										m_udp = 0;

		bool 											m_networkBroadcast = false;
		bool 											m_networkListen = false;

		friend EventSystem;


		virtual void Init(const char* token, 
							std::vector<std::pair<std::string, int>>* propagationTarget,
							bfu::udp* _udp)
		{
			if( m_arg == 0 )
				m_arg = new ArgT();

			if( m_token != 0 )
				delete m_token;

			m_propagationTargets = propagationTarget;
			m_udp = _udp;

			int size = std::strlen(token);
			m_token = new char[size];
			std::strcpy(m_token, token);
		}

		inline void InvokeLocaly(EventArgsBase& data) 
		{
			m_callbacks.Invoke(data);
		}

		inline void InvokeRemotly(EventArgsBase& data) 
		{
			if( m_networkBroadcast == false )
				return;

			for(auto it = m_propagationTargets->begin(); it!=m_propagationTargets->end(); ++it)
			{
				m_udp->Write(data, m_token, it->first.c_str(), it->second);
			}
		}


		virtual void Invoke(bfu::JSONStream& stream)
		{
			if( m_networkListen == false )
			{
				return;
			}

			stream >> *m_arg;

			InvokeLocaly(*m_arg);
		}

	public:
		~Event()
		{
			if(m_arg!=0)
				delete m_arg;

			if(m_token!=0)
				delete m_token;
		}

		inline void Invoke(EventArgsBase& data) 
		{
			InvokeLocaly(data);
			InvokeRemotly(data);
		}

		template<typename Func>
		inline void RegisterCallback(CallbackId& callbackId, Func f)
		{
			m_callbacks.RegisterCallback<Func>(callbackId, f);
		}

		inline void UnregisterCallback(CallbackId& callbackId)
		{
			m_callbacks.UnregisterCallback(callbackId);
		}

		inline void EnableNetworkBoadcast()
		{
			m_networkBroadcast = true;
		}

		inline void DisableNetworkBoadcast()
		{
			m_networkBroadcast = false;
		}

		inline void EnableNetworkListen()
		{
			m_networkListen = true;
		}

		inline void DisableNetworkListen()
		{
			m_networkListen = false;
		}

		inline bool IsInitialized()
		{
			return m_arg != 0;
		}
	};


	class EventSystem
	{
		static std::map<const char*, EventBase*, cmpByStringLength> 	
																m_events;
		static std::vector<std::pair<std::string, int>> 		m_propagationTargets;

		static bfu::udp 										m_udp;
		static bfu::udp::packet 								m_pkg;

		template<class ArgT>
		static Event<ArgT>& GetEventRef()
		{
			static Event<ArgT> ev;
			return ev;
		}

		template<class ArgT>
		static void RegisterEvent(const char* token, ArgT& ev)
		{
			auto it = EventSystem::m_events.find(token);

			if( it != EventSystem::m_events.end() )
			{
				m_events[token] = &ev;
			}
			else
			{
				log::warning << "Attempting te reinitialize Event \"" << token << "\", breaking." << std::endl;
			}
		}
	public:

		template<class ArgT>
		static void InitEvent(const char* token)
		{
			auto it = EventSystem::m_events.find(token);

			if( it != EventSystem::m_events.end() )
			{
				log::warning << "Attempting te reinitialize Event \"" << token << "\", breaking." << std::endl;
				return;
			}

			EventSystem::GetEventRef<ArgT>().Init(token, &m_propagationTargets, &m_udp);
			m_events[token] = & EventSystem::GetEventRef<ArgT>();
		}

		template<class ArgT, typename Func>
		static void RegisterCallback(CallbackId& callbackId, Func f)
		{
			EventSystem::GetEventRef<ArgT>().template RegisterCallback<Func>(callbackId, f);
		}

		template<class ArgT>
		static void UnregisterCallback(CallbackId& callbackId)
		{
			EventSystem::GetEventRef<ArgT>().UnregisterCallback(callbackId);
		}

		template<class ArgT, typename Func>
		static void Invoke(Func func)
		{
			static ArgT arg;
			Event<ArgT> &ev = EventSystem::GetEventRef<ArgT>();

			if( !ev.IsInitialized() )
			{
				log::error << "Traying to invoke unitialized Event, breaking" << std::endl;
				return;
			}

			func( arg );
			ev.Invoke( arg );
		}

		template<class ArgT>
		static void Invoke(ArgT& arg)
		{
			Event<ArgT> &ev = EventSystem::GetEventRef<ArgT>();

			if( !ev.IsInitialized() )
			{
				log::error << "Traying to invoke unitialized Event, breaking" << std::endl;
				return;
			}

			ev.Invoke( arg );
		}



	
		static bool ProcessNetworkQueuedEvents()
		{

			bool ret = false;

			while(EventSystem::m_udp.Read(EventSystem::m_pkg, false))
			{
				auto it = EventSystem::m_events.find(EventSystem::m_pkg.m_id.GetRef().c_str());

				if( it != EventSystem::m_events.end() )
				{
					it->second->Invoke(EventSystem::m_pkg.m_data.GetRef());
					ret = true;
				}
				else
				{
					log::warning << "Can't find network event \"" << EventSystem::m_pkg.m_id.GetRef().c_str() << "\" from host: " << m_pkg.m_host << 
						"Did you initialized event?" << std::endl;
				}
			}

			return ret;
		}


		static void EnableNetworkListening(int port)
		{
			EventSystem::m_udp.StartListening(port);
		}

		static void DisableNetworkListening()
		{
			EventSystem::m_udp.StopListening();
		}

		template<class ArgT>
		static void EnableNetworkBoadcast()
		{
			EventSystem::GetEventRef<ArgT>().EnableNetworkBoadcast();
		}

		template<class ArgT>
		static void DisableNetworkBoadcast()
		{
			EventSystem::GetEventRef<ArgT>().DisableNetworkBoadcast();
		}

		template<class ArgT>
		static void EnableNetworkListen()
		{
			EventSystem::GetEventRef<ArgT>().EnableNetworkListen();
		}

		template<class ArgT>
		static void DisableNetworkListen()
		{
			EventSystem::GetEventRef<ArgT>().DisableNetworkListen();
		}

		static void RegisterPropagationTarget(const char* host, const int port)
		{
			EventSystem::m_propagationTargets.push_back(std::pair<std::string, int>(host, port));
		}

		static void UnregisterPropagationTarget(const char* host, const int port)
		{
			for(auto it = EventSystem::m_propagationTargets.begin();
				it != EventSystem::m_propagationTargets.end();
				++it)
			{
				if( strcmp(it->first.c_str(), host)==0 && it->second == port)
				{
					EventSystem::m_propagationTargets.erase(it);
					return;
				}
			}
		}

	};
}

#endif