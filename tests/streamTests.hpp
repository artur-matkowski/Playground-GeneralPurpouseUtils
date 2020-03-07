#ifndef _H_streamTests
#define _H_streamTests
#include "stream.hpp"
#include "testsbase.hpp"

#define OUT(T,v) #T":\t " << (v<0?" ":"  ") << (T)v

bool streamTests()
{
	bool result = true;

	std::cout << "TESTING bfu::stream VISUALLY" << std::endl << std::flush;

	bfu::stream str;

	str << OUT(float, -2.321) << std::endl;
	str << OUT(float, 2.321) << std::endl;

	str << OUT(int, -2) << std::endl;
	str << OUT(int, 3) << std::endl;


	str << OUT(bool, true) << std::endl;
	str << OUT(bool, false) << std::endl;

	str << LOREM_IPSUM << std::endl;

	std::cout << str << std::endl << std::flush;
	std::cout << "\tCan you see properly float, int, bool, and lorem ipsum text?\n\n";
	//std::cin >> result;

	return result;
}


#endif