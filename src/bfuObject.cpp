#include "bfuObject.hpp"
#include <iostream>
#include <cstdlib> 
#include "Log.hpp"


void* operator new(size_t size)
{
	void* ptr = std::malloc(size);
	std::cout << "alocated " << size << " bytes of memory in " << ptr << "\n" << std::flush;

	return ptr;
}


void operator delete(void* where) noexcept
{
	//std::cout << "released " << where << " memory chunk\n" << std::flush;

	std::free(where);
}
