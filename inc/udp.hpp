#ifndef H_UDP
#define	H_UDP
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>


#define PACKAGESIZE 65507


namespace bfu{
	class udp
	{
	private:
		int m_socket = -1; 
		int m_port = -1;


		struct sockaddr_in si_me;

	
	public:

		udp(int Port = -1);
		~udp();

		bool StartListening(int port);
		void StopListening();
		int GetPort();

		int Read(char* outBuff, int buffSize, char* remoteHost, int hostBuffSize, bool isBlocking = false );
		static void Write(const char * buff, int buffsize, const char* host, int port);

	};







}




#endif