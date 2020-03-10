#ifndef H_UDP
#define	H_UDP
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

#include "stream.hpp"

namespace bfu{
	class Udp
	{
		int s, port;
		struct sockaddr_in si_me;

	public:
		Udp(int Port);

		std::string Read();
		std::string Read(std::string & remoteHost);
		void Read(char* outBuff, int buffSize);
		void Read(char* outBuff, int buffSize, std::string & remoteHost);
		static void Write(const std::string & buff, const char* host, int port);
		static void Write(const char * buff, int buffsize, const char* host, int port);

		int GetPort();
	};
}




#endif