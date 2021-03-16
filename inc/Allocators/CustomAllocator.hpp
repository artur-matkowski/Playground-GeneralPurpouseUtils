#ifndef _H_CustomAllocator
#define _H_CustomAllocator
#include "StdAllocatorMemBlock.hpp"

namespace bfu
{

	template <class T>
	struct custom_allocator {

		typedef T value_type;
		MemBlockBase* m_memBlock = 0;

		custom_allocator(MemBlockBase* memBlock = StdAllocatorMemBlock::GetMemBlock()) noexcept 
		{
	  		m_memBlock = memBlock;
		}
		~custom_allocator() noexcept 
		{
		}

		template <class U> custom_allocator (const custom_allocator<U>& cp) noexcept 
		{
	  		m_memBlock = cp.m_memBlock;
	  	}

		T* allocate (std::size_t n) 
		{
	  		T* ret = (T*)(m_memBlock->allocate( n, sizeof(T), alignof(T) ));		
			return ret; 
		}

		void deallocate (T* p, std::size_t n) 
		{
	  		m_memBlock->deallocate(p, n * sizeof(T));	
		}

	};

	template <class T, class U>
	bool operator==(const custom_allocator<T>&, const custom_allocator<U>&) { return true; }
	template <class T, class U>
	bool operator!=(const custom_allocator<T>&, const custom_allocator<U>&) { return false; }

}

#endif