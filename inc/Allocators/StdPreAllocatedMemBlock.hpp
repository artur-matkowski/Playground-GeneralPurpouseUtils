#ifndef H_STDPreAllocatedMemBlock
#define H_STDPreAllocatedMemBlock
#include <memory>
#include "Allocators/PreAllocatedMemBlock.hpp"
#include "Allocators/StdAllocatorMemBlock.hpp"

namespace bfu
{
	class StdPreAllocatedMemBlock: public PreAllocatedMemBlock
	{
		MemBlockBase* 	mBlock = nullptr;
		uint32_t 		m_size = 0;
	public:
		StdPreAllocatedMemBlock( uint32_t size, const char* name = "StdPreAllocatedMemBlock", MemBlockBase* memBlock = StdAllocatorMemBlock::GetMemBlock());
		StdPreAllocatedMemBlock(StdPreAllocatedMemBlock&& cp);
		~StdPreAllocatedMemBlock();
	};
}

#endif