#include "ForwardAllocatorMemBlock.hpp"

namespace bfu
{
	ForwardAllocatorMemBlock::ForwardAllocatorMemBlock(std::shared_ptr< MemBlockBase >& forwardTarget)
		:MemBlockBase("Forwarded Mem Block")
		,shrp_forwardedMemBlock(forwardTarget)
	{}
	ForwardAllocatorMemBlock::ForwardAllocatorMemBlock(const ForwardAllocatorMemBlock& cp)
		:MemBlockBase(cp)
		,shrp_forwardedMemBlock(cp.shrp_forwardedMemBlock)
	{}
		
	ForwardAllocatorMemBlock& ForwardAllocatorMemBlock::operator=(const ForwardAllocatorMemBlock& cp)
	{
		shrp_forwardedMemBlock = cp.shrp_forwardedMemBlock;
	}

	size_t ForwardAllocatorMemBlock::getFreeMemory() 
	{
		return shrp_forwardedMemBlock->getFreeMemory();
	}
	size_t ForwardAllocatorMemBlock::getUsedMemory() 
	{
		return shrp_forwardedMemBlock->getUsedMemory();
	}
	void* ForwardAllocatorMemBlock::getRefPtr() 
	{
		return shrp_forwardedMemBlock->getRefPtr();
	}
	void* ForwardAllocatorMemBlock::getMemPtr() 
	{
		return shrp_forwardedMemBlock->getMemPtr();
	}
	bool ForwardAllocatorMemBlock::owns(void* p) 
	{
		return shrp_forwardedMemBlock->owns(p);
	}
	int ForwardAllocatorMemBlock::GetAllocationsCount() 
	{
		return shrp_forwardedMemBlock->GetAllocationsCount();
	}
	int ForwardAllocatorMemBlock::GetDeallocationsCount() 
	{
		return shrp_forwardedMemBlock->GetDeallocationsCount();
	}
}
