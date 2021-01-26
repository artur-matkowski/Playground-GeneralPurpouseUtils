#ifndef _H_StdAllocatorMemBlock
#define _H_StdAllocatorMemBlock
#include "MemBlockBase.hpp"
#include <climits>
#include <cstdlib>

namespace bfu
{
	class StdAllocatorMemBlock: public MemBlockBase
	{
		static size_t 	s_allocatedMemory;
		static size_t 	s_deallocatedMemory;
		static int 		s_allocationCount;
		static int 		s_deallocationCount;
	public:
		StdAllocatorMemBlock(const char* name = "StdAllocatorMemBlock")
			:MemBlockBase(name)
		{};

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
	    {
	    	s_allocatedMemory += sizeOf * elements;

	        void* ret = aligned_alloc(alignOf, sizeOf * elements);

	    
	   		logAlloc(	ret, 
	    			sizeOf * elements, 
	    			m_memBlockDescriptor,
	    			getUsedMemory(),
	    			getFreeMemory(),
	    			s_deallocatedMemory,
	    			++s_allocationCount,
	    			s_deallocationCount,
	    			this);


	        return ret;
	    }

		virtual void deallocate (void* p, std::size_t n)
	    {
	    	s_deallocatedMemory += n;

	   		logDealloc(	p, 
	    			n, 
	    			m_memBlockDescriptor,
	    			getUsedMemory(),
	    			getFreeMemory(),
	    			s_deallocatedMemory,
	    			s_allocationCount,
	    			++s_deallocationCount,
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
			return s_allocatedMemory;
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