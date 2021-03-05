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
		virtual void deallocate (void* p, std::size_t n){};
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

	class MallocAllocator: public MemBlockBase
	{
		static size_t s_allocatedInBlock;
		static size_t s_deallocatedInBlock;
		static int s_allocationCount;
		static int s_deallocationCount;
		static size_t s_memoryCapacity;
	public:

		MallocAllocator();

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf) 
		{
 			void * p = malloc(sizeOf==0?1:sizeOf); 

			++s_allocationCount;
    		s_allocatedInBlock+=sizeOf;

			#ifdef DEBUG_MEMORY_ALLOC
		    logAlloc(	p, 
    			sizeOf==0?1:sizeOf, 
    			"global operator NEW",
    			s_allocatedInBlock,
    			0,
    			s_deallocatedInBlock,
    			s_allocationCount,
    			s_deallocationCount,
    			0);
		    #endif

    		return p; 
		}
		virtual void deallocate (void* p, std::size_t n)
		{
			++s_deallocationCount;

			#ifdef DEBUG_MEMORY_ALLOC
			logDealloc(p, 
		    			0, 
		    			"global operator NEW",
		    			s_allocatedInBlock,
		    			0,
		    			s_deallocatedInBlock,
		    			s_allocationCount,
		    			s_deallocationCount,
		    			0);
		    #endif

		    free(p); 
		}

		virtual size_t getFreeMemory();
		virtual size_t getUsedMemory();
		virtual void*  getRefPtr();
		virtual void* getMemPtr();
		virtual bool owns(void*);

		virtual int GetAllocationsCount();
		virtual int GetDeallocationsCount();
	};

	bool BindOperatorNew2MemBlock(MemBlockBase*);
}

void* operator new(std::size_t size);
void operator delete(void* p) noexcept;

#endif