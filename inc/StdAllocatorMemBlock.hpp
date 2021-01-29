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

		MallocAllocator mock;
	public:
		StdAllocatorMemBlock(const char* name = "StdAllocatorMemBlock")
			:MemBlockBase(name)
		{};

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
	    {
	    	s_allocatedMemory += sizeOf * elements;

	        void* ret = aligned_alloc(alignOf, sizeOf * elements);

	        ++s_allocationCount;
	    	#ifdef DEBUG_MEMORY_ALLOC
	   		logAlloc(	ret, 
	    			sizeOf * elements, 
	    			m_memBlockDescriptor,
	    			getUsedMemory(),
	    			getFreeMemory(),
	    			s_deallocatedMemory,
	    			s_allocationCount,
	    			s_deallocationCount,
	    			this);
	   		#endif


	        return ret;
	    }

		virtual void deallocate (void* p, std::size_t n)
	    {
	    	s_deallocatedMemory += n;
	    	++s_deallocationCount;

			#ifdef DEBUG_MEMORY_ALLOC
	   		logDealloc(	p, 
	    			n, 
	    			m_memBlockDescriptor,
	    			getUsedMemory(),
	    			getFreeMemory(),
	    			s_deallocatedMemory,
	    			s_allocationCount,
	    			s_deallocationCount,
	    			this);
	   		#endif


	        free(p);
	    };
		virtual size_t getFreeMemory()
	    {
		    return mock.getFreeMemory() - s_allocatedMemory;
	    };
		virtual size_t getUsedMemory() 
		{
			return s_allocatedMemory;
		}
		virtual void* getRefPtr()
		{
			return 0;
		}
		virtual void* getMemPtr()
		{
			return nullptr;
		}
		virtual bool owns(void* ptr)
		{
			return false;
		}

		virtual int GetAllocationsCount() {return s_allocationCount;}
		virtual int GetDeallocationsCount() {return s_deallocationCount;}

		static StdAllocatorMemBlock* GetMemBlock()
		{
			static StdAllocatorMemBlock _this;
			return &_this;
		}
	};
}

#endif