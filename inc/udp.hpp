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
		struct sockaddr_in si_me;
		JSONStream m_json;

	public:
		class packet: public SerializableClassBase
		{
		public:
			SerializableVar<std::string> id;
			SerializableVar<std::string> data;
			char* host;

			packet()
				:SerializableClassBase()
				,id("id",this)
				,data("data",this)
			{}
		};

		udp(int Port);

		std::string Read(std::string & remoteHost);
		void Read(char* outBuff, int buffSize);
		void Read(char* outBuff, int buffSize, std::string & remoteHost);
		static void Write(const std::string & buff, const char* host, int port);
		static void Write(const char * buff, int buffsize, const char* host, int port);

		int GetPort();
	};
}




#endif