#include "bfuObject.hpp"
#include <iostream>
#include <cstdlib> 
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>


void* operator new(size_t size)
{
	void* ptr = std::malloc(size);

	/*
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    std::cout.width( w.ws_col -64);

	std::cout << std::right << "alocated " << size << " bytes of memory in " << ptr << "\n" << std::flush;
*/
	return ptr;
}


void operator delete(void* where) noexcept
{
	//std::cout << "released " << where << " memory chunk\n" << std::flush;

	std::free(where);
}
