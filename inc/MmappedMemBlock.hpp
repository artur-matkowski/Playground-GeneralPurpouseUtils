#ifndef _H_MmappedMemBlock
#define _H_MmappedMemBlock
#include "MemBlockBase.hpp"
#include <memory>

namespace bfu
{
	class MmappedMemBlock: public MemBlockBase
	{
	protected:
		void* m_buffStartPtr = 0;
		void* m_buffFreePtr = 0;
		void* m_buffEndPtr = 0;
		size_t m_deallocatedMemory = 0;

	public:
		inline static size_t PageSize();

		MmappedMemBlock(void* reqAddr, size_t size, const char* name = "MmappedMemBlock");
		~MmappedMemBlock();

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
		{
			size_t size = getFreeMemory();

			void* tmp = m_buffFreePtr;

			if ( m_buffFreePtr = std::align(alignOf, sizeOf, m_buffFreePtr, size ))
	        {
	            void* result = m_buffFreePtr;
	            size_t size = sizeOf * elements;
	            size = size > 0 ? size : 1;
	            m_buffFreePtr = (void*)((size_t) m_buffFreePtr + size);


	            if(m_buffFreePtr >= m_buffEndPtr)
		        {
		            //std::cout << "Failed to allocate memory by MmappedMemBlock, requested size: " << sizeOf * elements << std::endl;
  					//std::cout.flush();
  					return nullptr;
		        }

				if(result == m_buffFreePtr)
				{
					m_buffFreePtr = (void*)((size_t)m_buffFreePtr +1);
				}

				++m_allocationCount;
				#ifdef DEBUG_MEMORY_ALLOC
				logAlloc(	result, 
		    			size, 
		    			m_memBlockDescriptor,
		    			getUsedMemory(),
		    			getFreeMemory(),
		    			m_deallocatedMemory,
		    			m_allocationCount,
		    			m_deallocationCount,
		    			m_buffStartPtr);
				#endif

	            return result;
	        }
	        return nullptr;
		}

		virtual void deallocate (void* p, std::size_t n) 
		{
			m_deallocatedMemory += n;
			memset(p, 0, n);
			if( (size_t)p+n==(size_t)m_buffFreePtr)
			{
	            //std::cout << "Regaining memory becouse deallocate was called right after allocate on the same ptr" << std::endl;
				//std::cout.flush();
				m_buffFreePtr = (void*)((size_t)m_buffFreePtr - n);
			}

    		++m_deallocationCount;
			#ifdef DEBUG_MEMORY_ALLOC
   			logDealloc(	p, 
    			n, 
    			m_memBlockDescriptor,
    			getUsedMemory(),
    			getFreeMemory(),
    			m_deallocatedMemory,
    			m_allocationCount,
    			m_deallocationCount,
    			m_buffStartPtr);
			#endif
		}

		void free()
		{
			m_buffFreePtr = m_buffStartPtr;
		}


		size_t getFreeMemory()
		{
			return (size_t)m_buffEndPtr- (size_t)m_buffFreePtr;
		}
		size_t getUsedMemory()
		{
			return (size_t)m_buffFreePtr- (size_t)m_buffStartPtr;
		}
		size_t size()
		{
			return (size_t)m_buffEndPtr- (size_t)m_buffStartPtr;
		}

		void* end()
		{
			return m_buffEndPtr;
		}
		void* getRefPtr()
		{
			return this;
		}

		void* getMemPtr()
		{
			return m_buffStartPtr;
		}

		virtual bool owns(void* ptr)
		{
			if((size_t)m_buffStartPtr<(size_t)ptr && (size_t)ptr < (size_t)m_buffEndPtr)
				return true;
			
			return false;
		}

	};

}

#endif