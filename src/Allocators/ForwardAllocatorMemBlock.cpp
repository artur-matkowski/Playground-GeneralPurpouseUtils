#include "ForwardAllocatorMemBlock.hpp"

namespace bfu
{
	ForwardAllocatorMemBlock::ForwardAllocatorMemBlock(MemBlockBase* forwardTarget)
		:MemBlockBase("Forwarded Mem Block")
		,p_forwardedMemBlock(forwardTarget)
	{}
	ForwardAllocatorMemBlock::ForwardAllocatorMemBlock(const ForwardAllocatorMemBlock& cp)
		:MemBlockBase(cp)
		,p_forwardedMemBlock(cp.p_forwardedMemBlock)
	{}
		
	ForwardAllocatorMemBlock& ForwardAllocatorMemBlock::operator=(const ForwardAllocatorMemBlock& cp)
	{
		p_forwardedMemBlock = cp.p_forwardedMemBlock;
		return *this;
	}

	ForwardAllocatorMemBlock& ForwardAllocatorMemBlock::operator=(MemBlockBase*  cp)
	{
		p_forwardedMemBlock = cp;
		return *this;
	}


	void* ForwardAllocatorMemBlock::allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
	{
		return p_forwardedMemBlock->allocate(elements, sizeOf, alignOf);
	}
	void ForwardAllocatorMemBlock::deallocate (void* p, std::size_t n)
	{
		MemBlockBase::DeallocateUnknown( p );
	}

	size_t ForwardAllocatorMemBlock::getFreeMemory() 
	{
		return p_forwardedMemBlock->getFreeMemory();
	}
	size_t ForwardAllocatorMemBlock::getUsedMemory() 
	{
		return p_forwardedMemBlock->getUsedMemory();
	}
	void* ForwardAllocatorMemBlock::getRefPtr() 
	{
		return p_forwardedMemBlock->getRefPtr();
	}
	void* ForwardAllocatorMemBlock::getMemPtr() 
	{
		return p_forwardedMemBlock->getMemPtr();
	}
	bool ForwardAllocatorMemBlock::owns(void* p) 
	{
		return p_forwardedMemBlock->owns(p);
	}
	int ForwardAllocatorMemBlock::GetAllocationsCount() 
	{
		return p_forwardedMemBlock->GetAllocationsCount();
	}
	int ForwardAllocatorMemBlock::GetDeallocationsCount() 
	{
		return p_forwardedMemBlock->GetDeallocationsCount();
	}
}
