#include "stream.hpp"
#include <algorithm>

namespace bfu{

	stream::stream()
	    :first(0)
	    ,last(0)
	    ,current(0)
	{
		if(buffsize!=0)
		{
			first = new char[buffsize];
		    last = first+buffsize-1;
		    current = first;
		}
	}

	stream::stream(const char* input, int size)
	    :buffsize( std::max( {size, (int)strlen(input), minimalbuffsize} ) )
	    ,first(new char[buffsize])
	    ,last(first+buffsize-1)
	    ,current(first)
	{
		std::memcpy(first, input, buffsize);
	}

	stream::stream(const stream& input)
	    :buffsize( input.buffsize )
	    ,first(new char[buffsize])
	    ,last(first+buffsize-1)
	    ,current(first)
	{
		std::memcpy(first, input.first, buffsize);
	}

	stream::~stream()
	{
		delete[] first;
	}

	std::ostream& operator<<(std::ostream& os, const stream& strm)
	{
		strm.current[0] = '\0';
	    os << strm.first << std::flush;
	    return os;
	}

}