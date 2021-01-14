#ifndef H_UDP
#define	H_UDP
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

#include "SerializableVarVector.hpp"

#define PACKAGESIZE 65507


namespace bfu{
	class udp
	{
	public:
		class packet: public SerializableClassBase
		{
    		char  m_buff[PACKAGESIZE] = {'0'};
		public:
			SerializableVar<stream> m_id;
			SerializableVar<JSONStream> m_data;
			#define HOSTSIZE 16
			char m_host[HOSTSIZE] = {0};
			int m_port;

			packet()
				:SerializableClassBase()
				,m_id("m_id",this, m_buff, PACKAGESIZE)
				,m_data("m_data",this)
			{}

			packet(const packet& cp)
				:SerializableClassBase()
				,m_id("m_id",this, m_buff, PACKAGESIZE)
				,m_data("m_data",this)
			{
				m_id = cp.m_id;
				m_data = cp.m_data;
				m_port = cp.m_port;

				std::strncpy(m_host, cp.m_host, HOSTSIZE);
			}

			void SetHost(const char* host)
			{
				std::strncpy(m_host, host, HOSTSIZE);
			}

			void SetData(SerializableClassBase& data)
			{
				m_data.GetRef().clear();
				m_data.GetRef() << data;
			}

			void SetId(const char* data)
			{
				m_id.GetRef().clear();
				m_id.GetRef() << data;
			}

			void clear()
			{
				m_id.GetRef().clear();
				m_data.GetRef().clear();
			}
		};

	private:
		int m_socket = -1; 
		int m_port = -1;
		struct sockaddr_in si_me, si_other;
		JSONStream m_json;
		unsigned int slen = sizeof(sockaddr_in);

		packet m_cache;

	
	public:

		udp(int Port = -1);
		~udp();

		bool StartListening(int port);
		void StopListening();

		bool Read( packet &out, bool isBlocking );
		bool Write( packet &in );
		bool Write( SerializableClassBase &in, const char* eventId, const char* host, int port);
		
		std::string Read(std::string & remoteHost);
		void Read(char* outBuff, int buffSize);
		void Read(char* outBuff, int buffSize, std::string & remoteHost);
		static void Write(const std::string & buff, const char* host, int port);
		static void Write(const char * buff, int buffsize, const char* host, int port);

		int GetPort();
	};
}




#endif