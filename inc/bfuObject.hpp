#ifndef _H_bfuObject
#define _H_bfuObject
#include <cstddef>
#include <iostream>
#include <memory>
#include <sys/mman.h>
#include <stdlib.h>
#include <cstring>

namespace bfu
{

	class MemBlockBase
	{
	public:
		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf) = 0;
		virtual void deallocate (void* p, std::size_t n){};
		virtual size_t getFreeMemory() = 0;
	};

	class StdAllocatorMemBlock: public MemBlockBase
	{
	public:
		virtual void* allocate (int elements, std::size_t sizeOf, std::size_t alignOf);
		virtual void deallocate (void* p, std::size_t n);
		virtual size_t getFreeMemory();

		static StdAllocatorMemBlock* GetMemBlock()
		{
			static StdAllocatorMemBlock _this;
			return &_this;
		}
	};


	template <int stackSize>
	class MonotonicMemBlock: public MemBlockBase
	{
	protected:
		void* m_buffStartPtr = 0;
		void* m_buffFreePtr = 0;
		void* m_buffEndPtr = 0;
		//char buff[stackSize];

	public:
		MonotonicMemBlock()
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

	            std::cout << "Allocating memory by MonotonicMemBlock, requested size: " << sizeOf * elements << std::endl;
					std::cout.flush();
	            if(m_buffFreePtr >= m_buffEndPtr)
		        {
		            std::cout << "Failed to allocate memory by MonotonicMemBlock, requested size: " << sizeOf * elements << std::endl;
  					std::cout.flush();
  					return nullptr;
		        }
	            if(getFreeMemory() < 0)
					return nullptr;
	            return result;
	        }
	        return nullptr;
		}

		virtual void deallocate (void* p, std::size_t n) 
		{
			memset(p, 0, n);
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


	void convert(size_t& gb, size_t& mb, size_t& kb, size_t& b);


	template <class T>
	struct custom_allocator {

		typedef T value_type;
		MemBlockBase* m_memBlock = 0;

		custom_allocator(MemBlockBase* memBlock = StdAllocatorMemBlock::GetMemBlock()) noexcept 
		{
	  		//std::cout << "\tcustom_allocator()\n";
	  		//std::cout.flush();
	  		m_memBlock = memBlock;
		}
		~custom_allocator() noexcept 
		{
	  		//std::cout << "\t~custom_allocator()\n";
	  		//std::cout.flush();
		}

		template <class U> custom_allocator (const custom_allocator<U>& cp) noexcept 
		{
	  		m_memBlock = cp.m_memBlock;
	  	}

		T* allocate (std::size_t n) 
		{ 
			size_t bytes = 0;
	    	size_t gb = 0, mb = 0, kb = 0;

	  		T* ret = (T*)(m_memBlock->allocate( n, sizeof(T), alignof(T) ));
	  		bytes = m_memBlock->getFreeMemory();
	  		convert(gb, mb, kb, bytes);

	  		std::cout << /*typeid(T).name() <<*/ " allocate(" << n << ") sizeof(" << sizeof(T) << ")\talignof(" << alignof(T) << ") " << 
	  				std::hex << (size_t)ret << std::dec << " remaining memory: " << gb << "Gb, "
	  				<< mb << "Mb, " << kb << "kb, " << bytes << "b, "  << std::endl;
	  		std::cout.flush();  		
			return ret; 
		}

		void deallocate (T* p, std::size_t n) 
		{
	  		m_memBlock->deallocate(p, n * sizeof(T));
	  		std::cout << "deallocate() " << std::hex <<(size_t)p << std::dec << std::endl;
	  		std::cout.flush();  		
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

	template <class T, class U>
	bool operator==(const custom_allocator<T>&, const custom_allocator<U>&) { return true; }
	template <class T, class U>
	bool operator!=(const custom_allocator<T>&, const custom_allocator<U>&) { return false; }


	typedef std::basic_string<char, std::char_traits<char>, custom_allocator<char> > string;
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