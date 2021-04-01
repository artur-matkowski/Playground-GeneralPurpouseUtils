#include "udp.hpp"
#include <log.hpp>
#include <algorithm>
#include <poll.h>



namespace bfu{

	udp::udp(int Port)
	{
		if(Port>0)
		{
			StartListening(Port);
		}
	}
	udp::~udp()
	{
		if( m_socket!=-1 )
	    	close( m_socket );
	}

	bool udp::StartListening(int port)
	{
		m_port = port;

		if ((m_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		{
			log::error << "Creating socket" << std::endl;
			return false;
		}

		// zero out the structure
		memset((char *) &si_me, 0, sizeof(si_me));

		si_me.sin_family = AF_INET;
		si_me.sin_port = htons(m_port);
		si_me.sin_addr.s_addr = htonl(INADDR_ANY);

		//bind socket to port
		if( bind(m_socket , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
		{
			log::error << "Binding socket" << std::endl;
			return false;
		}
		log::info << "Listening for udp on port " << m_port << std::endl;

		return true;
	}

	void udp::StopListening()
	{
	    close( m_socket );
	    m_socket = -1;
	}

	int udp::Read(char* outBuff, int buffSize, char* remoteHost, int hostBuffSize, bool isBlocking )
	{
		if( m_socket == -1 )
		{
			return -1;
		}
	    else if(!isBlocking)
	    {
		    struct pollfd pollStruct;
		    pollStruct.fd = m_socket;
	        pollStruct.events = POLLIN;
	        pollStruct.revents = 0;

	        int rv = poll( &pollStruct, 1, 0 ); 

	        if(rv<1)
	        {
	        	return 0;
	        }	    	
	    }

		struct sockaddr_in si_other;


		unsigned int slen = sizeof(sockaddr_in);

	    //try to receive some data, this is a blocking call
		if ((recvfrom(m_socket, outBuff, buffSize, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			log::error << "recvfrom" << std::endl;
			return -2;
		}
		strncpy(remoteHost, inet_ntoa(si_other.sin_addr), hostBuffSize);

	    //print details of the client/peer and the data received
		log::debug << "Received udp msg: {" << outBuff << "} from {"<<inet_ntoa(si_other.sin_addr)<<":"<<ntohs(si_other.sin_port)<<"}" << std::endl;
	
		return 1;
	}

	void udp::Write(const char * buff, int buffsize, const char* host, int port)
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

	int udp::GetPort()
	{
		return m_port;
	}

}