#ifndef _H_MemBlockBase
#define _H_MemBlockBase
#include <cstddef>

namespace bfu
{
	class MemBlockBase
	{
	protected:
		char 		m_memBlockDescriptor[255] = {'\0'};
		int 		m_allocationCount = 0;
		int 		m_deallocationCount = 0;
	public:
		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf) = 0;
		virtual void deallocate (void* p, std::size_t n){};
		virtual size_t getFreeMemory() = 0;
		virtual size_t getUsedMemory() = 0;
		virtual void*  getRefPtr() = 0;
	};
}

void* operator new(std::size_t size);
void operator delete(void* p) noexcept;

void logAlloc(	void* ptr, 
				size_t allocationSize, 
				const char* memBlockDescriptor,
				size_t allocatedInBlock,
				size_t freeInBlock,
				size_t deallocatedInBlock,
				int allocationCount,
				int deallocationCount,
				void* refPtr );

void logDealloc(void* ptr, 
				size_t allocationSize, 
				const char* memBlockDescriptor,
				size_t allocatedInBlock,
				size_t freeInBlock,
				size_t deallocatedInBlock,
				int allocationCount,
				int deallocationCount,
				void* refPtr );

#endif