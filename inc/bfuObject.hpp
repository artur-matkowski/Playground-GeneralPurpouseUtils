#ifndef _H_bfuObject
#define _H_bfuObject
#include <cstddef>
#include <iostream>
#include <memory>
#include <sys/mman.h>

namespace bfu
{

class MonotonicAlocatorBase
{
protected:
	void* m_buffStartPtr = 0;
	void* m_buffFreePtr = 0;
	void* m_buffEndPtr = 0;

public:
	MonotonicAlocatorBase(){};
	~MonotonicAlocatorBase(){};

	template <typename T>
	T* allocate (int elements = 1, std::size_t offset = alignof(T))
    {
    	size_t size = getFreeMemory();
        if (std::align(offset, sizeof(T), m_buffFreePtr, size ))
        {
            T* result = reinterpret_cast<T*>(m_buffFreePtr);
            m_buffFreePtr = (void*)((size_t) m_buffFreePtr + sizeof(T) * elements);
            return result;
        }
        return nullptr;
    }

	template <typename T>
	void deallocate (T* p, std::size_t n) 
	{

	}

	void free()
	{
		m_buffFreePtr = m_buffStartPtr;
	}


	size_t getFreeMemory()
	{
		return (size_t)m_buffEndPtr- (size_t)m_buffFreePtr;
	}
};

template <int stackSize>
class MonotonicAllocator: public MonotonicAlocatorBase
{
	char buff[stackSize];
public:

	MonotonicAllocator()
	{
		m_buffFreePtr = m_buffStartPtr = buff;
		m_buffEndPtr = (void*)((size_t)m_buffStartPtr + (size_t)stackSize);

		/*
		m_size = size;
		m_buffEnd = m_buffStart = mmap((void*)0x10000, m_size, 
                    PROT_READ | PROT_WRITE, 
                    MAP_PRIVATE | MAP_ANONYMOUS, 
                    -1, 0);*/
	}

	virtual ~MonotonicAllocator()
	{
  		//munmap(m_buffStart, m_size);
	}



	static MonotonicAlocatorBase* GetAllocator()
	{
		static MonotonicAllocator<stackSize> _this;
		return &_this;
	}
};



template <class T, class Allocator>
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

	template <class U, class A> custom_allocator (const custom_allocator<U, A>&) noexcept 
	{
  		std::cout << "\tcustom_allocator(&)\n";
  		std::cout.flush();
  	}

	T* allocate (std::size_t n) 
	{ 
  		static MonotonicAlocatorBase* allocator = Allocator::GetAllocator();
  		T* ret = static_cast<T*>(allocator->allocate<T>(n));
  		std::cout << "allocate() remaining memory: " << allocator->getFreeMemory()/1024.0f << "kb" << std::endl;
  		std::cout.flush();  		
		return ret; 
	}

	void deallocate (T* p, std::size_t n) 
	{
  		static MonotonicAlocatorBase* allocator = Allocator::GetAllocator();
  		allocator->deallocate(p, n);
  		std::cout << "deallocate()\n";
  		std::cout.flush();
		//::delete(p); 
	}

  	/*
	T* allocate (std::size_t n) 
	{ 
		return static_cast<T*>(::operator new(n*sizeof(T))); 
	}

	void deallocate (T* p, std::size_t n) 
	{
		::delete(p); 
	}*/
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