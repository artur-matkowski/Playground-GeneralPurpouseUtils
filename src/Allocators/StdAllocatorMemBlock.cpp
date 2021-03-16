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
    // if(s_mBlock!=0)
    // 	return s_mBlock->allocate(1, size, 0);
    // else 
    // 	return s_mMalloc.allocate(1, size, 0);
    return bfu::StdAllocatorMemBlock::GetMemBlock()->allocate(1, size, 0);
} 
  
void operator delete(void * p) noexcept
{ 
    // if(s_mBlock!=0 && s_mBlock->owns(p) )
    // 	return s_mBlock->deallocate(p, 0);
    // else 
    // 	return s_mMalloc.deallocate(p, 0);
    bfu::StdAllocatorMemBlock::GetMemBlock()->deallocate(p, 0);
}



