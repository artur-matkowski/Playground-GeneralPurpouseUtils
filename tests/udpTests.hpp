#ifndef _H_udpTests
#define _H_udpTests
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

#include <thread>
#include <chrono>

#include "udp.hpp"
#include "testsbase.hpp"

#define TEST_STRING "{kupa \"msg type\"}"

bool udpTests( bfu::MemBlockBase* mBlock )
{
	char hostBuff[16];
	char recvBuff[128] = {0};

	int result = fork();

	if( result == 0 ) //parent
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));


		//bfu::udp _udp(8889);

		bfu::udp::Write(TEST_STRING, strlen(TEST_STRING), "127.0.0.1", 8888);

		return false; // irrelevent
	}
	else //child
	{
		bfu::udp udp(8888);

		bool readed;

		do
		{
			readed = udp.Read( recvBuff, 128, hostBuff, 16, false) > 0;
		}while(!readed);
	}

	if( std::strcmp(TEST_STRING, recvBuff )==0 )
	{
		log::warning << "<<<<<<<<<<<<<<<< Test concluded : SUCCES\n" << std::endl;
		return true;
	}
	else
	{
		log::error << "<<<<<<<<<<<<<<<< Test concluded : FAILED\n" << std::endl;
		return false;		
	}
}

#endif