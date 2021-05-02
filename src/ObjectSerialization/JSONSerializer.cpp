#include "JSONSerializer.hpp"
#include "ObjectSerializableClassBase.hpp"

namespace bfu
{

#define GENERAL_VECTOR_SERIALIZE_BODY \
		this->sprintf("["); \
 		 \
		if( data->begin() != data->end() ) \
		{ \
			for(auto it = data->begin(); ; ) \
			{ \
				this->Serialize(&*it); \
 		 \
				++it; \
 		 \
				if( it != data->end() ) \
				{ \
					this->sprintf(", "); \
				} \
				else \
				{ \
					break; \
				} \
			} \
		} \
		 \
		this->sprintf("]");


#define GENERAL_VECTOR_DESERIALIZE_BODY(T) \
		data->clear(); \
 		 \
		this->skipTo('['); \
		this->skip( 1 ); \
 		 \
		while(this->peak() != ']') \
		{ \
			T cache; \
 		 \
			this->Deserialize( &cache ); \
 		 \
			data->emplace_back( cache ); \
		}


	JSONSerializer::JSONSerializer(bfu::stream&& other)
		:bfu::stream(std::move(other))
	{}


	char* JSONSerializer::data() 
	{
		return this->c_str();
	}
	int JSONSerializer::size() 
	{
		return bfu::stream::size();
	}
	void JSONSerializer::clear()
	{
		bfu::stream::clear();
	}
	void JSONSerializer::assignData(char* data, uint32_t size)
	{
		this->assign(data, size);
	}

	void JSONSerializer::Serialize( SerializableClassInterface* data )
	{
		data->PreSerializationCallback();
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
		data->PostSerializationCallback();
	}
	
	void JSONSerializer::Serialize( SerializableVector<SerializableClassInterface>* data )
	{
		this->sprintf("["); 
 		 
		if( data->begin() != data->end() ) 
		{ 
			for(auto it = data->begin(); ; ) 
			{ 
				this->Serialize(*it); 
 		 
				++it; 
 		 
				if( it != data->end() ) 
				{ 
					this->sprintf(", "); 
				} 
				else 
				{ 
					break; 
				} 
			} 
		} 
		 
		this->sprintf("]");
	}

	void JSONSerializer::Serialize( float* data )
	{
   		this->sprintf("%f", *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<float>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}

	void JSONSerializer::Serialize( bool* data )
	{
		this->sprintf("%s", (*data ? "true" : "false") );
	}
	
	void JSONSerializer::Serialize( SerializableVector<bool>* data )
	{
		this->sprintf("[");

		for(int i=0; i<data->size(); )
		{
			bool tmp = (*data)[i];
			this->Serialize( &tmp );

			++i;

			if( i != data->size() )
			{
				this->sprintf(", ");
			}
			else
			{
				break;
			}
		}
	

		this->sprintf("]");
	}

	void JSONSerializer::Serialize( stream* data )
	{
		int buffsize = data->size();

		put('\"');

		for(int i=0; i<buffsize; ++i)
		{
			if( (*data)[i] == '\"' )
			{
				put('\\');
			}
			put((*data)[i]);
		}

		put('\"');
	}
	
	void JSONSerializer::Serialize( SerializableVector<stream>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}

	void JSONSerializer::Serialize( string* data )
	{
		int buffsize = (*data).size();

		put('\"');

		for(int i=0; i<buffsize; ++i)
		{
			if( (*data)[i] == '\"' )
			{
				put('\\');
			}
			put((*data)[i]);
		}

		put('\"');
	}
	
	void JSONSerializer::Serialize( SerializableVector<string>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}
		

	void JSONSerializer::Serialize( uint8_t* data )
	{
		this->sprintf("%" PRIu8, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<uint8_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}

	void JSONSerializer::Serialize( uint16_t* data )
	{
		this->sprintf("%" PRIu16, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<uint16_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}

	void JSONSerializer::Serialize( uint32_t* data )
	{
		this->sprintf("%" PRIu32, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<uint32_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}

	void JSONSerializer::Serialize( uint64_t* data )
	{
		this->sprintf("%" PRIu64, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<uint64_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}


	void JSONSerializer::Serialize( int8_t* data )
	{
		this->sprintf("%" PRId8, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<int8_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}

	void JSONSerializer::Serialize( int16_t* data )
	{
		this->sprintf("%" PRId16, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<int16_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}

	void JSONSerializer::Serialize( int32_t* data )
	{
		this->sprintf("%" PRId32, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<int32_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}

	void JSONSerializer::Serialize( int64_t* data )
	{
		this->sprintf("%" PRId64, *data);
	}
	
	void JSONSerializer::Serialize( SerializableVector<int64_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY;
	}





	//---------------





	void JSONSerializer::Deserialize( SerializableClassInterface* data )
	{
		data->PreDeserializationCallback();
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

			ClassInfo* tmp = (*classInfo)[ token.c_str() ];

			if( tmp != nullptr )
				tmp->jsonDeserializeFunc( this,  (void*) ((size_t)data + tmp->offset) );

			this->skipToOneOf("\"}");

		}
		this->skip(1);
		data->PostDeserializationCallback();
	}
	void JSONSerializer::Deserialize( SerializableVector<SerializableClassInterface>* data )
	{
		for(int i=0; i<data->size(); ++i)
		{
			(*data)[i].Dispouse();
		}
		data->clear(); 

		this->skipTo('['); 
		this->skip( 1 ); 
 		 
		while(this->peak() != ']') 
		{ 
			SerializableClassInterface* cache = data->allocateAndInit( data->mBlock() );
 		 
			this->Deserialize( cache ); 
 		 
			data->emplace_back( cache ); 
		}
	}

	void JSONSerializer::Deserialize( float* data )
	{
		skipToOneOf("-.0123456789");

		m_readCursor += sscanf(m_readCursor, "%f", data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<float>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(float);
	}

	void JSONSerializer::Deserialize( bool* data )
	{
		skipToOneOf("tf");

		if( 0==strncmp(m_readCursor, "true", 4) )
		{
			*data = true;
		}
		else if( 0==strncmp(m_readCursor, "false", 5) )
		{
			*data = false;
		}

		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<bool>* data )
	{	
		data->clear();

		this->skipTo('[');
		this->skip( 1 );

		while(this->peak() != ']')
		{
			bool cache;

			this->Deserialize( &cache );

			data->emplace_back( cache );
		}
	}

	void JSONSerializer::Deserialize( stream* data )
	{
		skipTo('\"');

		char* skipper = m_readCursor+1;

		while( m_readCursor!=m_end )
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
	void JSONSerializer::Deserialize( SerializableVector<stream>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(stream);
	}

	void JSONSerializer::Deserialize( string* data )
	{
		skipTo('\"');

		char* skipper = m_readCursor+1;

		while( m_readCursor!=m_end )
		{
			if( skipper[0] == '\"' && skipper[-1] != '\\' )
			{
				break;
			}

			++skipper;
		}

		int size = skipper-m_readCursor+1;
		//char* buff = new char[size];
		char* buff = (char*)m_mBlock->allocate(size, sizeof(char), alignof(char));

		int buffC = 0;

		for(char* cursor = m_readCursor+1; m_readCursor<skipper; ++cursor)
		{
			if( cursor[0]=='\\' && cursor[1]=='\"' )
			{
				++cursor;
			}
			//yes looks like shit, but this is never going to be first element of array anyway
			else if( cursor[0]=='\"' && cursor[-1]!='\\' )
			{
				buff[buffC] = '\0';
				break;
			}
			buff[buffC] = *cursor;

			++buffC;
		}

		(*data).assign(buff);

		//delete buff;
		m_mBlock->deallocate(buff, size * sizeof(char));

		m_readCursor = skipper;
		skipToOneOf(":,]}");

	}
	void JSONSerializer::Deserialize( SerializableVector<string>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(string);
	}

	void JSONSerializer::Deserialize( uint8_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNu8, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<uint8_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(uint8_t);
	}

	void JSONSerializer::Deserialize( uint16_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNu16, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<uint16_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(uint16_t);
	}

	void JSONSerializer::Deserialize( uint32_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNu32, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<uint32_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(uint32_t);
	}

	void JSONSerializer::Deserialize( uint64_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNu64, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<uint64_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(uint64_t);
	}


	void JSONSerializer::Deserialize( int8_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNd8, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<int8_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(int8_t);
	}

	void JSONSerializer::Deserialize( int16_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNd16, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<int16_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(int16_t);
	}

	void JSONSerializer::Deserialize( int32_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNd32, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<int32_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(int32_t);
	}

	void JSONSerializer::Deserialize( int64_t* data )
	{
		skipToOneOf("-0123456789");

		m_readCursor += sscanf(m_readCursor, "%" SCNd64, data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( SerializableVector<int64_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY(int64_t);
	}
}