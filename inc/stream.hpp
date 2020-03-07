#ifndef _H_stream
#define _H_stream
#include <cstdarg>
#include <cstring>
#include <string>
#include "bfuObject.hpp"

namespace bfu{
	class stream
	{
		//lazy alocation
		int buffsize = 0;
		char* first = 0;
		char* last = 0;
		char* current = 0;

		int next_power_of_two(int n) {
		    int i = 0;
		    ++n;
		    for (--n; n > 0; n >>= 1) {
		        i++;
		    }
		    return 1 << i;
		}

	public:

		stream();
	    stream(const char* input, int size = -1);
	    stream(const stream& input);

	    ~stream();


		inline bool isOneOf(const char* str)
		{
			int size = strlen(str);

			for(int i=0; i<size; ++i)
			{
				if(*current==str[i])
				{
					return true;
				}
			}
			return false;
		}

		inline void skipToOneOf(const char* str)
		{
			while( current!=last && !isOneOf(str) ) 
			{
				++current;
			}
		}

		inline void skipTo(char c)
		{
			while( current!=last && *current!=c ) 
			{
				++current;
			}
		}
		inline void skip(int c)
		{
			if( (current + c) <= last )
			{
				current += c;
			}
			else
			{
				current = last;
			}
		}

		inline std::string str()
		{
			return std::string(first,last);
		}

		inline void SetCursonPos(int pos)
		{
			current = first + pos;
		}

		inline void sprintf(const char* str, ...)
		{
			va_list args;
			va_start(args, str);

			int t = vsnprintf(current, last-current, str, args);

			if(t > last-current)
			{
				t = next_power_of_two(current-first+t);
				resize(t);
				t = vsnprintf(current, last-current, str, args);
			}

			current += t;
			va_end(args);
		}

		inline char peak() const
		{
			return *current;
		}

		inline void resize(int newsize)
		{
			char* newbuff = new char[newsize];
			int toCopy = std::min(newsize, (int)(current-first));

			std::memcpy(newbuff, first, toCopy);

			delete[] first;

			first = newbuff;
			current = first + toCopy;
			last = first + newsize -1;
			buffsize = newsize;
		}

		inline void resize()
		{
			int size = next_power_of_two(8);
			resize(size);
		}
	};
}


#endif