#include "udp.hpp"
#include <log.hpp>

#define PACKAGESIZE 65507


namespace bfu{

	Udp::Udp(int Port)
		:port(Port)
	{
		if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		{
			log::error << "Creating socket" << std::endl;
			return;
		}

		// zero out the structure
		memset((char *) &si_me, 0, sizeof(si_me));

		si_me.sin_family = AF_INET;
		si_me.sin_port = htons(port);
		si_me.sin_addr.s_addr = htonl(INADDR_ANY);

		//bind socket to port
		if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
		{
			log::error << "Binding socket" << std::endl;
			return;
		}
		log::info << "Listening for udp on port " << Port << std::endl;
	}


	std::string Udp::Read()
	{
		std::string host;
		return this->Read(host);
	}

	std::string Udp::Read(std::string & remoteHost)
	{
		struct sockaddr_in si_other;

		//LOG_DEBUG("Waiting for data...", 0);
	    fflush(stdout);

		unsigned int slen = sizeof(sockaddr_in);
		char cache[PACKAGESIZE] = {0};


	    //try to receive some data, this is a blocking call

		if ((recvfrom(s, cache, PACKAGESIZE, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			log::error << "recvfrom2" << std::endl;
			return "";
		}
		remoteHost = std::string(inet_ntoa(si_other.sin_addr));

	    //print details of the client/peer and the data received
		log::debug << "Received udp msg: {" << cache << "} to {"<<inet_ntoa(si_other.sin_addr)<<":"<<ntohs(si_other.sin_port)<<"}" << std::endl;

		return std::string(cache);
	}

	void Udp::Read(char* outBuff, int buffSize)
	{
		std::string host;
		this->Read(outBuff, buffSize, host);
	}
	void Udp::Read(char* outBuff, int buffSize, std::string & remoteHost)
	{
		struct sockaddr_in si_other;

		//LOG_DEBUG("Waiting for data...", 0);
	    fflush(stdout);

		unsigned int slen = sizeof(sockaddr_in);
		//char cache[PACKAGESIZE] = {0};


	    //try to receive some data, this is a blocking call

		if ((recvfrom(s, outBuff, buffSize, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			log::error << "recvfrom2" << std::endl;
			return;
		}
		remoteHost = std::string(inet_ntoa(si_other.sin_addr));

	    //print details of the client/peer and the data received
		log::debug << "Received udp msg: {" << outBuff << "} to {"<<inet_ntoa(si_other.sin_addr)<<":"<<ntohs(si_other.sin_port)<<"}" << std::endl;
	}

	void Udp::Write(const std::string & buff, const char* host, int port)
	{
		struct sockaddr_in si_other;
	    int s;
	    unsigned int slen = sizeof(sockaddr_in);

	    int buffLength = buff.size() + 1;
	    char msg[buffLength] = {0};
	    strcpy(msg, buff.c_str());

	    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	    {
			log::error << "Creating socket" << std::endl;
			exit(-1);
	    }

	    memset((char *) &si_other, 0, sizeof(si_other));
	    si_other.sin_family = AF_INET;
	    si_other.sin_port = htons(port);

	    if (inet_aton(host , &si_other.sin_addr) == 0) 
	    {
			log::error << "inet_aton() failed" << std::endl;
	        exit(-1);
	    }

	    log::debug << "Sending udp msg: {" << msg << "} to {"<<host<<":"<<port<<"}" << std::endl;

	    //send the message
	    if (sendto(s, msg, buffLength , 0 , (struct sockaddr *) &si_other, slen)==-1)
	    {
			log::error << "sendto() Error while sending udp msg: {" << msg << "} to {"<<host<<":"<<port<<"}" << std::endl;
			exit(-1);
	    }

	    close(s);
	}


	void Udp::Write(const char * buff, int buffsize, const char* host, int port)
	{
		struct sockaddr_in si_other;
	    int s;
	    unsigned int slen = sizeof(sockaddr_in);

	    //int buffLength = buff.size() + 1;
	    //char msg[buffsize] = {0};
	    //strcpy(msg, buff.c_str());

	    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	    {
			log::error << "Creating socket" << std::endl;
			exit(-1);
	    }

	    memset((char *) &si_other, 0, sizeof(si_other));
	    si_other.sin_family = AF_INET;
	    si_other.sin_port = htons(port);

	    if (inet_aton(host , &si_other.sin_addr) == 0) 
	    {
			log::error << "inet_aton() failed" << std::endl;
	        exit(-1);
	    }

	    log::debug << "Sending udp msg: {" << buff << "} to {"<<host<<":"<<port<<"}" << std::endl;

	    //send the message
	    if (sendto(s, buff, buffsize , 0 , (struct sockaddr *) &si_other, slen)==-1)
	    {
			log::error << "sendto() Error while sending udp msg: {" << buff << "} to {"<<host<<":"<<port<<"}" << std::endl;
			exit(-1);
	    }

	    close(s);
	}

	int Udp::GetPort()
	{
		return port;
	}

}