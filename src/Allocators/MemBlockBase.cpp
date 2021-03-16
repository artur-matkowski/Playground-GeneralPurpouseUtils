#include "MemBlockBase.hpp"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "log.hpp"

void convert(size_t& big, size_t& small)
{
    big = small / 1024;
    small = small % 1024;
}

void convert(size_t& gb, size_t& mb, size_t& kb, size_t& b)
{
    convert(kb, b);
    convert(mb, kb);
    convert(gb, mb);
}

static bfu::MemBlockBase* 		s_mBlock = 0;

namespace bfu
{
	// size_t MallocAllocator::s_allocatedInBlock = 0;
	// size_t MallocAllocator::s_deallocatedInBlock = 0;
	// int MallocAllocator::s_allocationCount = 0;
	// int MallocAllocator::s_deallocationCount = 0;
	// size_t MallocAllocator::s_memoryCapacity = 0;

	// MallocAllocator::MallocAllocator()
	// 	:MemBlockBase("Malloc Allocator")
	// {
	//     size_t pages = sysconf(_SC_PHYS_PAGES);
	//     size_t page_size = sysconf(_SC_PAGE_SIZE);
	// 	s_memoryCapacity = pages * page_size;
	// };

	// size_t MallocAllocator::getFreeMemory()
	// {
	//     return s_memoryCapacity - s_allocatedInBlock;
	// }

	// size_t MallocAllocator::getUsedMemory()
	// {
	// 	return s_allocatedInBlock;
	// }

	// void*  MallocAllocator::getRefPtr()
	// {
	// 	return nullptr;
	// }
	// void*  MallocAllocator::getMemPtr()
	// {
	// 	return nullptr;
	// }
	// bool MallocAllocator::owns(void* ptr)
	// {
	// 	return false;
	// }

	// int MallocAllocator::GetAllocationsCount() {return s_allocationCount;}
	// int MallocAllocator::GetDeallocationsCount() {return s_deallocationCount;}


	// bool BindOperatorNew2MemBlock(MemBlockBase* mBlock)
	// {
	// 	if(s_mBlock==0)
	// 	{
	// 		s_mBlock = mBlock;
	// 		return true;
	// 	}
	// 	return false;
		
	// }
}

#define TALBE_WIDTH 30

void logAlloc(	void* ptr, 
				size_t allocationSize, 
				const char* memBlockDescriptor,
				size_t allocatedInBlock,
				size_t freeInBlock,
				size_t deallocatedInBlock,
				int allocationCount,
				int deallocationCount,
				void* refPtr )
{
	size_t bytes = allocationSize;
    size_t gb = 0, mb = 0, kb = 0;
    convert(gb, mb, kb, bytes);


	size_t Bytes = allocatedInBlock;
    size_t Gb = 0, Mb = 0, Kb = 0;
    convert(Gb, Mb, Kb, Bytes);

	size_t _Bytes = freeInBlock;
    size_t _Gb = 0, _Mb = 0, _Kb = 0;
    convert(_Gb, _Mb, _Kb, _Bytes);


	log::warning << "\nMemory alocation by:   " << memBlockDescriptor << std::endl;
	std::cout 					 << std::left << std::setw(TALBE_WIDTH) << "| allocator name:" << "| " << memBlockDescriptor << "\t" << (size_t) refPtr
				 	<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| returning addr:" << "| " << std::hex << (size_t)ptr
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| end addr:" << "| " << (size_t)ptr + allocationSize 
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| allocations:" << "| \033[1;31m" << std::dec << allocationCount << "\033[0m"
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| deallocations:" << "| " << deallocationCount
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| allocated size: " << "| " << (int)gb << "Gb, " << (int)mb << "Mb, " << (int)kb << "kb, " << (int)bytes << "b"
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| allocated in this block: " << "| " << (int)Gb << "Gb, " << (int)Mb << "Mb, " << (int)Kb << "kb, " << (int)Bytes << "b"
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| free in this block: " << "| " << (int)_Gb << "Gb, " << (int)_Mb << "Mb, " << (int)_Kb << "kb, " << (int)_Bytes << "b"
					<< std::endl << std::endl;
}

void logDealloc(void* ptr, 
				size_t allocationSize, 
				const char* memBlockDescriptor,
				size_t allocatedInBlock,
				size_t freeInBlock,
				size_t deallocatedInBlock,
				int allocationCount,
				int deallocationCount,
				void* refPtr )
{
	size_t bytes = allocationSize;
    size_t gb = 0, mb = 0, kb = 0;
    convert(gb, mb, kb, bytes);

	size_t Bytes = allocatedInBlock;
    size_t Gb = 0, Mb = 0, Kb = 0;
    convert(Gb, Mb, Kb, Bytes);

	size_t _Bytes = freeInBlock;
    size_t _Gb = 0, _Mb = 0, _Kb = 0;
    convert(_Gb, _Mb, _Kb, _Bytes);


	log::warning << "\nMemory dealocation by:   " << memBlockDescriptor << std::endl;
	std::cout 					 << std::left << std::setw(TALBE_WIDTH) << "| allocator name:" << "| " << memBlockDescriptor << "\t" <<(size_t) refPtr
				 	<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| returning addr:" << "| " << std::hex << (size_t)ptr 
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| end addr:" << "| " << (size_t)ptr + allocationSize
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| allocations:" << "| " << std::dec << allocationCount 
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| deallocations:" << "| \033[1;31m" << deallocationCount << "\033[0m"
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| deallocated size:" << "| " << (int)gb << "Gb, " << (int)mb << "Mb, " << (int)kb << "kb, " << (int)bytes << "b"
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| allocated in this block: " << "| " << (int)Gb << "Gb, " << (int)Mb << "Mb, " << (int)Kb << "kb, " << (int)Bytes << "b"
					<< std::endl << std::left << std::setw(TALBE_WIDTH) << "| free in this block: " << "| " << (int)_Gb << "Gb, " << (int)_Mb << "Mb, " << (int)_Kb << "kb, " << (int)_Bytes << "b"
					<< std::endl << std::endl;
}