#include "BinarySerializer.hpp"

namespace bfu2
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


#define GENERAL_VAR_DESERIALIZE_BODY(T) \
		*data = *(T*) (m_buff.data() + m_readCursor); \
		m_readCursor += sizeof(T);

	BinarySerializer::BinarySerializer( bfu::MemBlockBase* memBlock )
		:m_buff( bfu::custom_allocator<char>(memBlock) )
	{

	}
	BinarySerializer::BinarySerializer(BinarySerializer&& other)
	{}

	bool BinarySerializer::operator==(const BinarySerializer& other)
	{
		return this->m_buff == other.m_buff;
	}
	void BinarySerializer::growToFitNextData(int incomingbuffsize)
	{
		incomingbuffsize = next_power_of_two( m_buff.size() + incomingbuffsize );
		m_buff.reserve( incomingbuffsize );
	}
	char* BinarySerializer::buff()
	{
		return m_buff.data();
	}
	uint32_t BinarySerializer::size()
	{
		return m_buff.size();
	}







	void BinarySerializer::Serialize( SerializableClassInterface* data )
	{
		for(ClassInfo* it = data->GetFirstClassInfo(); it != nullptr; it = it->next )
		{
			it->jsonSerializeFunc(this, (void*) ((size_t)data + it->offset) );
		}
	}
	void BinarySerializer::Serialize( SerializableVector<SerializableClassInterface>* data )
	{

	}
	void BinarySerializer::Serialize( float* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(float);
	}
	void BinarySerializer::Serialize( SerializableVector<float>* data )
	{

	}
	void BinarySerializer::Serialize( bool* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(bool);
	}
	void BinarySerializer::Serialize( SerializableVector<bool>* data )
	{

	}
	void BinarySerializer::Serialize( bfu::stream* data )
	{
		uint32_t buffSize = data->size();

		growToFitNextData( sizeof(uint32_t) );
		m_buff.insert(m_buff.end(), &buffSize, &buffSize+sizeof(uint32_t));

		growToFitNextData( buffSize );
		m_buff.insert(m_buff.end(), data->c_str(), data->c_str()+buffSize);
	}
	void BinarySerializer::Serialize( SerializableVector<bfu::stream>* data )
	{

	}
	void BinarySerializer::Serialize( bfu::string* data )
	{
		uint32_t buffSize = data->size();

		growToFitNextData( sizeof(uint32_t) );
		m_buff.insert(m_buff.end(), &buffSize, &buffSize+sizeof(uint32_t));

		growToFitNextData( buffSize );
		m_buff.insert(m_buff.end(), data->c_str(), data->c_str()+buffSize);
	}
	void BinarySerializer::Serialize( SerializableVector<bfu::string>* data )
	{

	}
		
	void BinarySerializer::Serialize( uint8_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(uint8_t);
	}
	void BinarySerializer::Serialize( SerializableVector<uint8_t>* data )
	{

	}
	void BinarySerializer::Serialize( uint16_t* data )
	{
		//GENERAL_VAR_SERIALIZE_BODY(uint16_t);
		growToFitNextData( sizeof(uint16_t) );
		m_buff.insert(m_buff.end(), (char*)data, ((char*)data)+sizeof(uint16_t));
	}
	void BinarySerializer::Serialize( SerializableVector<uint16_t>* data )
	{

	}
	void BinarySerializer::Serialize( uint32_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(uint32_t);
	}
	void BinarySerializer::Serialize( SerializableVector<uint32_t>* data )
	{

	}
	void BinarySerializer::Serialize( uint64_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(uint64_t);
	}
	void BinarySerializer::Serialize( SerializableVector<uint64_t>* data )
	{

	}

	void BinarySerializer::Serialize( int8_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(int8_t);
	}
	void BinarySerializer::Serialize( SerializableVector<int8_t>* data )
	{

	}
	void BinarySerializer::Serialize( int16_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(int16_t);
	}
	void BinarySerializer::Serialize( SerializableVector<int16_t>* data )
	{

	}
	void BinarySerializer::Serialize( int32_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(int32_t);
	}
	void BinarySerializer::Serialize( SerializableVector<int32_t>* data )
	{

	}
	void BinarySerializer::Serialize( int64_t* data )
	{
		GENERAL_VAR_SERIALIZE_BODY(int64_t);
	}
	void BinarySerializer::Serialize( SerializableVector<int64_t>* data )
	{

	}





		//---------------




	void BinarySerializer::Deserialize( SerializableClassInterface* data )
	{
		for( ClassInfo* classInfo = data->GetFirstClassInfo(); classInfo != nullptr; classInfo = classInfo->next )
		{
			classInfo->jsonDeserializeFunc( this,  (void*) ((size_t)data + classInfo->offset) );
		}
	}
	void BinarySerializer::Deserialize( SerializableVector<SerializableClassInterface>* data )
	{

	}
	void BinarySerializer::Deserialize( float* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( float );
	}
	void BinarySerializer::Deserialize( SerializableVector<float>* data )
	{

	}
	void BinarySerializer::Deserialize( bool* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( bool );
	}
	void BinarySerializer::Deserialize( SerializableVector<bool>* data )
	{

	}
	void BinarySerializer::Deserialize( bfu::stream* data )
	{
	}
	void BinarySerializer::Deserialize( SerializableVector<bfu::stream>* data )
	{

	}
	void BinarySerializer::Deserialize( bfu::string* data )
	{
	}
	void BinarySerializer::Deserialize( SerializableVector<bfu::string>* data )
	{

	}
		
	void BinarySerializer::Deserialize( uint8_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( uint8_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<uint8_t>* data )
	{

	}
	void BinarySerializer::Deserialize( uint16_t* data )
	{
		//GENERAL_VAR_DESERIALIZE_BODY( uint16_t );

		*data = *(uint16_t*) (m_buff.data() + m_readCursor); \
		m_readCursor += sizeof(uint16_t);
	}
	void BinarySerializer::Deserialize( SerializableVector<uint16_t>* data )
	{

	}
	void BinarySerializer::Deserialize( uint32_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( uint32_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<uint32_t>* data )
	{

	}
	void BinarySerializer::Deserialize( uint64_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( uint64_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<uint64_t>* data )
	{

	}

	void BinarySerializer::Deserialize( int8_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( int8_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<int8_t>* data )
	{

	}
	void BinarySerializer::Deserialize( int16_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( int16_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<int16_t>* data )
	{

	}
	void BinarySerializer::Deserialize( int32_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( int32_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<int32_t>* data )
	{

	}
	void BinarySerializer::Deserialize( int64_t* data )
	{
		GENERAL_VAR_DESERIALIZE_BODY( int64_t );
	}
	void BinarySerializer::Deserialize( SerializableVector<int64_t>* data )
	{

	}
}