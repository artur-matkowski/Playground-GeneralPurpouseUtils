#include "SerializableClassBase.hpp"
#include "JSONStream.hpp"



namespace bfu{
	SerializableClassBase::~SerializableClassBase()
	{
	}
	void SerializableClassBase::Serialize(JSONStream& stream)
	{
		stream.sprintf("{");

		auto last = m_membersMap.end();

		for(auto it = m_membersMap.begin(); it != last; )
		{
			stream.sprintf("\n\"%s\": ", it->first.c_str() );

			it->second->Serialize( stream );

			++it;

			if( it != last )
			{
				stream.sprintf(", ");
			}
		}

		stream.sprintf("\n}");
	}

	void SerializableClassBase::Deserialize(JSONStream& stream)
	{
    	char buff[1024] = {'0'};
    	bfu::stream token(buff, 1024, m_mBlock);


		stream.skipTo('{');
		stream.skip( 1 );

		if(stream.peak() == '\n')
			stream.skip( 1 );

		while( stream.peak() != '}' )
		{
			token.clear();

			stream.Deserialize( token );

			auto &tmp = m_membersMap[ token ];

			tmp->Deserialize( stream );

			stream.skipToOneOf("\"}");

		}
		stream.skip(1);
	}


	void SerializableClassBase::print()
	{
		auto last = m_membersMap.end();

		for(auto it = m_membersMap.begin(); it != last; ++it)
		{
			std::cout << "\n\tKEY: " << it->first;

			std::cout  << "\n\tVALUE: " << it->second;
		}

	    return;
	}

}