#ifndef _H_MonotonicMemBlock
#define _H_MonotonicMemBlock
#include "MemBlockBase.hpp"
#include <memory>

namespace bfu
{

	template <int stackSize>
	class MonotonicMemBlock: public MemBlockBase
	{
	protected:
		void* m_buffStartPtr = 0;
		void* m_buffFreePtr = 0;
		void* m_buffEndPtr = 0;
		size_t m_deallocatedMemory = 0;
		//char buff[stackSize];

	public:
		MonotonicMemBlock(const char* name = "MonotonicMemBlock")
			:MemBlockBase(name)
		{
			m_buffFreePtr = m_buffStartPtr = new char[stackSize];
			std::memset(m_buffFreePtr, 0, stackSize);
			m_buffEndPtr = (void*)((size_t)m_buffStartPtr + (size_t)stackSize);
		};
		~MonotonicMemBlock(){};

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
		{
			size_t size = getFreeMemory();

			void* tmp = m_buffFreePtr;

			if ( m_buffFreePtr = std::align(alignOf, sizeOf, m_buffFreePtr, size ))
	        {
	            void* result = m_buffFreePtr;
	            m_buffFreePtr = (void*)((size_t) m_buffFreePtr + sizeOf * elements);


	            if(m_buffFreePtr >= m_buffEndPtr)
		        {
		            std::cout << "Failed to allocate memory by MonotonicMemBlock, requested size: " << sizeOf * elements << std::endl;
  					std::cout.flush();
  					return nullptr;
		        }
	            if(getFreeMemory() < 0)
					return nullptr;

				if(result == m_buffFreePtr)
				{
					m_buffFreePtr = (void*)((size_t)m_buffFreePtr +1);
				}
				#ifdef DEBUG_MEMORY_ALLOC
				logAlloc(	result, 
		    			sizeOf * elements, 
		    			m_memBlockDescriptor,
		    			getUsedMemory(),
		    			getFreeMemory(),
		    			m_deallocatedMemory,
		    			++m_allocationCount,
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
	            std::cout << "Regaining memory becouse deallocate was called right after allocate on the same ptr" << std::endl;
				std::cout.flush();
				m_buffFreePtr = (void*)((size_t)m_buffFreePtr - n);
			}

			#ifdef DEBUG_MEMORY_ALLOC
   			logDealloc(	p, 
    			n, 
    			m_memBlockDescriptor,
    			getUsedMemory(),
    			getFreeMemory(),
    			m_deallocatedMemory,
    			m_allocationCount,
    			++m_deallocationCount,
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
		void* getRefPtr()
		{
			return this;
		}

		static MonotonicMemBlock* GetMemBlock()
		{
			static MonotonicMemBlock<stackSize> _this;
			return &_this;
		}
	};

}

#endif