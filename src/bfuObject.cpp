#include "bfuObject.hpp"
#include <iostream>
#include <cstdlib> 
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>


int alocations = 0;
int dealocations = 0;



void * operator new(std::size_t size)
{ 
	++alocations;
    void * p = malloc(size); 
    std::cout << "\nMemory alocations:   " << alocations << "<" <<
    		     "\nMemory dealocations: " << dealocations <<
    		     "\nMemory addr: " << p << " " << size << "b" << std::endl;
    		     //"\nAlocation called from: " << file << ":" << line << std::endl; 
    std::cout.flush();
    return p; 
} 
  
void operator delete(void * p) noexcept
{ 
	++dealocations;
    std::cout << "\nMemory alocations:   " << alocations << 
    		     "\nMemory dealocations: " << dealocations << "<" <<
    		     "\nMemory addr: " << p <<  std::endl;
    		     //"\nAlocation called from: " << file << ":" << line << std::endl; 
    std::cout.flush();
    free(p); 
}
