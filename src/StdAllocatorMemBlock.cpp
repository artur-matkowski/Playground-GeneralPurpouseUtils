#include "StdAllocatorMemBlock.hpp"


namespace bfu
{
	size_t 	StdAllocatorMemBlock::s_allocatedMemory = 0;
	size_t 	StdAllocatorMemBlock::s_deallocatedMemory = 0;
	int 	StdAllocatorMemBlock::s_allocationCount = 0;
	int 	StdAllocatorMemBlock::s_deallocationCount = 0;
}