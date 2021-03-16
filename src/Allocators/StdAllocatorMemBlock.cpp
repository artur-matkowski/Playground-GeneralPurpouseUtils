#include "StdAllocatorMemBlock.hpp"


namespace bfu
{

	size_t 	StdAllocatorMemBlock::s_allocatedMemory = 0;
	size_t 	StdAllocatorMemBlock::s_deallocatedMemory = 0;
	int 	StdAllocatorMemBlock::s_allocationCount = 0;
	int 	StdAllocatorMemBlock::s_deallocationCount = 0;
}

void * operator new(std::size_t size)
{ 
    return bfu::StdAllocatorMemBlock::GetMemBlock()->allocate(1, size, 0);
} 
  
void operator delete(void * p) noexcept
{
    bfu::StdAllocatorMemBlock::GetMemBlock()->deallocate(p, 0);
}



