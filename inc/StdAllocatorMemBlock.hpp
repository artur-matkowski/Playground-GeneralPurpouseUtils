#ifndef _H_StdAllocatorMemBlock
#define _H_StdAllocatorMemBlock
#include "MemBlockBase.hpp"

namespace bfu
{
	class StdAllocatorMemBlock: public MemBlockBase
	{
		size_t 	m_allocatedMemory = 0;
		size_t 	m_deallocatedMemory = 0;
	public:
		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf);
		virtual void deallocate (void* p, std::size_t n);
		virtual size_t getFreeMemory();
		virtual size_t getUsedMemory();
		virtual void*  getRefPtr();

		static StdAllocatorMemBlock* GetMemBlock()
		{
			static StdAllocatorMemBlock _this;
			return &_this;
		}
	};
}

#endif