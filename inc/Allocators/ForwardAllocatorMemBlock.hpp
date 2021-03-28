#ifndef _H_ForwardAllocatorMemBlock
#define _H_ForwardAllocatorMemBlock
#include <memory>
#include "Allocators/MemBlockBase.hpp"

namespace bfu
{
	class ForwardAllocatorMemBlock: public MemBlockBase
	{
	protected:
		std::shared_ptr< MemBlockBase > shrp_forwardedMemBlock;
	public:
		ForwardAllocatorMemBlock(std::shared_ptr< MemBlockBase >& forwardTarget);
		ForwardAllocatorMemBlock(const ForwardAllocatorMemBlock& forwardTarget);

		ForwardAllocatorMemBlock& operator=(const ForwardAllocatorMemBlock& forwardTarget);


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