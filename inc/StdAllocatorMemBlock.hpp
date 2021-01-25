#ifndef _H_StdAllocatorMemBlock
#define _H_StdAllocatorMemBlock
#include "MemBlockBase.hpp"
#include <climits>
#include <cstdlib>

namespace bfu
{
	class StdAllocatorMemBlock: public MemBlockBase
	{
		static size_t 	m_allocatedMemory;
		static size_t 	m_deallocatedMemory;
	public:
		StdAllocatorMemBlock(const char* name = "StdAllocatorMemBlock")
			:MemBlockBase(name)
		{};

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
	    {
	    	m_allocatedMemory += sizeOf * elements;

	        void* ret = aligned_alloc(alignOf, sizeOf * elements);

	    
	   		logAlloc(	ret, 
	    			sizeOf * elements, 
	    			m_memBlockDescriptor,
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
	    			m_memBlockDescriptor,
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
		    static operatorNEWstatistics mock;
		    return mock.getFreeMemory();
	    };
		virtual size_t getUsedMemory() 
		{
			return m_allocatedMemory;
		}
		virtual void* getRefPtr()
		{
			return 0;
		}

		static StdAllocatorMemBlock* GetMemBlock()
		{
			static StdAllocatorMemBlock _this;
			return &_this;
		}
	};
}

#endif