#ifndef _H_StdAllocatorMemBlock
#define _H_StdAllocatorMemBlock
#include "MemBlockBase.hpp"
#include <climits>
#include <cstdlib>

namespace bfu
{
	class StdAllocatorMemBlock: public MemBlockBase
	{
		size_t 	m_allocatedMemory = 0;
		size_t 	m_deallocatedMemory = 0;
	public:
		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
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

		virtual void deallocate (void* p, std::size_t n)
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
		virtual size_t getFreeMemory()
	    {
	        return 0;
	    };
		virtual size_t getUsedMemory() 
		{
			return m_allocatedMemory;
		}
		virtual void* getRefPtr()
		{
			return this;
		}

		static StdAllocatorMemBlock* GetMemBlock()
		{
			static StdAllocatorMemBlock _this;
			return &_this;
		}
	};
}

#endif