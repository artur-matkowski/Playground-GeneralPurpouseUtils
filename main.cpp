#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>

#include <fstream>
#include <unistd.h>

#include "tests/streamTests.hpp"
#include "tests/loggingTests.hpp"
#include "tests/udpTests.hpp"
#include "tests/EventTest.hpp"
#include "tests/JSONObjectSerializable_tests.hpp"
#include "tests/BINObjectSerializable_tests.hpp"

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

	// template<class T>
	// class A: public bfu::SerializableClassBase<A<T>>
	// {
	// public:
	// 	SERIALIZABLE_VAR(A<T>, int, i);


	// public:
	// 	A()
	// 	{};
	// 	~A(){};
	// };


	// class B: public bfu::SerializableClassBase<B>
	// {
	// public:
	// 	SERIALIZABLE_VAR(B, int, i);


	// public:
	// 	B()
	// 	{};
	// 	~B(){};
	// };

int main(int argc, char** argv)
{
	//MonotonicMemBlock<1024*1024*50> membloc("main memory block");
	StdAllocatorMemBlock membloc("STD memory block");
	//log::file();


	if( argc < 2 )
	{
		cout << "\nUsage:";
		cout << "\n\t" << argv[0] << " [1] [2]";
		cout << "\n\t[1]:";
		cout << "\n\t\t- stream  - runs stream rests";
		cout << "\n\t\t- logging - runs logging tests";
		cout << "\n\t\t- udp     - runs udp tests";
		cout << "\n\t\t- event   - event tests";
		cout << "\n\t\t- serialj - new serialization methods (JSON)";
		cout << "\n\t\t- serialb - new serialization methods (BINARY)\n";

		return -1;
	}

	if( strcmp(argv[1], "stream") == 0 )
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
	else if( strcmp(argv[1], "serialj") == 0 )
	{
		bool ret = JSONObjectSerializationTests::ObjectSerializableTests(&membloc);

		if(ret)
			return 0;
		else
			return -1;
	}
	else if( strcmp(argv[1], "serialb") == 0 )
	{
		bool ret = BINObjectSerializationTests::ObjectSerializableTests(&membloc);

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
	cout << "\n\t\t- stream  - runs stream rests";
	cout << "\n\t\t- logging - runs logging tests";
	cout << "\n\t\t- udp     - runs udp tests";
	cout << "\n\t\t- event   - event tests";
	cout << "\n\t\t- serialj - new serialization methods (JSON)";
	cout << "\n\t\t- serialb - new serialization methods (BINARY)\n";
	return -1;
}



