#ifndef _H_udpTests
#define _H_udpTests
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

#include <thread>
#include <chrono>

#include "udp.hpp"
#include "testsbase.hpp"


void udpTests()
{
	int resoult = fork();

	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	if (resoult == 0) 
	{
		bfu::Udp udp(8888);
		printf(udp.Read().c_str());
		printf(udp.Read().c_str());
	}
    else
    {
		bfu::Udp::Write(LOREM_IPSUM, "127.0.0.1", 8888);
		bfu::Udp::Write(LOREM_IPSUM, "127.0.0.1", 8888);
	}


}

#endif