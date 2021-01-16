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


class Prealocator10mb: public MonotonicAllocator<1024*1024*10>{};

int main(int argc, char** argv)
{
	/*
	//vector<float, custom_allocator<float, Prealocator10mb >> v_floats;
	vector<float> v_floats;
	float f = 1.0;
	v_floats.push_back(++f);
	v_floats.push_back(++f);
	v_floats.push_back(++f);
	v_floats.push_back(++f);


	for(int i=0; i<v_floats.size(); ++i)
		cout << v_floats[i] << " ";
*/


	if( argc < 2 )
	{
		cout << "\nUsage:";
		cout << "\n\t" << argv[0] << " [1] [2]";
		cout << "\n\t[1]:";
		cout << "\n\t\t- json    - runs json tests";
		cout << "\n\t\t- stream  - runs stream rests";
		cout << "\n\t\t- logging - runs logging tests";
		cout << "\n\t\t- udp     - runs udp tests";
		cout << "\n\t\t- event   - event tests";

		return -1;
	}

	if( strcmp(argv[1], "json") == 0 )
	{
		bool ret = jsonTests();

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "stream") == 0 )
	{
		bool ret = streamTests();

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "logging") == 0 )
	{
		bool ret = loggingTests();

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "udp") == 0 )
	{
		bool ret = udpTests();

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "event") == 0 )
	{
		bool ret = EventTest();

		if(ret)
			return 0;
		else
			return -1;
	}

	//log::Log.EnableFileLogging();
	//streamTests();
	//loggingTests();

	
	//jsonTests();
	//udpTests(argc, argv);

	//EventTest(argc, argv);
	
	
	//cout << "\nProject Name: " << getenv("PROJECT_NAME") << std::endl;


	cout << "\nUsage:";
	cout << "\n\t" << argv[0] << " [1] [2]";
	cout << "\n\t[1]:";
	cout << "\n\t\t- json    - runs json tests";
	cout << "\n\t\t- stream  - runs stream rests";
	cout << "\n\t\t- logging - runs logging tests";
	cout << "\n\t\t- udp     - runs udp tests";
	cout << "\n\t\t- event   - event tests";
	return -1;
}



