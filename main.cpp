#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Log.hpp"

#include "stream.hpp"

using namespace std;

using namespace bfu;

int main(int argc, char** argv)
{
	


	//log::Log.EnableFileLogging();


	
	
	log::error << "dasdad" << std::endl;
  	log::warning << "Hello Log! " << 2 << " " << __FUNCTION__ << std::endl;
	log::info << "Hello Log! " << 2 << " " << __FUNCTION__ << std::endl;
	log::debug << "Hello Log! " << 2 << " " << __FUNCTION__ << std::endl;

    log::debug << "Hello Log! " << 0xFA << std::endl; // NB: this way the debugLevel is default

	//cout << "\nProject Name: " << getenv("PROJECT_NAME") << std::endl;

/*
	bfu::stream str;

	str << "dadf adfads df asdf fsg sdfg sdfgs dfg dafsadf sfsf sfd sd sdf s s";
	//str << "kupa kupa kupa";



	std::cout << str << true << false << std::flush;
*/


	return 0;
}



