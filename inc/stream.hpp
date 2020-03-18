#ifndef _H_stream
#define _H_stream
#include <cstdarg>
#include <cstring>
#include <string>
#include <iostream>
#include "bfuObject.hpp"
//#include <iostream>
	
namespace bfu{
	class stream
	{
	protected:
		const int minimalbuffsize = 64;
		//lazy alocation if buffsize = 0
		int buffsize = 0;
		char* first = 0;
		char* last = 0;
		char* current = 0;

		enum class status{NOK = -1, OK = 0};

		status m_status = status::OK;

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

	    inline int size() const
	    {
	    	return (int)(current-first);
	    }

	    inline bool eof()
	    {
	    	return current==last;
	    }

		inline void clear()
		{
			current = first;
		}

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
			while( !eof() && *current!=c ) 
			{
				++current;
			}
		}
		inline void skip(int c)
		{
			if( (current + c) > last )
			{
				int newSize = next_power_of_two(size()+c+2);
				resize(newSize);
			}

			current += c;
		}

		inline std::string str()
		{
			return std::string(first,last);
		}

		inline void SetCursonPos(int pos)
		{
			if(pos > buffsize)
			{
				int t = next_power_of_two(pos);
				resize(t);
			}

			current = first + pos;
		}

		inline void sprintf(const char* str, ...)
		{
			va_list args1;
			va_start(args1, str);
			va_list args2;
    		va_copy(args2, args1);

			int t = vsnprintf(current, last-current, str, args1);

			va_end(args1);

			if(t >= last-current)
			{
				t = next_power_of_two(current-first+t+2);
				resize(t);

				t = vsnprintf(current, last-current, str, args2);

			}
    		va_end(args2);

			current += t;
		}

		inline char peak(int offset = 0) const
		{
			return current[offset];
		}

		inline void put(char c)
		{
			if( current == last )
			{
				int newSize = last-first+1;
				newSize = next_power_of_two(newSize);
				resize(newSize);
			}

			*current = c;
			++current;			
		}

		inline void resize(int newsize)
		{
			newsize = std::max(newsize, minimalbuffsize);
			char* newbuff = new char[newsize];
			int toCopy = std::min(newsize, (int)(current-first));

			std::memset(newbuff, ' ', newsize);
			std::memcpy(newbuff, first, toCopy);

			delete[] first;

			first = newbuff;
			current = first + toCopy;
			//*current = ' ';
			last = first + newsize -1;
			buffsize = newsize;
		}

		inline void grow(int minSize)
		{
			int newSize = last-first+1;
			newSize = next_power_of_two(newSize);
			resize(newSize);
		}

		inline status getStatus()
		{
			return m_status;
		}

		inline void resize()
		{
			int size = next_power_of_two(buffsize);
			resize(size);
		}

		stream& operator<<(const char* val)
		{
			this->sprintf(val);

			return *this;
		}

		stream& operator<<(const int& val)
		{
			this->sprintf("%d", val);

			return *this;
		}

		stream& operator<<(const float& val)
		{
			this->sprintf("%f", val);

			return *this;
		}

		stream& operator<<(const bool& val)
		{
			this->sprintf("%d", val);

			return *this;
		}

		stream& operator<<(const std::string& val)
		{
			this->sprintf(val.c_str());

			return *this;
		}

		stream& operator<<(std::ostream& (*os)(std::ostream&))
		{
			this->sprintf("\n");
			
			return *this;
		}

		inline char operator[](int i) const
		{
			return first[i];
		}

		inline stream& operator=(const bfu::stream& src)
		{
			buffsize = src.buffsize;
			resize(buffsize);

			std::memcpy(first, src.first, buffsize);

			const int offset = src.current - src.first;

			current = first + offset;

			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const bfu::stream& strm);
	};

	std::ostream& operator<<(std::ostream& os, const bfu::stream& strm);



}

using bfu::operator<<;


#endif