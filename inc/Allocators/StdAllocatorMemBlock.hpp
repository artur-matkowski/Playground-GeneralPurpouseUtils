#ifndef _H_StdAllocatorMemBlock
#define _H_StdAllocatorMemBlock
#include "Allocators/MemBlockBase.hpp"
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
		StdAllocatorMemBlock(const char* name = "Std Allocator MemBlock")
			:MemBlockBase( name )
		{};

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
	    {
	    	size_t size = sizeOf * elements + sizeof(MemChunkHeader);
	    	s_allocatedMemory += size;

	        void* ret = aligned_alloc( alignOf, size );
			//std::memset(ret, 0, size);

	        MemChunkHeader* headerInfo = (MemChunkHeader*)ret;

	        headerInfo->m_MemBlockOwner = this;
	        headerInfo->m_sizeOfChunk = size;

	        ++s_allocationCount;
	    	#ifdef DEBUG_MEMORY_ALLOC
	   		logAlloc(	ret, 
	    			size, 
	    			m_memBlockDescriptor,
	    			getUsedMemory(),
	    			getFreeMemory(),
	    			s_deallocatedMemory,
	    			s_allocationCount,
	    			s_deallocationCount,
	    			this);
	   		#endif

	        return (void*) ((size_t)ret + sizeof(MemChunkHeader));
	    }

		virtual void deallocate (void* p, std::size_t n)
	    {
	    	if( p==nullptr )
	    		return;
	    	
	        MemChunkHeader* headerInfo = MemChunkHeader::InitFromLifePtr(p);
	    	s_deallocatedMemory += headerInfo->m_sizeOfChunk;
	    	++s_deallocationCount;

			#ifdef DEBUG_MEMORY_ALLOC
	   		logDealloc(	p, 
	    			headerInfo->m_sizeOfChunk, 
	    			m_memBlockDescriptor,
	    			getUsedMemory(),
	    			getFreeMemory(),
	    			s_deallocatedMemory,
	    			s_allocationCount,
	    			s_deallocationCount,
	    			this);
	   		#endif
		

	        free(headerInfo);
	    };
		virtual size_t getFreeMemory()
	    {
		    return 0;
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

void* operator new(std::size_t size);
void operator delete(void* p) noexcept;
#endif