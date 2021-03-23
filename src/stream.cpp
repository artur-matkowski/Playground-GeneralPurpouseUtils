#include "stream.hpp"
#include <algorithm>

namespace bfu{

	stream::stream(MemBlockBase* mBlock)
	    :m_begin(tmpBuff)
	    ,m_end(m_begin+1)
	    ,m_writeCursor(m_begin)
	    ,m_readCursor(m_begin)
	    ,using_prealocated(true)
	    ,m_mBlock(mBlock)
	{
	}

	stream::stream(char* prealocatedBuff, int buffSize, MemBlockBase* mBlock )
	    :m_begin(prealocatedBuff)
	    ,m_end(m_begin+buffSize)
	    ,m_writeCursor(m_begin)
	    ,m_readCursor(m_begin)
	    ,using_prealocated(true)
	    ,m_mBlock(mBlock)
	{
	}

	stream::stream(const char* prealocatedBuff, MemBlockBase* mBlock )
	    :m_begin((char*)prealocatedBuff)
	    ,m_end(m_begin+strlen(prealocatedBuff))
	    ,m_writeCursor(0)
	    ,m_readCursor(m_begin)
	    ,using_prealocated(true)
	    ,m_mBlock(mBlock)
	{
	}

	stream::stream(const stream& input)
	    :m_begin(0)
	    ,m_end(0)
	    ,m_writeCursor(0)
	    ,m_readCursor(0)
	    ,using_prealocated(false)
	    ,m_mBlock(input.m_mBlock)
	{
		resize( input.capacity() );
		this->operator=(input);
	}
/*
	stream::stream(const int size)
	    :m_buffsize( sizeof(initialbuff) )
	    ,m_begin(initialbuff)
	    ,m_end(m_begin+m_buffsize-1)
	    ,m_writeCursor(m_begin)
	    ,m_readCursor(m_begin)
	{
		if(size >= sizeof(initialbuff))
		{
			resize(size);
		}
		std::memset(m_begin, 0, m_buffsize);
	}*/

	stream::~stream()
	{
		if(m_begin!=0 && !using_prealocated)
			m_mBlock->deallocate( m_begin, capacity()+1 );
	}

	std::ostream& operator<<(std::ostream& os, const stream& strm)
	{
	    os << strm.m_begin << std::flush;
	    return os;
	}

}