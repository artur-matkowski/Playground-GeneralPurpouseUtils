#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


#include "tests/streamTests.hpp"
#include "tests/loggingTests.hpp"
#include "tests/udpTests.hpp"
#include "tests/jsonTests.hpp"
#include "tests/EventTest.hpp"

using namespace std;

using namespace bfu;

int main(int argc, char** argv)
{
	//log::Log.EnableFileLogging();
	//streamTests();
	//loggingTests();

	jsonTests();
	//udpTests(argc, argv);

	//EventTest(argc, argv);
	
	
	//cout << "\nProject Name: " << getenv("PROJECT_NAME") << std::endl;



	return 0;
}



