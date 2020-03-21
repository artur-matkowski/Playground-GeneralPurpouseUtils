#ifndef H_UDP
#define	H_UDP
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

#include "SerializableVarVector.hpp"

namespace bfu{
	class udp
	{
		int m_socket; 
		int m_port;
		struct sockaddr_in si_me, si_other;
		JSONStream m_json;
		unsigned int slen = sizeof(sockaddr_in);

	public:
		class packet: public SerializableClassBase
		{
		public:
			SerializableVar<stream> m_id;
			SerializableVar<JSONStream> m_data;
			#define HOSTSIZE 16
			char m_host[HOSTSIZE] = {0};
			int m_port;

			packet()
				:SerializableClassBase()
				,m_id("m_id",this)
				,m_data("m_data",this)
			{}

			void SetHost(const char* host)
			{
				std::strncpy(m_host, host, HOSTSIZE);
			}
		};

		udp(int Port);

		bool Read( packet &out, bool isBlocking );
		bool Write( packet &in );

		std::string Read(std::string & remoteHost);
		void Read(char* outBuff, int buffSize);
		void Read(char* outBuff, int buffSize, std::string & remoteHost);
		static void Write(const std::string & buff, const char* host, int port);
		static void Write(const char * buff, int buffsize, const char* host, int port);

		int GetPort();
	};
}




#endif