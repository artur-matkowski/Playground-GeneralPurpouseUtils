#include "JSONSerializer.hpp"
#include "ObjectSerializableClassBase.hpp"

namespace bfu2
{
	void JSONSerializer::Serialize( SerializableClassInterface* data )
	{
		this->sprintf("{");
		ClassInfo* it = data->GetFirstClassInfo();

		for(; it != nullptr; )
		{
			this->sprintf("\n\"%s\": ", it->name );

			it->jsonSerializeFunc(this, (void*) ((size_t)data + it->offset) );

			it = it->next;

			if( it != nullptr )
			{
				this->sprintf(", ");
			}
		}

		this->sprintf("\n}");
	}
	
	void JSONSerializer::Serialize( SerializableVector<SerializableClassInterface*>* data )
	{

	}

	void JSONSerializer::Serialize( float* data )
	{
   		this->sprintf("%f", *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<float>* data )
	{

	}

	void JSONSerializer::Serialize( double* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<double>* data )
	{

	}

	void JSONSerializer::Serialize( bool* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<bool>* data )
	{

	}

	void JSONSerializer::Serialize( char* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<char>* data )
	{

	}

	void JSONSerializer::Serialize( stream* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<stream>* data )
	{

	}

	void JSONSerializer::Serialize( string* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<string>* data )
	{

	}
		

	void JSONSerializer::Serialize( uint8_t* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<uint8_t>* data )
	{

	}

	void JSONSerializer::Serialize( uint16_t* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<uint16_t>* data )
	{

	}

	void JSONSerializer::Serialize( uint32_t* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<uint32_t>* data )
	{

	}

	void JSONSerializer::Serialize( uint64_t* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<uint64_t>* data )
	{

	}


	void JSONSerializer::Serialize( int8_t* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<int8_t>* data )
	{

	}

	void JSONSerializer::Serialize( int16_t* data )
	{

	}
	
	void JSONSerializer::Serialize( SerializableVector<int16_t>* data )
	{

	}

	void JSONSerializer::Serialize( int32_t* data )
	{
		this->sprintf("%" PRId32, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<int32_t>* data )
	{

	}

	void JSONSerializer::Serialize( int64_t* data )
	{
		this->sprintf("%" PRId64, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<int64_t>* data )
	{

	}





	//---------------





	void JSONSerializer::Deserialize( SerializableClassInterface* data )
	{
		char buff[1024] = {'0'};
    	bfu::stream token(buff, 1024 /*, mBlock*/);
		ClassInfo* classInfo = data->GetFirstClassInfo();


		this->skipTo('{');
		this->skip( 1 );

		if(this->peak() == '\n')
			this->skip( 1 );

		while( this->peak() != '}' )
		{
			token.clear();

			Deserialize( &token );

			(*classInfo)[ token.c_str() ]->jsonDeserializeFunc( this,  (void*) ((size_t)data + classInfo->offset) );

			this->skipToOneOf("\"}");

		}
		this->skip(1);
	}
	void JSONSerializer::Deserialize( SerializableVector<SerializableClassInterface*>* data )
	{

	}

	void JSONSerializer::Deserialize( float* data )
	{
		skipToOneOf("-.0123456789");

		m_readCursor += sscanf(m_readCursor, "%f", data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<float>* data )
	{

	}

	void JSONSerializer::Deserialize( double* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<double>* data )
	{

	}

	void JSONSerializer::Deserialize( bool* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<bool>* data )
	{

	}

	void JSONSerializer::Deserialize( char* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<char>* data )
	{

	}

	void JSONSerializer::Deserialize( bfu::stream* data )
	{
		skipTo('\"');

		char* skipper = m_readCursor+1;

		while( m_readCursor!=m_last )
		{
			if( skipper[0] == '\"' && skipper[-1] != '\\' )
			{
				break;
			}

			++skipper;
		}

		int size = skipper-m_readCursor+1;

		data->grow( size );

		for(char* cursor = m_readCursor+1; cursor<skipper; ++cursor)
		{
			if( cursor[0]=='\\' && cursor[1]=='\"' )
			{
				++cursor;
			}
			else if( cursor[0]=='\"' && cursor[-1]!='\\' )
			{
				data->put( '\0' );
				break;
			}
			data->put( *cursor );
		}


		m_readCursor = skipper;
		skipToOneOf(":,]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<bfu::stream>* data )
	{

	}

	void JSONSerializer::Deserialize( bfu::string* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<bfu::string>* data )
	{

	}

	void JSONSerializer::Deserialize( uint8_t* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<uint8_t>* data )
	{

	}

	void JSONSerializer::Deserialize( uint16_t* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<uint16_t>* data )
	{

	}

	void JSONSerializer::Deserialize( uint32_t* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<uint32_t>* data )
	{

	}

	void JSONSerializer::Deserialize( uint64_t* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<uint64_t>* data )
	{

	}


	void JSONSerializer::Deserialize( int8_t* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<int8_t>* data )
	{

	}

	void JSONSerializer::Deserialize( int16_t* data )
	{

	}
	void JSONSerializer::Deserialize( SerializableVector<int16_t>* data )
	{

	}

	void JSONSerializer::Deserialize( int32_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNd32, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<int32_t>* data )
	{

	}

	void JSONSerializer::Deserialize( int64_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNd64, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<int64_t>* data )
	{

	}
}