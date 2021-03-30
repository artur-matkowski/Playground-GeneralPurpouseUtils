#include "BinarySerializer.hpp"

namespace bfu2
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

	BinarySerializer::BinarySerializer()
	{

	}
	BinarySerializer::BinarySerializer(BinarySerializer&& other)
	{}







	void BinarySerializer::Serialize( SerializableClassInterface* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<SerializableClassInterface>* data )
	{

	}
	void BinarySerializer::Serialize( float* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<float>* data )
	{

	}
	void BinarySerializer::Serialize( bool* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<bool>* data )
	{

	}
	void BinarySerializer::Serialize( bfu::stream* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<bfu::stream>* data )
	{

	}
	void BinarySerializer::Serialize( bfu::string* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<bfu::string>* data )
	{

	}
		
	void BinarySerializer::Serialize( uint8_t* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<uint8_t>* data )
	{

	}
	void BinarySerializer::Serialize( uint16_t* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<uint16_t>* data )
	{

	}
	void BinarySerializer::Serialize( uint32_t* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<uint32_t>* data )
	{

	}
	void BinarySerializer::Serialize( uint64_t* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<uint64_t>* data )
	{

	}

	void BinarySerializer::Serialize( int8_t* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<int8_t>* data )
	{

	}
	void BinarySerializer::Serialize( int16_t* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<int16_t>* data )
	{

	}
	void BinarySerializer::Serialize( int32_t* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<int32_t>* data )
	{

	}
	void BinarySerializer::Serialize( int64_t* data )
	{

	}
	void BinarySerializer::Serialize( SerializableVector<int64_t>* data )
	{

	}





		//---------------




	void BinarySerializer::Deserialize( SerializableClassInterface* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<SerializableClassInterface>* data )
	{

	}
	void BinarySerializer::Deserialize( float* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<float>* data )
	{

	}
	void BinarySerializer::Deserialize( bool* data )
	{

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

	}
	void BinarySerializer::Deserialize( SerializableVector<uint8_t>* data )
	{

	}
	void BinarySerializer::Deserialize( uint16_t* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<uint16_t>* data )
	{

	}
	void BinarySerializer::Deserialize( uint32_t* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<uint32_t>* data )
	{

	}
	void BinarySerializer::Deserialize( uint64_t* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<uint64_t>* data )
	{

	}

	void BinarySerializer::Deserialize( int8_t* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<int8_t>* data )
	{

	}
	void BinarySerializer::Deserialize( int16_t* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<int16_t>* data )
	{

	}
	void BinarySerializer::Deserialize( int32_t* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<int32_t>* data )
	{

	}
	void BinarySerializer::Deserialize( int64_t* data )
	{

	}
	void BinarySerializer::Deserialize( SerializableVector<int64_t>* data )
	{

	}
}