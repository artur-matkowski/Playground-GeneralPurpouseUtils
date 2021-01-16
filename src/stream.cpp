#include "stream.hpp"
#include <algorithm>

namespace bfu{
/*
	stream::stream()
	    :m_buffsize(0)
	    ,m_first(0)
	    ,m_last(0)
	    ,m_writeCursor(0)
	    ,m_readCursor(0)
	    ,using_prealocated(false)
	{
	}
*/
	stream::stream(char* prealocatedBuff, int buffSize, std::allocator<char> alloc)
	    :m_buffsize( buffSize )
	    ,m_first(prealocatedBuff)
	    ,m_last(m_first+m_buffsize-1)
	    ,m_writeCursor(m_first)
	    ,m_readCursor(m_first)
	    ,using_prealocated(true)
	    ,m_alloc(alloc)
	{
	}

	stream::stream(const stream& input)
	    :m_buffsize( 0 )
	    ,m_first(0)
	    ,m_last(0)
	    ,m_writeCursor(0)
	    ,m_readCursor(0)
	    ,using_prealocated(false)
	    ,m_alloc(input.m_alloc)
	{
		resize( input.m_buffsize );

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
		if(m_first!=0 && !using_prealocated)
			m_alloc.deallocate( m_first, (size_t)m_last-(size_t)m_first );
	}

	std::ostream& operator<<(std::ostream& os, const stream& strm)
	{
	    os << strm.m_first << std::flush;
	    return os;
	}

}