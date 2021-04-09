#include "SerializerBase.hpp"



namespace bfu
{
#define GENERATE_SERIALIZE_BINDING_FUNC(T) \
	void SerializerBase::Serialize_##T (SerializerBase* serializer, void* data){ serializer->Serialize( (T*)data ); }

#define GENERATE_SERIALIZE_VECTOR_BINDING_FUNC(T) \
	void SerializerBase::Serialize_v_##T (SerializerBase* serializer, void* data){ serializer->Serialize( (SerializableVector<T>*)data ); }


#define GENERATE_DESERIALIZE_BINDING_FUNC(T) \
	void SerializerBase::Deserialize_##T (SerializerBase* serializer, void* data){ serializer->Deserialize( (T*)data ); }

#define GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC(T) \
	void SerializerBase::Deserialize_v_##T (SerializerBase* serializer, void* data){ serializer->Deserialize( (SerializableVector<T>*)data ); }



	void SerializerBase::Serialize_SerializableClassInterface (SerializerBase* serializer, void* data)
	{
		SerializableClassInterface* i_data = (SerializableClassInterface*)data;

		serializer->Serialize( i_data );
	}
	GENERATE_SERIALIZE_BINDING_FUNC( float )
	GENERATE_SERIALIZE_BINDING_FUNC( bool )
	GENERATE_SERIALIZE_BINDING_FUNC( stream )
	GENERATE_SERIALIZE_BINDING_FUNC( string )
	GENERATE_SERIALIZE_BINDING_FUNC( uint8_t )
	GENERATE_SERIALIZE_BINDING_FUNC( uint16_t )
	GENERATE_SERIALIZE_BINDING_FUNC( uint32_t )
	GENERATE_SERIALIZE_BINDING_FUNC( uint64_t )
	GENERATE_SERIALIZE_BINDING_FUNC( int8_t )
	GENERATE_SERIALIZE_BINDING_FUNC( int16_t )
	GENERATE_SERIALIZE_BINDING_FUNC( int32_t )
	GENERATE_SERIALIZE_BINDING_FUNC( int64_t )


	void SerializerBase::Serialize_v_SerializableClassInterface (SerializerBase* serializer, void* data){ serializer->Serialize( (SerializableVector<SerializableClassInterface>*)data ); }
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( float )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( bool )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( stream )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( string )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( uint8_t )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( uint16_t )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( uint32_t )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( uint64_t )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( int8_t )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( int16_t )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( int32_t )
	GENERATE_SERIALIZE_VECTOR_BINDING_FUNC( int64_t )




	void SerializerBase::Deserialize_SerializableClassInterface (SerializerBase* serializer, void* data)
	{
		SerializableClassInterface* i_data = (SerializableClassInterface*)data;

		serializer->Deserialize( i_data );
	}
	GENERATE_DESERIALIZE_BINDING_FUNC( float )
	GENERATE_DESERIALIZE_BINDING_FUNC( bool )
	GENERATE_DESERIALIZE_BINDING_FUNC( stream )
	GENERATE_DESERIALIZE_BINDING_FUNC( string )
	GENERATE_DESERIALIZE_BINDING_FUNC( uint8_t )
	GENERATE_DESERIALIZE_BINDING_FUNC( uint16_t )
	GENERATE_DESERIALIZE_BINDING_FUNC( uint32_t )
	GENERATE_DESERIALIZE_BINDING_FUNC( uint64_t )
	GENERATE_DESERIALIZE_BINDING_FUNC( int8_t )
	GENERATE_DESERIALIZE_BINDING_FUNC( int16_t )
	GENERATE_DESERIALIZE_BINDING_FUNC( int32_t )
	GENERATE_DESERIALIZE_BINDING_FUNC( int64_t )

	
	void SerializerBase::Deserialize_v_SerializableClassInterface (SerializerBase* serializer, void* data){ serializer->Deserialize( (SerializableVector<SerializableClassInterface>*)data ); }
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( float )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( bool )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( stream )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( string )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( uint8_t )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( uint16_t )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( uint32_t )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( uint64_t )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( int8_t )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( int16_t )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( int32_t )
	GENERATE_DESERIALIZE_VECTOR_BINDING_FUNC( int64_t )
}