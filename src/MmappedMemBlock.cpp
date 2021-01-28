#include "MmappedMemBlock.hpp"
#include <unistd.h>
#include <sys/mman.h>

namespace bfu
{

	size_t MmappedMemBlock::PageSize()
	{
		static size_t pageSize = sysconf(_SC_PAGE_SIZE);
	    return pageSize;
	}

	MmappedMemBlock::MmappedMemBlock(size_t startingPointPage, size_t size, const char* name)
		:MemBlockBase(name)
	{
		m_buffStartPtr = m_buffFreePtr = mmap((void*)(PageSize() * startingPointPage), size, 
                PROT_READ | PROT_WRITE, 
                MAP_PRIVATE | MAP_ANONYMOUS, 
                -1, 0);

		//m_buffFreePtr = m_buffStartPtr = new char[stackSize];
		std::memset(m_buffFreePtr, 0, size);
		m_buffEndPtr = (void*)((size_t)m_buffStartPtr + size);
	};

	MmappedMemBlock::~MmappedMemBlock()
	{
		munmap(m_buffFreePtr, (size_t)m_buffEndPtr - (size_t)m_buffStartPtr);
	};
}