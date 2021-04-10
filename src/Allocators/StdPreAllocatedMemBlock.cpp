#include "StdPreAllocatedMemBlock.hpp"

namespace bfu
{
	StdPreAllocatedMemBlock::StdPreAllocatedMemBlock( uint32_t size, const char* name, MemBlockBase* memBlock)
		:PreAllocatedMemBlock( (char*)memBlock->allocate(size, sizeof(char), alignof(char))
							, size
							, name)
		,mBlock(memBlock)
		,m_size(size)
	{}

	StdPreAllocatedMemBlock::StdPreAllocatedMemBlock(StdPreAllocatedMemBlock&& cp)
		:PreAllocatedMemBlock( std::move(cp) )
	{}

	StdPreAllocatedMemBlock::~StdPreAllocatedMemBlock()
	{
		if(m_buffStartPtr!=0)
		{
			mBlock->deallocate(m_buffStartPtr, m_size);
		}
	}
}