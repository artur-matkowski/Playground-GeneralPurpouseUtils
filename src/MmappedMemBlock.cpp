#include "MmappedMemBlock.hpp"
#include "CustomAllocator.hpp"
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
		m_buffStartPtr = mmap(reqAddr, size, 
                PROT_READ | PROT_WRITE, 
                MAP_PRIVATE | MAP_ANONYMOUS, 
                -1, 0);

		//as we can not emlpace shared pointer we need temporary m_buffFreePtr to be able to later allocate m_selfRefCounter & m_buffFreePtr by custom_allocator<...>
		m_buffFreePtr = std::make_shared<void*>(m_buffStartPtr);

		//m_buffFreePtr = m_buffStartPtr = new char[stackSize];
		std::memset(m_buffStartPtr, 0, size);
		m_buffEndPtr = (void*)((size_t)m_buffStartPtr + size);

		m_selfRefCounter = std::allocate_shared<int>(custom_allocator<int>(this), 1);
		m_buffFreePtr = std::allocate_shared<void*>(custom_allocator<void*>(this), *m_buffFreePtr);
	};


	MmappedMemBlock::MmappedMemBlock(const MmappedMemBlock& cp)
		:MemBlockBase(cp)
		,m_buffStartPtr(cp.m_buffStartPtr)
		,m_buffFreePtr(cp.m_buffFreePtr)
		,m_selfRefCounter(cp.m_selfRefCounter)
		,m_buffEndPtr(cp.m_buffEndPtr)
		,m_deallocatedMemory(cp.m_deallocatedMemory)
	{
		++(*m_selfRefCounter);
	}

	MmappedMemBlock::~MmappedMemBlock()
	{
		--(*m_selfRefCounter);
		if(*m_selfRefCounter==0)
			munmap(*m_buffFreePtr, (size_t)m_buffEndPtr - (size_t)m_buffStartPtr);
	};
}