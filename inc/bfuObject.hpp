#ifndef _H_bfuObject
#define _H_bfuObject
#include <cstddef>
#include <iostream>
#include <memory>
#include <sys/mman.h>

namespace bfu
{

class MonotonicAllocator
{
	void* 	m_buffStart = 0;
	void* 	m_buffEnd = 0;
	size_t 	m_size = 0;


	void* GetAlignedAddr(size_t alignment)
	{
		//void* ptr_fixed = (void*)((uintptr_t)m_buffEnd + ()(alignment - 1)) & ~((uintptr_t)(alignment - 1));
		return 0;
	}

public:

	MonotonicAllocator(size_t size)
	{
		m_size = size;
		m_buffEnd = m_buffStart = mmap((void*)0x10000, m_size, 
                    PROT_READ | PROT_WRITE, 
                    MAP_PRIVATE | MAP_ANONYMOUS, 
                    -1, 0);
	}

	~MonotonicAllocator()
	{
  		munmap(m_buffStart, m_size);
	}

	template <typename T>
    T* Alloc(std::size_t elements = alignof(T))
    {
        if (std::align(elements, sizeof(T), m_buffEnd, m_size))
        {
            T* result = reinterpret_cast<T*>(m_buffEnd);
            m_buffEnd = (void*)((size_t) m_buffEnd + sizeof(T));
            m_size -= sizeof(T);
            return result;
        }
        return nullptr;
    }

	void Free()
	{
		m_buffEnd = m_buffStart;
	}

	static MonotonicAllocator& GetAllocator()
	{
		static MonotonicAllocator _this(1024*1024*10);  //10 of Mb memory pre allocated
		return _this;
	}

	size_t GetFreeMemory()
	{
		return m_size;
	}

};

template <class T>
struct custom_allocator {

	typedef T value_type;

	custom_allocator() noexcept 
	{
  		std::cout << "\tcustom_allocator()\n";
  		std::cout.flush();
	}
	~custom_allocator() noexcept 
	{
  		std::cout << "\t~custom_allocator()\n";
  		std::cout.flush();
	}

	template <class U> custom_allocator (const custom_allocator<U>&) noexcept 
	{
  		std::cout << "\tcustom_allocator(&)\n";
  		std::cout.flush();
  	}
/*
	T* allocate (std::size_t n) 
	{ 
  		static MonotonicAllocator& Allocator = MonotonicAllocator::GetAllocator();
  		T* ret = static_cast<T*>(Allocator.Alloc<T>(n));
  		std::cout << "allocate() remaining memory: " << Allocator.GetFreeMemory() << std::endl;
  		std::cout.flush();  		
		return ret; 
	}

	void deallocate (T* p, std::size_t n) 
	{
  		std::cout << "deallocate()\n";
  		std::cout.flush();
		//::delete(p); 
	}
*/
	T* allocate (std::size_t n) 
	{ 
		/*
  		static MonotonicAllocator& Allocator = MonotonicAllocator::GetAllocator();
  		T* ret = static_cast<T*>(Allocator.Alloc<T>(n));
  		std::cout << "allocate() remaining memory: " << Allocator.GetFreeMemory() << std::endl;
  		std::cout.flush();  
  		*/		
		return static_cast<T*>(::operator new(n*sizeof(T))); 
	}

	void deallocate (T* p, std::size_t n) 
	{
  		//std::cout << "deallocate()\n";
  		//std::cout.flush();
		::delete(p); 
	}
};

}


void* operator new(std::size_t size);
void operator delete(void* p) noexcept;


static bool LineRaport(char const* file, int line)
{
    std::cout << "\nAlocation called from: " << file << ":" << line;
  	std::cout.flush();
    return false;
}

#define TRACE_NEW LineRaport(__FILE__,__LINE__)?0:new 

#define ALLOC(T,n) MonotonicAllocator::GetAllocator().Alloc<T>(n)



#endif