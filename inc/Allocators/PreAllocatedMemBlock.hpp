#ifndef H_PreAllocatedMemBlock
#define H_PreAllocatedMemBlock
#include <memory>
#include "Allocators/MemBlockBase.hpp"

namespace bfu
{
	class PreAllocatedMemBlock: public MemBlockBase
	{
		void* m_buffStartPtr = 0;
		void* m_buffFreePtr = 0;
		void* m_buffEndPtr = 0;
		size_t m_deallocatedMemory = 0;
	public:
		PreAllocatedMemBlock(void* memStart, size_t memSize, const char* name = "PreAllocatedMemBlock");
		PreAllocatedMemBlock(PreAllocatedMemBlock&& cp);
		~PreAllocatedMemBlock();

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf);

		virtual void deallocate (void* p, std::size_t n);

		void free();


		size_t getFreeMemory();
		size_t getUsedMemory();
		void* getRefPtr();
		void* getMemPtr();
		virtual bool owns(void* ptr);
		
	};
}

#endif