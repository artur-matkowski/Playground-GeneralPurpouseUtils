#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


#include "tests/streamTests.hpp"
#include "tests/loggingTests.hpp"

using namespace std;

using namespace bfu;

int main(int argc, char** argv)
{
	streamTests();
	loggingTests();


	//


	
	
	//cout << "\nProject Name: " << getenv("PROJECT_NAME") << std::endl;

/*
	bfu::stream str;

	str << "dadf adfads df asdf fsg sdfg sdfgs dfg dafsadf sfsf sfd sd sdf s s";
	//str << "kupa kupa kupa";



	std::cout << str << true << false << std::flush;
*/


	return 0;
}



