#include "bfuObject.hpp"
#include <iostream>
#include <cstdlib> 
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "log.hpp"

int alocations = 0;
int dealocations = 0;



void * operator new(std::size_t size)
{ 
	++alocations;
    void * p = malloc(size); 
    //std::cout << "\033[1;31m";
    log::warning << "\n\t\tMemory alocations:   " << alocations << " caling global operator NEW" <<
    		     "\n\t\tMemory dealocations: " << dealocations <<
    		     "\n\t\tMemory addr: " << (size_t)p << " " << size << "b\n" << std::endl;
    return p; 
} 
  
void operator delete(void * p) noexcept
{ 
	++dealocations;
    log::warning << "\n\t\tMemory alocations:   " << alocations << 
    		     "\n\t\tMemory dealocations: " << dealocations << " caling global operator DELETE" <<
    		     "\n\t\tMemory addr: " << (size_t)p << "\n" <<  std::endl;
    free(p); 
}
