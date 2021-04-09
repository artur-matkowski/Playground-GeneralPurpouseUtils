#include "BinarySerializer.hpp"

namespace bfu
{
	int next_power_of_two(int n)
	{
	    int i = 0;
	    ++n;
	    for (--n; n > 0; n >>= 1) {
	        i++;
	    }
	    return 1 << i;
	}


#define GENERAL_VAR_SERIALIZE_BODY(T) \
		growToFitNextData( sizeof(T) ); \
		m_buff.insert(m_buff.end(), (char*)data, ((char*)data)+sizeof(T));


#define GENERAL_VECTOR_SERIALIZE_BODY(T) \
		uint32_t arraySize = data->size(); \
 		 \
		growToFitNextData( sizeof(uint32_t) ); \
		m_buff.insert(m_buff.end(), (char*)&arraySize, ((char*)&arraySize)+sizeof(uint32_t)); \
		 \
		growToFitNextData( sizeof(T)*arraySize ); \
		m_buff.insert(m_buff.end(), (char*)data->data(), ((char*)data->data())+sizeof(T)*arraySize);


#define GENERAL_VAR_DESERIALIZE_BODY(T) \
		*data = *(T*) (m_buff.data() + m_readCursor); \
		m_readCursor += sizeof(T);

#define GENERAL_VECTOR_DESERIALIZE_BODY(T) \
		uint32_t arraySize = 0; \
		 \
		arraySize = *(uint32_t*) (m_buff.data() + m_readCursor); \
		m_readCursor += sizeof(uint32_t); \
		 \
		data->clear(); \
		data->reserve(arraySize); \
		 \
		data->insert(data->end(), (T*)(m_buff.data() + m_readCursor), (T*)(m_buff.data() + m_readCursor + sizeof(T)*arraySize) ); \
		m_readCursor += sizeof(T)*arraySize;

	BinarySerializer::BinarySerializer( bfu::MemBlockBase* memBlock )
		:m_buff( bfu::custom_allocator<char>(memBlock) )
	{

	}
	BinarySerializer::BinarySerializer(BinarySerializer&& other)
		:m_buff( std::move(other.m_buff) )
	{

	}


	char* BinarySerializer::data()
	{
		return m_buff.data();
	}
	int BinarySerializer::size()
	{
		return m_buff.size();
	}
	void BinarySerializer::clear()
	{
		m_buff.clear();
	}
	void BinarySerializer::assignData(char* data, uint32_t size)
	{
		m_buff.clear();
		m_buff.reserve(size);
		m_buff.insert(m_buff.begin(), data, data+size);
	}

	bool BinarySerializer::operator==(const BinarySerializer& other)
	{
		return this->m_buff == other.m_buff;
	}
	void BinarySerializer::growToFitNextData(int incomingbuffsize)
	{
		incomingbuffsize = next_power_of_two( m_buff.size() + incomingbuffsize );
		m_buff.reserve( incomingbuffsize );
	}







	void BinarySerializer::Serialize( SerializableClassInterface* data )
	{
		data->PreSerializationCallback();
		for(ClassInfo* it = data->GetFirstClassInfo(); it != nullptr; it = it->next )
		{
			it->jsonSerializeFunc(this, (void*) ((size_t)data + it->offset) );
		}
		data->PostDeserializationCallback();
	}
	void BinarySerializer::Serialize( SerializableVector<SerializableClassInterface>* data )
	{
		uint32_t arraySize = data->size();
 		 
		growToFitNextData( sizeof(uint32_t) ); 
		m_buff.insert(m_buff.end(), (char*)&arraySize, ((char*)&arraySize)+sizeof(uint32_t));
		
		for(uint32_t i=0; i<arraySize; ++i)
		{ 
			SerializableClassInterface* ptr = &(*data)[i];
			Serialize( ptr );
		}
	}
	void BinarySerializer::Serialize( float* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(float);
	}
	void BinarySerializer::Serialize( SerializableVector<float>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( float );
	}
	void BinarySerializer::Serialize( bool* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(bool);
	}
	void BinarySerializer::Serialize( SerializableVector<bool>* data )
	{
		uint32_t arraySize = data->size();
 		 
		growToFitNextData( sizeof(uint32_t) ); 
		m_buff.insert(m_buff.end(), (char*)&arraySize, ((char*)&arraySize)+sizeof(uint32_t));

		growToFitNextData( sizeof(bool)*arraySize );
		for(uint32_t i=0; i<arraySize; ++i)
		{
			bool tmp = (*data)[i];
			m_buff.insert(m_buff.end(), (char*)&tmp, ( (char*)&tmp )+sizeof(bool));
		}
	}
	void BinarySerializer::Serialize( bfu::stream* data )
	{
		uint32_t buffSize = data->size();

		growToFitNextData( sizeof(uint32_t) );
		m_buff.insert(m_buff.end(), (char*)&buffSize, ((char*)&buffSize)+sizeof(uint32_t));

		growToFitNextData( buffSize );
		m_buff.insert(m_buff.end(), data->c_str(), data->c_str()+buffSize);
	}
	void BinarySerializer::Serialize( SerializableVector<bfu::stream>* data )
	{
		uint32_t arraySize = data->size(); 
 		 
		growToFitNextData( sizeof(uint32_t) ); 
		m_buff.insert(m_buff.end(), (char*)&arraySize, ((char*)&arraySize)+sizeof(uint32_t)); 
		 

		for(int i=0; i<arraySize; ++i)
		{
			uint32_t stringSize = (*data)[i].size();
			growToFitNextData( sizeof(uint32_t) ); 
			m_buff.insert(m_buff.end(), (char*)&stringSize, ((char*)&stringSize)+sizeof(uint32_t)); 


			growToFitNextData( stringSize );
			m_buff.insert(m_buff.end(), (*data)[i].c_str(), (*data)[i].c_str()+stringSize);
		}
	}
	void BinarySerializer::Serialize( bfu::string* data )
	{
		uint32_t buffSize = data->size();

		growToFitNextData( sizeof(uint32_t) );
		m_buff.insert(m_buff.end(), (char*)&buffSize, ((char*)&buffSize)+sizeof(uint32_t));

		growToFitNextData( buffSize );
		m_buff.insert(m_buff.end(), data->c_str(), data->c_str()+buffSize);
	}
	void BinarySerializer::Serialize( SerializableVector<bfu::string>* data )
	{
		uint32_t arraySize = data->size(); 
 		 
		growToFitNextData( sizeof(uint32_t) ); 
		m_buff.insert(m_buff.end(), (char*)&arraySize, ((char*)&arraySize)+sizeof(uint32_t)); 
		 

		for(int i=0; i<arraySize; ++i)
		{
			uint32_t stringSize = (*data)[i].size();
			growToFitNextData( sizeof(uint32_t) ); 
			m_buff.insert(m_buff.end(), (char*)&stringSize, ((char*)&stringSize)+sizeof(uint32_t)); 


			growToFitNextData( stringSize );
			m_buff.insert(m_buff.end(), (*data)[i].c_str(), (*data)[i].c_str()+stringSize);
		}
	}
		
	void BinarySerializer::Serialize( uint8_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(uint8_t);
	}
	void BinarySerializer::Serialize( SerializableVector<uint8_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( uint8_t );
	}
	void BinarySerializer::Serialize( uint16_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(uint16_t);
	}
	void BinarySerializer::Serialize( SerializableVector<uint16_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( uint16_t );
	}
	void BinarySerializer::Serialize( uint32_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(uint32_t);
	}
	void BinarySerializer::Serialize( SerializableVector<uint32_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( uint32_t );
	}
	void BinarySerializer::Serialize( uint64_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(uint64_t);
	}
	void BinarySerializer::Serialize( SerializableVector<uint64_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( uint64_t );
	}

	void BinarySerializer::Serialize( int8_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(int8_t);
	}
	void BinarySerializer::Serialize( SerializableVector<int8_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( int8_t );
	}
	void BinarySerializer::Serialize( int16_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(int16_t);
	}
	void BinarySerializer::Serialize( SerializableVector<int16_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( int16_t );
	}
	void BinarySerializer::Serialize( int32_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(int32_t);
	}
	void BinarySerializer::Serialize( SerializableVector<int32_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( int32_t );
	}
	void BinarySerializer::Serialize( int64_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(int64_t);
	}
	void BinarySerializer::Serialize( SerializableVector<int64_t>* data )
	{
		GENERAL_VECTOR_SERIALIZE_BODY( int64_t );
	}





		//---------------




	void BinarySerializer::Deserialize( SerializableClassInterface* data )
	{
		data->PreDeserializationCallback();
		for( ClassInfo* classInfo = data->GetFirstClassInfo(); classInfo != nullptr; classInfo = classInfo->next )
		{
			classInfo->jsonDeserializeFunc( this,  (void*) ((size_t)data + classInfo->offset) );
		}
		data->PostDeserializationCallback();
	}
	void BinarySerializer::Deserialize( SerializableVector<SerializableClassInterface>* data )
	{
		for(int i=0; i<data->size(); ++i)
		{
			(*data)[i].Dispouse();
		}
		data->clear(); 

		uint32_t arraySize = 0; 
		 
		arraySize = *(uint32_t*) (m_buff.data() + m_readCursor); 
		m_readCursor += sizeof(uint32_t);
 		 
		for(int i=0; i<arraySize; ++i)
		{ 
			SerializableClassInterface* cache = data->allocateAndInit( data->mBlock() );
 		 
			Deserialize( cache ); 
 		 
			data->emplace_back( cache ); 
		}
	}
	void BinarySerializer::Deserialize( float* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( float );
	}
	void BinarySerializer::Deserialize( SerializableVector<float>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( float );
	}
	void BinarySerializer::Deserialize( bool* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( bool );
	}
	void BinarySerializer::Deserialize( SerializableVector<bool>* data )
	{
		uint32_t arraySize = 0; 
		 
		arraySize = *(uint32_t*) (m_buff.data() + m_readCursor); 
		m_readCursor += sizeof(uint32_t);
		 
		data->clear(); 
		data->reserve(arraySize);

		bool tmp;
		for(int i=0; i<arraySize; ++i)
		{
			tmp = *(bool*) (m_buff.data() + m_readCursor);
			m_readCursor += sizeof(bool);
			data->push_back(tmp); 
		}
	}
	void BinarySerializer::Deserialize( bfu::stream* data )
	{
		uint32_t buffSize;

		buffSize = *(uint32_t*) (m_buff.data() + m_readCursor);
		m_readCursor += sizeof(uint32_t);

		data->clear();
		data->assign(m_buff.data() + m_readCursor, buffSize);
		m_readCursor += buffSize;
	}
	void BinarySerializer::Deserialize( SerializableVector<bfu::stream>* data )
	{
		uint32_t arraySize;

		arraySize = *(uint32_t*) (m_buff.data() + m_readCursor);
		m_readCursor += sizeof(uint32_t);

		data->clear();
		data->reserve(arraySize);
		for(int i=0; i<arraySize; ++i)
		{
			uint32_t stringSize;

			stringSize = *(uint32_t*) (m_buff.data() + m_readCursor);
			m_readCursor += sizeof(uint32_t);


			data->emplace_back( data->mBlock() );
			(*data)[i].assign(m_buff.data() + m_readCursor, stringSize);
			m_readCursor += stringSize;
		}
	}
	void BinarySerializer::Deserialize( bfu::string* data )
	{
		uint32_t buffSize;

		buffSize = *(uint32_t*) (m_buff.data() + m_readCursor);
		m_readCursor += sizeof(uint32_t);

		data->clear();
		data->reserve(buffSize);
		data->insert(0, m_buff.data() + m_readCursor, buffSize);
		m_readCursor += buffSize;
	}
	void BinarySerializer::Deserialize( SerializableVector<bfu::string>* data )
	{
		uint32_t arraySize;

		arraySize = *(uint32_t*) (m_buff.data() + m_readCursor);
		m_readCursor += sizeof(uint32_t);

		data->clear();
		data->reserve(arraySize);
		for(int i=0; i<arraySize; ++i)
		{
			uint32_t stringSize;

			stringSize = *(uint32_t*) (m_buff.data() + m_readCursor);
			m_readCursor += sizeof(uint32_t);


			data->emplace_back( data->mBlock() );
			(*data)[i].insert(0, m_buff.data() + m_readCursor, stringSize);
			m_readCursor += stringSize;
		}
	}
		
	void BinarySerializer::Deserialize( uint8_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( uint8_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<uint8_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( uint8_t );
	}
	void BinarySerializer::Deserialize( uint16_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( uint16_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<uint16_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( uint16_t );
	}
	void BinarySerializer::Deserialize( uint32_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( uint32_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<uint32_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( uint32_t );
	}
	void BinarySerializer::Deserialize( uint64_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( uint64_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<uint64_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( uint64_t );
	}

	void BinarySerializer::Deserialize( int8_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( int8_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<int8_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( int8_t );
	}
	void BinarySerializer::Deserialize( int16_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( int16_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<int16_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( int16_t );
	}
	void BinarySerializer::Deserialize( int32_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( int32_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<int32_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( int32_t );
	}
	void BinarySerializer::Deserialize( int64_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( int64_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<int64_t>* data )
	{
		GENERAL_VECTOR_DESERIALIZE_BODY( int64_t );
	}
}