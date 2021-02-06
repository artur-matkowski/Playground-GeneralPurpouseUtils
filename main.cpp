#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <fstream>
#include <unistd.h>

#include "tests/streamTests.hpp"
#include "tests/loggingTests.hpp"
#include "tests/udpTests.hpp"
#include "tests/jsonTests.hpp"
#include "tests/EventTest.hpp"

using namespace std;

using namespace bfu;


void process_mem_usage(double& vm_usage, double& resident_set)
{
    vm_usage     = 0.0;
    resident_set = 0.0;

    // the two fields we want
    unsigned long vsize;
    long rss;
    {
        bfu::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}




int main(int argc, char** argv)
{
	//MonotonicMemBlock<1024*1024*50> membloc("main memory block");
	MmappedMemBlock membloc((void*)1, 1024*1024*50, "main memory block");
	//log::file();


	if( argc < 2 )
	{
		cout << "\nUsage:";
		cout << "\n\t" << argv[0] << " [1] [2]";
		cout << "\n\t[1]:";
		cout << "\n\t\t- json    - runs json tests";
		cout << "\n\t\t- stream  - runs stream rests";
		cout << "\n\t\t- logging - runs logging tests";
		cout << "\n\t\t- udp     - runs udp tests";
		cout << "\n\t\t- event   - event tests\n";

		return -1;
	}

	if( strcmp(argv[1], "json") == 0 )
	{
		bool ret = jsonTests(&membloc);

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "stream") == 0 )
	{
		bool ret = streamTests(&membloc);

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "logging") == 0 )
	{
		bool ret = loggingTests(&membloc);

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "udp") == 0 )
	{
		bool ret = udpTests(&membloc);

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "event") == 0 )
	{
		bool ret = EventTest(&membloc);

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



