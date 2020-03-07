#ifndef _H_bfuOjbect
#define _H_bfuOjbect
#include <cstddef>

void* operator new(size_t);
void operator delete(void*) noexcept;

#endif