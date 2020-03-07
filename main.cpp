#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "LOG.hpp"

#include "Log.hpp"

#include "stream.hpp"

using namespace std;



int main(int argc, char** argv)
{
	/*
	LOG_DEBUG("slaby blad : %s ", "asdfaf");
	LOG_INFO("slaby blad : %s ", "asdfaf");
	LOG_WARNING("slaby blad : %s ", "asdfaf");
	LOG_ERROR("slaby blad : %s ", "asdfaf");

	LOG_INFO("slaby blad", 1);

	Debug::Log.EnableFileLogging();
*/
	//Debug::Log << "Hello Log! " << 2 << " " << __FUNCTION__ << std::endl;
	
	
	log::error << "dasdad" << std::endl;
  	log::warning << "Hello Log! " << 2 << " " << __FUNCTION__ << std::endl;
	log::info << "Hello Log! " << 2 << " " << __FUNCTION__ << std::endl;
	log::debug << "Hello Log! " << 2 << " " << __FUNCTION__ << std::endl;

    log::debug << "Hello Log! " << 0xFA << std::endl; // NB: this way the debugLevel is default

	cout << "\nProject Name: " << getenv("PROJECT_NAME") << flush;


	bfu::stream str;

	str.resize();

	str.sprintf("kupa kupa kupa");


	std::cout << str.str();



	return 0;
}



