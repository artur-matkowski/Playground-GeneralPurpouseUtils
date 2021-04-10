#include "PreAllocatedMemBlock.hpp"

namespace bfu
{
	PreAllocatedMemBlock::PreAllocatedMemBlock(void* memStart, size_t memSize, const char* name)
		:bfu::MemBlockBase(name)
	{
		m_buffFreePtr = m_buffStartPtr = memStart;
		std::memset(m_buffFreePtr, 0, memSize);
		m_buffEndPtr = (void*)((size_t)m_buffStartPtr + memSize);
	}
	PreAllocatedMemBlock::PreAllocatedMemBlock(PreAllocatedMemBlock&& cp)
		:bfu::MemBlockBase(cp.m_memBlockDescriptor)
	{
		m_buffStartPtr = cp.m_buffStartPtr;
		cp.m_buffStartPtr = nullptr;

		m_buffFreePtr = cp.m_buffFreePtr;
		cp.m_buffFreePtr = nullptr;

		m_buffEndPtr = cp.m_buffEndPtr;
		cp.m_buffEndPtr = nullptr;

		m_deallocatedMemory = cp.m_deallocatedMemory;
		cp.m_deallocatedMemory = 0;

	}
	PreAllocatedMemBlock::~PreAllocatedMemBlock()
	{
		//no deallocation on pre suplied buffer
	}


	void* PreAllocatedMemBlock::allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
	{
		size_t freeMemory = getFreeMemory()-sizeof(MemChunkHeader);

		void* tmp = (void*) ((size_t)m_buffFreePtr + sizeof(MemChunkHeader));

		if ( tmp = std::align(alignOf, sizeOf, tmp, freeMemory ))
        {
            void* result = tmp;
            size_t size = sizeOf * elements;
            size = size > 0 ? size : 1;

	        bfu::MemChunkHeader* headerInfo = (bfu::MemChunkHeader*)((size_t)result-(size_t)sizeof(bfu::MemChunkHeader));
	        headerInfo->m_MemBlockOwner = this;
	        headerInfo->m_sizeOfChunk = (size_t)result - (size_t)m_buffFreePtr + size;
	        headerInfo->m_actuallBlockStart = m_buffFreePtr;

            m_buffFreePtr = (void*)((size_t) result + size);

			++m_allocationCount;

            return result;
        }
        return nullptr;
	}

	void PreAllocatedMemBlock::deallocate (void* p, std::size_t n) 
	{
	    bfu::MemChunkHeader* headerInfo = bfu::MemChunkHeader::InitFromLifePtr(p);
		m_deallocatedMemory += headerInfo->m_sizeOfChunk;

		memset(headerInfo->m_actuallBlockStart, 0, headerInfo->m_sizeOfChunk );

		++m_deallocationCount;
	}

	void PreAllocatedMemBlock::free()
	{
		m_buffFreePtr = m_buffStartPtr;
	}


	size_t PreAllocatedMemBlock::getFreeMemory()
	{
		return (size_t)m_buffEndPtr- (size_t)m_buffFreePtr;
	}
	size_t PreAllocatedMemBlock::getUsedMemory()
	{
		return (size_t)m_buffFreePtr- (size_t)m_buffStartPtr;
	}
	void* PreAllocatedMemBlock::getRefPtr()
	{
		return this;
	}
	void* PreAllocatedMemBlock::getMemPtr()
	{
		return m_buffStartPtr;
	}
	bool PreAllocatedMemBlock::owns(void* ptr)
	{
		if((size_t)m_buffStartPtr<(size_t)ptr && (size_t)ptr < (size_t)m_buffEndPtr)
			return true;
		
		return false;
	}
}