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

bool udpTests(int argc, char** argv)
{

	bfu::udp::packet out;
	bfu::udp::packet msg;

	out.SetHost("127.0.0.1");
	out.m_port = 8888;
	out.m_id.GetRef() << TEST_STRING;

	if(argc>1 && strcmp(argv[1], "sender") == 0 )
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));


		bfu::udp udp(8889);
		udp.Write( out );
		udp.Write( out );

	}
	else
	{
		
		int result = fork();
		
		if(result==0)
		{
			char cmd[128] = {0};
			sprintf(cmd, "xterm -e \"%s sender\"", argv[0]);
			system(cmd);
			exit(0);
		}
		else
		{
			bfu::udp udp(8888);

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			bool readed;

			do
			{
				readed = udp.Read( msg, false);
				printf( "gowno test:%s\n", msg.m_id.GetRef().c_str() );
			}while(readed);
		}
	}

	if( std::strcmp(TEST_STRING, msg.m_id.GetRef().c_str() )==0 )
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