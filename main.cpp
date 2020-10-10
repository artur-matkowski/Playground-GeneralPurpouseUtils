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
	if( arc < 2 )
	{
		cout << "\nUsage:";
		cout << "\n\t" << argv[0] << " [1] [2]";
		cout << "\n\t[1]:";
		cout << "\n\t\t- json    - runs json tests";
		cout << "\n\t\t- strema  - runs stream rests";
		cout << "\n\t\t- logging - runs logging tests";
		cout << "\n\t\t- udp     - runs udp tests";
		cout << "\n\t\t- event   - event tests";

		return -1;
	}

	if( strcmp(argv, "json") == 0 )
	{
		bool ret = jsonTests();

		if(ret)
			return 0;
		else
			return -1;
	}

	//log::Log.EnableFileLogging();
	//streamTests();
	//loggingTests();

	
	jsonTests();
	//udpTests(argc, argv);

	//EventTest(argc, argv);
	
	
	//cout << "\nProject Name: " << getenv("PROJECT_NAME") << std::endl;


	cout << "\nUsage:";
	cout << "\n\t" << argv[0] << " [1] [2]";
	cout << "\n\t[1]:";
	cout << "\n\t\t- json    - runs json tests";
	cout << "\n\t\t- strema  - runs stream rests";
	cout << "\n\t\t- logging - runs logging tests";
	cout << "\n\t\t- udp     - runs udp tests";
	cout << "\n\t\t- event   - event tests";
	return -1;
}



