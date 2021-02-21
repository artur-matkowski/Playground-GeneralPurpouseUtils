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
	stream::stream(char* prealocatedBuff, int buffSize, MemBlockBase* mBlock )
	    :m_buffsize( buffSize )
	    ,m_first(prealocatedBuff)
	    ,m_last(m_first+m_buffsize-1)
	    ,m_writeCursor(m_first)
	    ,m_readCursor(m_first)
	    ,using_prealocated(true)
	    ,m_mBlock(mBlock)
	{
	}

	stream::stream(const stream& input)
	    :m_buffsize( 0 )
	    ,m_first(0)
	    ,m_last(0)
	    ,m_writeCursor(0)
	    ,m_readCursor(0)
	    ,using_prealocated(false)
	    ,m_mBlock(input.m_mBlock)
	{
		this->operator=(input);
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
			m_mBlock->deallocate( m_first, (size_t)m_last-(size_t)m_first );
	}

	std::ostream& operator<<(std::ostream& os, const stream& strm)
	{
	    os << strm.m_first << std::flush;
	    return os;
	}

}