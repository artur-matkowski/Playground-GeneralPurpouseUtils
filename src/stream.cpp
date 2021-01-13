#include "stream.hpp"
#include <algorithm>

namespace bfu{

	stream::stream()
	    :m_buffsize( sizeof(initialbuff) )
	    ,m_first(initialbuff)
	    ,m_last(m_first+m_buffsize-1)
	    ,m_writeCursor(0)
	    ,m_readCursor(0)
	{
		m_buffsize = sizeof(initialbuff);
		m_last = m_first+m_buffsize-1;
	    m_writeCursor = m_first;
	    m_readCursor = m_first;
		std::memset(initialbuff, 0, m_buffsize);
	}

	stream::stream(const char* input, int size)
	    :m_buffsize( sizeof(initialbuff) )
	    ,m_first(initialbuff)
	    ,m_last(m_first+m_buffsize-1)
	    ,m_writeCursor(m_first+std::max( size, (int)strlen(input)))
	    ,m_readCursor(m_first)
	{
		if(size < sizeof(initialbuff))
		{
			std::memcpy(m_first, input, m_buffsize);
		}
		else
		{
			resize(size);
			std::memcpy(m_first, input, m_buffsize);			
		}
	}

	stream::stream(const stream& input)
	    :m_buffsize( input.m_buffsize )
	    ,m_first(initialbuff)
	    ,m_last(m_first+m_buffsize-1)
	    ,m_writeCursor(m_first)
	    ,m_readCursor(m_first)
	{
		std::memcpy(m_first, input.m_first, m_buffsize);
	}
/*
	stream::stream(const int size)
	    :m_buffsize( sizeof(initialbuff) )
	    ,m_first(initialbuff)
	    ,m_last(m_first+m_buffsize-1)
	    ,m_writeCursor(m_first)
	    ,m_readCursor(m_first)
	{
		if(size >= sizeof(initialbuff))
		{
			resize(size);
		}
		std::memset(m_first, 0, m_buffsize);
	}*/

	stream::~stream()
	{
		if(m_first!=initialbuff)
			delete[] m_first;
	}

	std::ostream& operator<<(std::ostream& os, const stream& strm)
	{
	    os << strm.m_first << std::flush;
	    return os;
	}

}