#ifndef _H_stream
#define _H_stream
#include <cstdarg>
#include <cstring>
#include <string>
#include <iostream>
#include <cinttypes>
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
		char* m_writeCursor = 0;
		char* m_readCursor = 0;


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
	    	return (int)(m_writeCursor-m_first);
	    }

	    inline int capacity() const
	    {
	    	return (int) (m_last-m_first);
	    }

		inline void clear()
		{
			m_writeCursor = m_first;
			m_readCursor = m_first;
		}

		inline bool isOneOf(const char* str) const
		{
			int size = strlen(str);

			for(int i=0; i<size; ++i)
			{
				if(*m_readCursor==str[i])
				{
					return true;
				}
			}
			return false;
		}

		inline void skipToOneOf(const char* str)
		{
			while( m_readCursor!=m_last && !isOneOf(str) ) 
			{
				++m_readCursor;
			}
		}

		inline void skipTo(char c)
		{
			while( m_readCursor!=m_last && *m_readCursor!=c ) 
			{
				++m_readCursor;
			}
		}
		inline void skip(int c)
		{
			if( (m_readCursor + c) > m_last )
			{
				int newSize = next_power_of_two(size()+c+2);
				resize(newSize);
			}

			m_readCursor += c;
		}

		inline std::string str() const
		{
			return std::string(m_first,m_writeCursor);
		}

		inline char* c_str()
		{
			put( '\0' );
			return m_first;
		}

		inline void SetCursonPos(int pos)
		{
			if(pos > m_buffsize)
			{
				int t = next_power_of_two(pos);
				resize(t);
			}

			m_readCursor = m_first + pos;
		}

		inline void OverrideWriteCursorPos(int pos)
		{
			if(pos > m_buffsize)
			{
				int t = next_power_of_two(pos);
				resize(t);
			}

			m_writeCursor = m_first + pos;
		}

		inline void OverrideReadCursorPos(int pos)
		{
			if(pos > m_buffsize)
			{
				int t = next_power_of_two(pos);
				resize(t);
			}

			m_readCursor = m_first + pos;
		}

		inline void sprintf(const char* str, ...)
		{
			va_list args1;
			va_start(args1, str);
			va_list args2;
    		va_copy(args2, args1);

			int t = vsnprintf(m_writeCursor, m_last-m_writeCursor, str, args1);

			va_end(args1);

			if(t >= m_last-m_writeCursor)
			{
				t = next_power_of_two(m_writeCursor-m_first+t+2);
				resize(t);

				t = vsnprintf(m_writeCursor, m_last-m_writeCursor, str, args2);

			}
    		va_end(args2);

			m_writeCursor += t;
		}

		inline char peak(int offset = 0) const
		{
			return m_readCursor[offset];
		}

		inline void put(char c)
		{
			if( m_writeCursor == m_last )
			{
				int newSize = m_last-m_first+1;
				newSize = next_power_of_two(newSize);
				resize(newSize);
			}

			*m_writeCursor = c;

			if( c != '\0' )
			{
				++m_writeCursor;
			}		
		}

		inline void resize(int newsize)
		{
			newsize = std::max(newsize+1, m_minimalbuffsize);
			char* newbuff = new char[newsize];
			int toCopy = std::min(newsize, (int)(m_writeCursor-m_first));

			std::memset(newbuff, '\0', newsize);
			std::memcpy(newbuff, m_first, toCopy);

			if(m_first!=0)
				delete[] m_first;

			int readOffset = m_readCursor - m_first;

			m_first = newbuff;
			m_writeCursor = m_first + toCopy;

			m_readCursor = readOffset + m_first; 
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

		stream& operator<<(const unsigned char* val)
		{
			this->sprintf("%s", val);

			return *this;
		}

		stream& operator<<(const int64_t& val)
		{
			this->sprintf("%" PRId64, val);
			return *this;
		}
		stream& operator<<(const int32_t& val)
		{
			this->sprintf("%" PRId32, val);
			return *this;
		}
		stream& operator<<(const int16_t& val)
		{
			this->sprintf("%" PRId16, val);
			return *this;
		}
		stream& operator<<(const int8_t& val)
		{
			this->sprintf("%" PRId8, val);
			return *this;
		}

		stream& operator<<(const uint64_t& val)
		{
			this->sprintf("%" PRIu64, val);
			return *this;
		}
		stream& operator<<(const uint32_t& val)
		{
			this->sprintf("%" PRIu32, val);
			return *this;
		}
		stream& operator<<(const uint16_t& val)
		{
			this->sprintf("%" PRIu16, val);
			return *this;
		}
		stream& operator<<(const uint8_t& val)
		{
			this->sprintf("%" PRIu8, val);
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
			if(src.m_buffsize == 0)
				return *this;

			m_buffsize = src.m_buffsize;
			resize(m_buffsize);

			std::memcpy(m_first, src.m_first, m_buffsize);

			const int writeOffset = src.m_writeCursor - src.m_first;
			const int readOffset = src.m_writeCursor - src.m_first;

			m_writeCursor = m_first + writeOffset;
			m_readCursor = m_first + readOffset;

			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const bfu::stream& strm);
	};

	std::ostream& operator<<(std::ostream& os, const bfu::stream& strm);



}

using bfu::operator<<;


#endif