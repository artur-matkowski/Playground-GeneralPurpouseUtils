#include "MmappedMemBlock.hpp"
#include <unistd.h>
#include <sys/mman.h>
#include <memory>

namespace bfu
{

	size_t MmappedMemBlock::PageSize()
	{
		static size_t pageSize = sysconf(_SC_PAGE_SIZE);
	    return pageSize;
	}

	MmappedMemBlock::MmappedMemBlock(void* reqAddr, size_t size, const char* name)
		:MemBlockBase(name)
	{
		reqAddr = std::align(PageSize(), 1, reqAddr, size);
		m_buffStartPtr = m_buffFreePtr = mmap(reqAddr, size, 
                PROT_READ | PROT_WRITE, 
                MAP_PRIVATE | MAP_ANONYMOUS, 
                -1, 0);

		//m_buffFreePtr = m_buffStartPtr = new char[stackSize];
		std::memset(m_buffFreePtr, 0, size);
		m_buffEndPtr = (void*)((size_t)m_buffStartPtr + size);
	};


	MmappedMemBlock::MmappedMemBlock(const MmappedMemBlock& cp)
		:MemBlockBase(cp)
		,m_buffStartPtr(cp.m_buffStartPtr)
		,m_buffFreePtr(cp.m_buffFreePtr)
		,m_buffEndPtr(cp.m_buffEndPtr)
		,m_deallocatedMemory(cp.m_deallocatedMemory)
	{
	}

	MmappedMemBlock::~MmappedMemBlock()
	{
		munmap(m_buffFreePtr, (size_t)m_buffEndPtr - (size_t)m_buffStartPtr);
	};
}