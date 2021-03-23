#ifndef _H_stream
#define _H_stream
#include <cstdarg>
#include <cstring>
#include <string>
#include <iostream>
#include <cinttypes>
#include "CustomAllocator.hpp"
//#include "log.hpp"
#include <iostream>
	
namespace bfu{
	
	typedef std::basic_string<char, std::char_traits<char>, custom_allocator<char> > t_string;

	class string: public t_string
	{
	public:
		using t_string::t_string;
		string(const std::string& cp, MemBlockBase* memBlock = StdAllocatorMemBlock::GetMemBlock() )
			:t_string(cp.c_str(), memBlock)
		{}
		operator std::string() const
	    {
	        return std::string(this->c_str());
	    }
	};

	class stream
	{
	protected:
		char tmpBuff[1];
		//lazy alocation if buffsize = 0 and not constructing with size
		char* m_begin = 0;
		char* m_end = 0;
		char* m_writeCursor = 0;
		char* m_readCursor = 0;
		bool using_prealocated;
		MemBlockBase* m_mBlock = 0;


		int next_power_of_two(int n) const
		{
		    int i = 0;
		    ++n;
		    for (--n; n > 0; n >>= 1) {
		        i++;
		    }
		    return 1 << i;
		}

	public:

		stream( MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() );
	    stream(char* prealocatedBuff, int size, MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() );
	    stream(const char* prealocatedBuff, MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock()  );
	    stream(const stream& input);
	    //stream(const int size);

	    ~stream();

	    inline void assignMemBlock(MemBlockBase* mBlock)
	    {
	    	if(using_prealocated)
	    	{
	    		m_mBlock = mBlock;
	    		return;
	    	}

	    	int newsize = size();
			char* newbuff = (char*)mBlock->allocate( newsize, sizeof(char), alignof(char) );
			int toCopy = m_writeCursor==0 && m_begin!=0 ? strlen(m_begin) : std::min(newsize, (int)(m_writeCursor-m_begin));

			std::memset(newbuff, '\0', newsize);
			std::memcpy(newbuff, m_begin, toCopy);

			if(m_begin!=0)
				m_mBlock->deallocate( m_begin, (size_t)m_end-(size_t)m_begin );
	    	m_mBlock = mBlock;

			int readOffset = m_readCursor - m_begin;

			m_begin = newbuff;
			m_writeCursor = m_begin + toCopy;

			m_readCursor = readOffset + m_begin; 
			m_end = m_begin + newsize;
			using_prealocated = false;
			
			*(m_end-1) = '\0';
	    }

	    inline int size() const
	    {
	    	if(m_writeCursor!=0)
	    		return (int)(m_writeCursor-m_begin);
	    	else
	    		return strlen(m_begin);
	    }

	    inline int capacity() const
	    {
	    	return (int) (m_end-m_begin)-2;
	    }

		inline void clear()
		{
			if(m_writeCursor!=0)
				m_writeCursor = m_begin;
			m_readCursor = m_begin;
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
			while( m_readCursor!=m_end && !isOneOf(str) ) 
			{
				++m_readCursor;
			}
		}

		inline void skipTo(char c)
		{
			while( m_readCursor!=m_end && *m_readCursor!=c ) 
			{
				++m_readCursor;
			}
		}
		inline void skip(int c)
		{
			if( (m_readCursor + c) > m_end )
			{
				int newSize = next_power_of_two(size()+c+2);
				resize(newSize);
			}

			m_readCursor += c;
		}

		inline bfu::string str() const
		{
			if(m_writeCursor!=0)
				return bfu::string(m_begin,m_writeCursor);
			else
				return bfu::string(m_begin);
		}

		inline char* c_str() const
		{
			if(m_writeCursor!=0)
				*m_writeCursor='\0';

			return m_begin;
		}

		inline void SetCursonPos(int pos)
		{
			if(pos > capacity())
			{
				int t = next_power_of_two(pos);
				resize(t);
			}

			m_readCursor = m_begin + pos;
		}

		inline void OverrideWriteCursorPos(int pos)
		{
			if(pos > capacity())
			{
				int t = next_power_of_two(pos);
				resize(t);
			}


			if(m_writeCursor!=0)
				m_writeCursor = m_begin + pos;
		}

		inline void OverrideReadCursorPos(int pos)
		{
			if(pos > capacity())
			{
				int t = next_power_of_two(pos);
				resize(t);
			}

			m_readCursor = m_begin + pos;
		}

		inline void sprintf(const char* str, ...)
		{
			if(m_writeCursor==0)
				return;

			va_list args1;
			va_start(args1, str);
			va_list args2;
    		va_copy(args2, args1);

			int t = vsnprintf(m_writeCursor, m_end-m_writeCursor, str, args1);

			va_end(args1);

			if(t >= m_end-m_writeCursor)
			{
				t = next_power_of_two(m_writeCursor-m_begin+t+2);
				resize(t);

				t = vsnprintf(m_writeCursor, m_end-m_writeCursor, str, args2);

			}
    		va_end(args2);

			m_writeCursor += t;
			put('\0');
		}

		inline char peak(int offset = 0) const
		{
			return m_readCursor[offset];
		}

		inline void put(char c)
		{
			if(m_writeCursor==0) 
				return;

			if( m_writeCursor == m_end )
			{
				int newSize = m_end-m_begin+1;
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
			if(newsize < capacity())
				return;

			newsize =  newsize+1;
			char* newbuff = (char*)m_mBlock->allocate( newsize, sizeof(char), alignof(char) );
			int toCopy = m_writeCursor==0 && m_begin!=0 ? strlen(m_begin) : std::min(newsize, (int)(m_writeCursor-m_begin));

			std::memset(newbuff, '\0', newsize);
			std::memcpy(newbuff, m_begin, toCopy);

			if(m_begin!=0 && !using_prealocated)
				m_mBlock->deallocate( m_begin, (size_t)m_end-(size_t)m_begin );

			int readOffset = m_readCursor - m_begin;

			m_begin = newbuff;
			m_writeCursor = m_begin + toCopy;

			m_readCursor = readOffset + m_begin; 
			m_end = m_begin + newsize;
			using_prealocated = false;
			
			*(m_end-1) = '\0';
		}

		inline void grow(int minSize)
		{
			int newSize = m_end-m_begin+1;
			newSize = next_power_of_two(newSize);
			resize(newSize);
		}

		inline void resize()
		{
			int size = next_power_of_two( capacity() + 2);
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

		stream& operator<<(const double& val)
		{
			this->sprintf("%f", val);

			return *this;
		}

		stream& operator<<(const bool& val)
		{
			this->sprintf("%d", val);

			return *this;
		}

		stream& operator<<(const bfu::string& val)
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
			return m_begin[i];
		}

		inline stream& operator=(const bfu::stream& src)
		{
			if(src.capacity() == 0)
				return *this;

			resize( src.capacity() );

			std::memcpy(m_begin, src.m_begin, capacity()+1);

			const int writeOffset = src.m_writeCursor - src.m_begin;
			const int readOffset = src.m_readCursor - src.m_begin;

			m_writeCursor = m_begin + (src.m_writeCursor==0 ? src.size() : writeOffset);
			m_readCursor = m_begin + readOffset;

			return *this;
		}

		inline bfu::stream& operator<<(const bfu::stream& src)
		{
			this->sprintf( src.c_str() );
			return *this;
		}

		bool operator==(const bfu::stream& other) const
		{
			return strncmp(c_str(), other.c_str(), size() )==0;
		}

		friend std::ostream& operator<<(std::ostream& os, const bfu::stream& strm);
		friend std::less<bfu::stream>;
	};

	std::ostream& operator<<(std::ostream& os, const bfu::stream& strm);



}

namespace std {
	template<>
	struct less<bfu::stream>
	{
		bool operator()(const bfu::stream& k1, const bfu::stream& k2) const
		{
			const char* str1 = k1.c_str();
			const char* str2 = k2.c_str();

			int ret = std::strcmp(str1, str2);
			return ret < 0;
		}
	};
}

using bfu::operator<<;


#endif