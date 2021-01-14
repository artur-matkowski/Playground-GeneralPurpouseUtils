#include "udp.hpp"
#include <log.hpp>
#include <algorithm>
#include <poll.h>



namespace bfu{

	udp::udp(int Port)
		:m_port(Port)
		,m_json()
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


	bool udp::Read(packet &out, bool isBlocking)
	{
		if( m_socket == -1 )
		{
			return false;
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
	        	return false;
	        }	    	
	    }

	    m_json.clear();
	    out.clear();


	    int recvsize = recvfrom(m_socket, m_json.c_str(), PACKAGESIZE, 0, (struct sockaddr *) &si_other, &slen);

		if (recvsize < 0)
		{
			log::error << "recvfrom " << recvsize << std::endl;
			return false;
		}
		
		m_json.OverrideWriteCursorPos(recvsize);
		//print details of the client/peer and the data received
		log::debug << "Received udp json: >\n" << m_json.c_str() << "\n< from {"<< out.m_host <<":"<< out.m_port <<"}" << std::endl;


		m_json >> out;

		char* tmp = inet_ntoa(si_other.sin_addr);

		std::strncpy(out.m_host, tmp, HOSTSIZE);
		out.m_port = ntohs(si_other.sin_port);

	    
		return true;
	}

	bool udp::Write( packet &in )
	{
	    int s;

	    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	    {
			log::error << "Creating socket" << std::endl;
			return false;
	    }

	    memset((char *) &si_other, 0, sizeof(si_other));
	    si_other.sin_family = AF_INET;
	    si_other.sin_port = htons(in.m_port);

	    if (inet_aton(in.m_host , &si_other.sin_addr) == 0) 
	    {
			log::error << "inet_aton() failed" << std::endl;
			return false;
	    }

	    m_json.clear();
	    m_json << in;

	    log::debug << "Sending udp json: >\n" << m_json.c_str() << "\n< to {"<< in.m_host <<":"<< in.m_port <<"}" << std::endl;

	    //send the message
	    if (sendto(s, m_json.c_str(), m_json.size() , 0 , (struct sockaddr *) &si_other, slen)==-1)
	    {
			log::error << "sendto() Error while sending udp json: >\n" << m_json.c_str() << "\n< to {"<< in.m_host <<":"<< in.m_port <<"}" << std::endl;
			return false;
	    }

	    close(s);

	    return true;
	}
	
	bool udp::Write( SerializableClassBase &in, const char* eventId, const char* host, int port)
	{
		m_cache.clear();
		m_cache.m_id.GetRef() << eventId;
		m_cache.m_data.GetRef() << in;

		int s;

	    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	    {
			log::error << "Creating socket" << std::endl;
			return false;
	    }

	    memset((char *) &si_other, 0, sizeof(si_other));
	    si_other.sin_family = AF_INET;
	    si_other.sin_port = htons( port );

	    if (inet_aton( host, &si_other.sin_addr) == 0) 
	    {
			log::error << "inet_aton() failed" << std::endl;
			return false;
	    }

	    m_json.clear();
	    m_json << m_cache;

	    log::debug << "Sending udp json: >\n" << m_json.c_str() << "\n< to {"<< host <<":"<< port <<"}" << std::endl;

	    //send the message
	    if (sendto(s, m_json.c_str(), m_json.size() , 0 , (struct sockaddr *) &si_other, slen)==-1)
	    {
			log::error << "sendto() Error while sending udp json: >\n" << m_json.c_str() << "\n< to {"<< host <<":"<< port <<"}" << std::endl;
			return false;
	    }

	    close(s);

	    return true;
	}


	std::string udp::Read(std::string & remoteHost)
	{
		char cache[PACKAGESIZE] = {0};


	    //try to receive some data, this is a blocking call

		if ((recvfrom(m_socket, cache, PACKAGESIZE, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			log::error << "recvfrom2" << std::endl;
			return "";
		}
		remoteHost = std::string(inet_ntoa(si_other.sin_addr));

	    //print details of the client/peer and the data received
		log::debug << "Received udp msg: {" << cache << "} to {"<<inet_ntoa(si_other.sin_addr)<<":"<<ntohs(si_other.sin_port)<<"}" << std::endl;

		return std::string(cache);
	}

	void udp::Read(char* outBuff, int buffSize)
	{
		std::string host;
		this->Read(outBuff, buffSize, host);
	}
	void udp::Read(char* outBuff, int buffSize, std::string & remoteHost)
	{
		struct sockaddr_in si_other;

		//LOG_DEBUG("Waiting for data...", 0);
	    fflush(stdout);

		unsigned int slen = sizeof(sockaddr_in);
		//char cache[PACKAGESIZE] = {0};


	    //try to receive some data, this is a blocking call

		if ((recvfrom(m_socket, outBuff, buffSize, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			log::error << "recvfrom2" << std::endl;
			return;
		}
		remoteHost = std::string(inet_ntoa(si_other.sin_addr));

	    //print details of the client/peer and the data received
		log::debug << "Received udp msg: {" << outBuff << "} to {"<<inet_ntoa(si_other.sin_addr)<<":"<<ntohs(si_other.sin_port)<<"}" << std::endl;
	}

	void udp::Write(const std::string & buff, const char* host, int port)
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