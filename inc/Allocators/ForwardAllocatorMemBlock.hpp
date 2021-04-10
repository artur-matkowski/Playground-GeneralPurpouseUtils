#ifndef _H_ForwardAllocatorMemBlock
#define _H_ForwardAllocatorMemBlock
#include <memory>
#include "Allocators/MemBlockBase.hpp"

namespace bfu
{
	class ForwardAllocatorMemBlock: public MemBlockBase
	{
	protected:
		MemBlockBase* p_forwardedMemBlock;
	public:
		ForwardAllocatorMemBlock(MemBlockBase* forwardTarget);
		ForwardAllocatorMemBlock(const ForwardAllocatorMemBlock& forwardTarget);

		ForwardAllocatorMemBlock& operator=(const ForwardAllocatorMemBlock& forwardTarget);
		ForwardAllocatorMemBlock& operator=(MemBlockBase* forwardTarget);


		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf) override;
		virtual void deallocate (void* p, std::size_t n) override;


		virtual size_t getFreeMemory() override;
		virtual size_t getUsedMemory() override;
		virtual void*  getRefPtr() override;
		virtual void* getMemPtr() override;
		virtual bool owns(void*) override;
		virtual int GetAllocationsCount() override;
		virtual int GetDeallocationsCount() override;
	};

}

#endif