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
		const int m_minimalbuffsize = 64;
		//lazy alocation if buffsize = 0 and not constructing with size
		int m_buffsize = 0;
		char* m_first = 0;
		char* m_last = 0;
		char* m_current = 0;

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
	    stream(const int size);

	    ~stream();

	    inline int size() const
	    {
	    	return (int)(m_current-m_first);
	    }

	    inline bool eof()
	    {
	    	return m_current==m_last;
	    }

		inline void clear()
		{
			m_current = m_first;
		}

		inline bool isOneOf(const char* str)
		{
			int size = strlen(str);

			for(int i=0; i<size; ++i)
			{
				if(*m_current==str[i])
				{
					return true;
				}
			}
			return false;
		}

		inline void skipToOneOf(const char* str)
		{
			while( m_current!=m_last && !isOneOf(str) ) 
			{
				++m_current;
			}
		}

		inline void skipTo(char c)
		{
			while( !eof() && *m_current!=c ) 
			{
				++m_current;
			}
		}
		inline void skip(int c)
		{
			if( (m_current + c) > m_last )
			{
				int newSize = next_power_of_two(size()+c+2);
				resize(newSize);
			}

			m_current += c;
		}

		inline std::string str()
		{
			return std::string(m_first,m_last);
		}

		inline void SetCursonPos(int pos)
		{
			if(pos > m_buffsize)
			{
				int t = next_power_of_two(pos);
				resize(t);
			}

			m_current = m_first + pos;
		}

		inline void sprintf(const char* str, ...)
		{
			va_list args1;
			va_start(args1, str);
			va_list args2;
    		va_copy(args2, args1);

			int t = vsnprintf(m_current, m_last-m_current, str, args1);

			va_end(args1);

			if(t >= m_last-m_current)
			{
				t = next_power_of_two(m_current-m_first+t+2);
				resize(t);

				t = vsnprintf(m_current, m_last-m_current, str, args2);

			}
    		va_end(args2);

			m_current += t;
		}

		inline char peak(int offset = 0) const
		{
			return m_current[offset];
		}

		inline void put(char c)
		{
			if( m_current == m_last )
			{
				int newSize = m_last-m_first+1;
				newSize = next_power_of_two(newSize);
				resize(newSize);
			}

			*m_current = c;
			++m_current;			
		}

		inline void resize(int newsize)
		{
			newsize = std::max(newsize, m_minimalbuffsize);
			char* newbuff = new char[newsize];
			int toCopy = std::min(newsize, (int)(m_current-m_first));

			std::memset(newbuff, ' ', newsize);
			std::memcpy(newbuff, m_first, toCopy);

			delete[] m_first;

			m_first = newbuff;
			m_current = m_first + toCopy;
			//*m_current = ' ';
			m_last = m_first + newsize;
			m_buffsize = newsize;
		}

		inline void grow(int minSize)
		{
			int newSize = m_last-m_first+1;
			newSize = next_power_of_two(newSize);
			resize(newSize);
		}

		inline status getStatus()
		{
			return m_status;
		}

		inline void resize()
		{
			int size = next_power_of_two(m_buffsize);
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
			return m_first[i];
		}

		inline stream& operator=(const bfu::stream& src)
		{
			m_buffsize = src.m_buffsize;
			resize(m_buffsize);

			std::memcpy(m_first, src.m_first, m_buffsize);

			const int offset = src.m_current - src.m_first;

			m_current = m_first + offset;

			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const bfu::stream& strm);
	};

	std::ostream& operator<<(std::ostream& os, const bfu::stream& strm);



}

using bfu::operator<<;


#endif