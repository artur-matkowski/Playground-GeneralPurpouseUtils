#include "bfuObject.hpp"
#include <iostream>
#include <cstdlib> 
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "log.hpp"
#include <climits>

int alocations = 0;
size_t alocatedBytes = 0;
int dealocations = 0;


namespace bfu
{
    void convert(size_t& big, size_t& small)
    {
        big = small / 1024;
        small = small % 1024;
    }

    void convert(size_t& gb, size_t& mb, size_t& kb, size_t& b)
    {
        convert(kb, b);
        convert(mb, kb);
        convert(gb, mb);
    }



    void* StdAllocatorMemBlock::allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
    {
        alocatedBytes += sizeOf * elements;
        size_t bytes = alocatedBytes;
        size_t gb = 0, mb = 0, kb = 0;
        convert(gb, mb, kb, bytes);

        ++alocations;
        alocatedBytes += sizeOf * elements;
        void* ret = aligned_alloc(alignOf, sizeOf * elements);
        log::warning << "\n\t\tMemory alocations: " << alocations << " caling global aligned_alloc()" <<
             "\n\t\tMemory dealocations: " << dealocations <<
             "\n\t\tMemory addr: " << (size_t)ret << " " << sizeOf * elements << "b\n" << 
             "\n\t\tGlobaly alocated " << (int)gb << "Gb, " << (int)mb << "Mb, " << (int)kb << "kb, " << (int)bytes << "b, " << std::endl;

        return ret;
    }
    void StdAllocatorMemBlock::deallocate (void* p, std::size_t n)
    {
        ++dealocations;
        log::warning << "\n\t\tMemory alocations:   " << alocations << 
             "\n\t\tMemory dealocations: " << dealocations << " caling global free()" <<
             "\n\t\tMemory addr: " << (size_t)p << "\n" << std::endl;
        free(p);
    };
    size_t StdAllocatorMemBlock::getFreeMemory()
    {
        return SIZE_MAX;
    };
}

void * operator new(std::size_t size)
{ 
    alocatedBytes += size;
    size_t bytes = alocatedBytes;
    size_t gb = 0, mb = 0, kb = 0;
    bfu::convert(gb, mb, kb, bytes);

	++alocations;
    alocatedBytes += size;
    void * p = malloc(size); 
    //std::cout << "\033[1;31m";
    log::warning << "\n\t\tMemory alocations:   " << alocations << " caling global operator NEW" <<
    		     "\n\t\tMemory dealocations: " << dealocations <<
    		     "\n\t\tMemory addr: " << (size_t)p << " " << size << "b\n" << "b\n" << 
             "\n\t\tGlobaly alocated " << (int)gb << "Gb, " << (int)mb << "Mb, " << (int)kb << "kb, " << (int)bytes << "b, " << std::endl;
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
