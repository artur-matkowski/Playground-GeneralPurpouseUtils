#ifndef H_Event
#define H_Event
#include <vector>
#include <map>
#include <cstring>

#include "SerializableVarVector.hpp"



namespace bfu{

	class EventArgsBase: public SerializableClassBase
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

	class Event
	{
		CallbackList 									m_callbacks;
		EventArgsBase* 									m_arg = 0;
		char* 											m_token = 0;

		//do not delete thouse pointers
		std::vector<std::pair<const char*, const int>>* m_propagationTargets = 0;
		bfu::udp* 										m_udp = 0;

		friend EventSystem;

		template<class ArgType>
		inline void EnableNetworkBehaviour(const char* token, 
											std::vector<std::pair<const char*, const int>>* propagationTarget,
											bfu::udp* _udp)
		{
			m_arg = new ArgType();
			m_propagationTargets = propagationTarget;
			m_udp = _udp;

			int size = std::strlen(token);
			m_token = new char[size];
			std::strcpy(m_token, token);
		}

		inline void DisableNetworkBehaviour()
		{
			if(m_arg!=0)
				delete m_arg;

			if(m_token!=0)
				delete m_token;

			m_arg = 0;
			m_token = 0;
		}

		inline void InvokeLocaly(EventArgsBase& data) 
		{
			m_callbacks.Invoke(data);
		}

		inline void InvokeRemotly(EventArgsBase& data) 
		{
			if(m_propagationTargets==0)
				return;

			for(auto it = m_propagationTargets->begin(); it!=m_propagationTargets->end(); ++it)
			{
				m_udp->Write(data, m_token, it->first, it->second);
			}
		}


		inline void Invoke(JSONStream& stream)
		{
			if(m_arg==0)
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
	};

	class EventSystem
	{
		std::map<const char*, Event, cmpByStringLength> 	m_events;
		std::vector<std::pair<const char*, const int>> 		m_propagationTargets;

		bfu::udp 											m_udp;
		bfu::udp::packet 									m_pkg;


	public:

		inline bool processNetworkQueuedEvents()
		{
			bool ret = false;

			while(m_udp.Read(m_pkg, false))
			{
				auto it = m_events.find(m_pkg.m_id.GetRef().c_str());

				if( it != m_events.end() )
				{
					it->second.Invoke(m_pkg.m_data.GetRef());
					ret = true;
				}
				else
				{
					log::warning << "Can't find network event \"" << m_pkg.m_id.GetRef().c_str() << "\" from host: " << m_pkg.m_host << std::endl;
				}
			}

			return ret;
		}

		inline Event& operator[](const char* token)
		{
			return m_events[token];
		}

		inline void EnableNetworkListening(int port)
		{
			m_udp.StartListening(port);
		}

		inline void DisableNetworkListening()
		{
			m_udp.StopListening();
		}

		template<class ArgType>
		inline void EnableNetworkBehaviour(const char* token)
		{
			m_events[token].EnableNetworkBehaviour<ArgType>(token, &m_propagationTargets, &m_udp);
		}

		inline void DisableNetworkBehaviour(const char* token)
		{
			m_events[token].DisableNetworkBehaviour();
		}

		inline void RegisterPropagationTarget(const char* host, const int port)
		{
			m_propagationTargets.push_back(std::pair<const char*, const int>(host, port));
		}

		inline void UnregisterPropagationTarget(const char* host, const int port)
		{
			//TBD
		}
	};
}

#endif
