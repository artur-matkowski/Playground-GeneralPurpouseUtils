#ifndef _H_bfuObject
#define _H_bfuObject
#include <cstddef>
#include <iostream>
#include <memory>
#include <sys/mman.h>

namespace bfu
{

	class MemBlockBase
	{
	public:
		virtual void* allocate (int elements, std::size_t offset, std::size_t sizeOf) = 0;
		virtual void deallocate (void* p, std::size_t n){};
		virtual size_t getFreeMemory() = 0;
	};


	template <int stackSize>
	class MonotonicMemBlock: public MemBlockBase
	{
	protected:
		void* m_buffStartPtr = 0;
		void* m_buffFreePtr = 0;
		void* m_buffEndPtr = 0;
		char buff[stackSize];

	public:
		MonotonicMemBlock()
		{
			m_buffFreePtr = m_buffStartPtr = buff;
			m_buffEndPtr = (void*)((size_t)m_buffStartPtr + (size_t)stackSize);
		};
		~MonotonicMemBlock(){};

		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf)
		{
			size_t size = getFreeMemory();
	        if (std::align(alignOf, sizeOf, m_buffFreePtr, size ))
	        {
	            void* result = m_buffFreePtr;
	            m_buffFreePtr = (void*)((size_t) m_buffFreePtr + sizeOf * elements);
	            return result;
	        }
	        return nullptr;
		}

		virtual void deallocate (void* p, std::size_t n) 
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

		static MonotonicMemBlock* GetMemBlock()
		{
			static MonotonicMemBlock<stackSize> _this;
			return &_this;
		}
	};


void convert(int& gb, int& mb, int& kb, int& b);


template <class T, class MemBlockType>
struct custom_allocator {

	typedef T value_type;
	MemBlockBase* m_memBlock = 0;

	custom_allocator(MemBlockBase* memBlock = MemBlockType::GetMemBlock()) noexcept 
	{
  		std::cout << "\tcustom_allocator()\n";
  		std::cout.flush();
  		m_memBlock = memBlock;
	}
	~custom_allocator() noexcept 
	{
  		std::cout << "\t~custom_allocator()\n";
  		std::cout.flush();
	}

	template <class U, class A> custom_allocator (const custom_allocator<U, A>& cp) noexcept 
	{
  		std::cout << "\tcustom_allocator(&)\n";
  		std::cout.flush();
  		m_memBlock = cp.m_memBlock;
  	}

	T* allocate (std::size_t n) 
	{ 
		int bytes = 0;
    	int gb = 0, mb = 0, kb = 0;

  		T* ret = static_cast<T*>(m_memBlock->allocate( n, sizeof(T), alignof(T) ));
  		bytes = (int)m_memBlock->getFreeMemory();
  		convert(gb, mb, kb, bytes);

  		std::cout << "allocate() remaining memory: " << gb << "Gb, "
  				<< mb << "Mb, " << kb << "kb, " << bytes << "b, "  << std::endl;
  		std::cout.flush();  		
		return ret; 
	}

	void deallocate (T* p, std::size_t n) 
	{
  		m_memBlock->deallocate(p, n);
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