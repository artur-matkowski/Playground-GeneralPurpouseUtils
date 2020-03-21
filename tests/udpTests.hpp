#ifndef _H_udpTests
#define _H_udpTests
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

#include <thread>
#include <chrono>

#include "udp.hpp"
#include "testsbase.hpp"


void udpTests(int argc, char** argv)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
/*
	if (resoult == 0) 
	{
		bfu::udp udp(8888);
		std::string host;
		printf(udp.Read(host).c_str());
		printf(udp.Read(host).c_str());
	}
    else
    {
		bfu::udp::Write(LOREM_IPSUM, "127.0.0.1", 8888);
		bfu::udp::Write(LOREM_IPSUM, "127.0.0.1", 8888);
	}
*/
	if(argc>1 && strcmp(argv[1], "sender") == 0 )
	{
		bfu::udp::packet msg;
		msg.SetHost("127.0.0.1");
		msg.m_port = 8888;
		msg.m_id.GetRef() << "kupa msg type";

		bfu::udp udp(8889);
		udp.Write( msg );

		while(1);

	}
	else
	{
		/*
		int result = fork();
		
		if(result==0)
		{
			char cmd[128] = {0};
			sprintf(cmd, "xterm -e \"%s sender\"", argv[0]);
			system(cmd);
		}
		else*/
		{
			bfu::udp::packet msg;

			bfu::udp udp(8888);
			std::string host;

			udp.Read( msg, true);

			printf( "%s\n", msg.m_id.GetRef().c_str() );			
		}


	}
}

#endif