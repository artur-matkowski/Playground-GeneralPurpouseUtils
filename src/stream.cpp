#include "stream.hpp"
#include <algorithm>

namespace bfu{

	stream::stream()
	    :m_first(0)
	    ,m_last(0)
	    ,m_current(0)
	{
		if(m_buffsize!=0)
		{
			m_first = new char[m_buffsize];
		    m_last = m_first+m_buffsize-1;
		    m_current = m_first;
			std::memset(m_first, ' ', m_buffsize);
		}
	}

	stream::stream(const char* input, int size)
	    :m_buffsize( std::max( {size, (int)strlen(input), m_minimalbuffsize} ) )
	    ,m_first(new char[m_buffsize])
	    ,m_last(m_first+m_buffsize)
	    ,m_current(m_first)
	{
		std::memcpy(m_first, input, m_buffsize);
	}

	stream::stream(const stream& input)
	    :m_buffsize( input.m_buffsize )
	    ,m_first(new char[m_buffsize])
	    ,m_last(m_first+m_buffsize)
	    ,m_current(m_first)
	{
		std::memcpy(m_first, input.m_first, m_buffsize);
	}

	stream::stream(const int size)
	    :m_buffsize( std::max( {size, m_minimalbuffsize} )  )
	    ,m_first(new char[m_buffsize])
	    ,m_last(m_first+m_buffsize)
	    ,m_current(m_first)
	{
		std::memset(m_first, ' ', m_buffsize);
	}

	stream::~stream()
	{
		delete[] m_first;
	}

	std::ostream& operator<<(std::ostream& os, const stream& strm)
	{
	    os << strm.m_first << std::flush;
	    return os;
	}

}