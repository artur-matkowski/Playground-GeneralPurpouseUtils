#ifndef _H_MemBlockBase
#define _H_MemBlockBase
#include <cstddef>
#include <cstring>
#include <cstdlib>

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



namespace bfu
{
	class MemBlockBase;

	struct MemChunkHeader
	{
		MemBlockBase* 	m_MemBlockOwner = nullptr;
		size_t			m_sizeOfChunk = 0;

		static MemChunkHeader* InitFromLifePtr(void* ptr);
	};

	class MemBlockBase
	{
	protected:
		char 		m_memBlockDescriptor[255] = {'\0'};
		int 		m_allocationCount = 0;
		int 		m_deallocationCount = 0;
	public:
		MemBlockBase(const char* name)
		{
			strncpy(m_memBlockDescriptor, name, sizeof(m_memBlockDescriptor));
		}
		MemBlockBase(const MemBlockBase& cp)
		{
			strncpy(m_memBlockDescriptor, cp.m_memBlockDescriptor, sizeof(m_memBlockDescriptor));
			m_allocationCount = cp.m_allocationCount;
			m_deallocationCount = cp.m_allocationCount;
		}
		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf) = 0;
		virtual void deallocate (void* p, std::size_t n) = 0;
		static void DeallocateUnknown(void* p);


		virtual size_t getFreeMemory() = 0;
		virtual size_t getUsedMemory() = 0;
		virtual void*  getRefPtr() = 0;
		virtual void* getMemPtr() = 0;
		virtual bool owns(void*) = 0;

		const char* GetDescription() const
		{
			return m_memBlockDescriptor;
		}
		virtual int GetAllocationsCount() {return m_allocationCount;}
		virtual int GetDeallocationsCount() {return m_deallocationCount;}
	};
}


#endif