#ifndef _H_streamTests
#define _H_streamTests
#include "stream.hpp"
#include "testsbase.hpp"

#define OUT(T,v) #T":\t " << (v<0?" ":"  ") << (T)v

bool streamTests( bfu::MemBlockBase* mBlock )
{
	bfu::MonotonicMemBlock<1024*1024> memBlock;

	bool result = true;
    	char  m_buff[1024] = {'0'};

	std::cout << "TESTING bfu::stream VISUALLY" << std::endl << std::flush;

	bfu::stream str(m_buff, 1024, &memBlock);

	str << OUT(float, -2.321) << std::endl;
	str << OUT(float, 2.321) << std::endl;

	str << OUT(int, -2) << std::endl;
	str << OUT(int, 3) << std::endl;


	str << OUT(uint64_t, 87394827) << std::endl;
	str << OUT(uint64_t, 3) << std::endl;

	str << OUT(int8_t, -2) << std::endl;
	str << OUT(int8_t, 3) << std::endl;

	str << OUT(bool, true) << std::endl;
	str << OUT(bool, false) << std::endl;

	str << LOREM_IPSUM << std::endl;

	std::cout << str << std::endl << std::flush;
	std::cout << "\tCan you see properly float, int, bool, and lorem ipsum text?\n\n";
	//std::cin >> result;

	return result;
}


#endif