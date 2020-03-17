#include "SerializableClassBase.hpp"
#include "JSONStream.hpp"



namespace bfu{

	void SerializableClassBase::Serialize(JSONStream& stream)
	{
		stream.sprintf("{");

		auto last = m_membersMap.end();

		for(auto it = m_membersMap.begin(); it != last; )
		{
			stream.sprintf("\n\"%s\": ", it->first );

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
		stream.skipTo('{');
		stream.skip( 1 );

		std::string token;

		while( stream.peak() != '}' )
		{
			stream.Deserialize( token );

			m_membersMap[ token.c_str() ]->Deserialize( stream );

			stream.skipToOneOf("\"}");
		}
	}

	void SerializableClassBase::print()
	{
		auto last = m_membersMap.end();

		for(auto it = m_membersMap.begin(); it != last; )
		{
			std::cout << "\n\tKEY: " << it->first;

			std::cout  << "\n\tVALUE: " << it->second;
		}

	    return;
	}

}