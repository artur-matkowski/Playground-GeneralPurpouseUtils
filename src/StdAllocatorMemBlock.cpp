#include "StdAllocatorMemBlock.hpp"
#include <climits>
#include "log.hpp"

namespace bfu
{
    void* StdAllocatorMemBlock::allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
    {
    	m_allocatedMemory += sizeOf * elements;

        void* ret = aligned_alloc(alignOf, sizeOf * elements);

    
   		logAlloc(	ret, 
    			sizeOf * elements, 
    			"StdAllocatorMemBlock",
    			getUsedMemory(),
    			getFreeMemory(),
    			m_deallocatedMemory,
    			++m_allocationCount,
    			m_deallocationCount,
    			this);


        return ret;
    }
    void StdAllocatorMemBlock::deallocate (void* p, std::size_t n)
    {
    	m_deallocatedMemory += n;


   		logDealloc(	p, 
    			n, 
    			"StdAllocatorMemBlock",
    			getUsedMemory(),
    			getFreeMemory(),
    			m_deallocatedMemory,
    			m_allocationCount,
    			++m_deallocationCount,
    			this);


        free(p);
    };
    size_t StdAllocatorMemBlock::getFreeMemory()
    {
        return 0;
    };
	size_t StdAllocatorMemBlock::getUsedMemory() 
	{
		return m_allocatedMemory;
	}
	void* StdAllocatorMemBlock::getRefPtr()
	{
		return this;
	}
}