#ifndef H_SerializerBase
#define H_SerializerBase
#include <cstdint>
#include "Serializable.hpp"
#include "stream.hpp"

namespace bfu2
{

#define GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR(T) \
	virtual void Serialize( T* data ) = 0; \
	static void Serialize_##T (SerializerBase* serializer, void* data); \


#define GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR(T) \
	virtual void Serialize( SerializableVector<T>* data ) = 0; \
	static void Serialize_v_##T (SerializerBase* serializer, void* data); \



#define GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR(T) \
	virtual void Deserialize( T* data ) = 0; \
	static void Deserialize_##T (SerializerBase* serializer, void* data); \

#define GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR(T) \
	virtual void Deserialize( SerializableVector<T>* data ) = 0; \
	static void Deserialize_v_##T (SerializerBase* serializer, void* data); \

	class SerializableClassInterface;

	using bfu::stream;
	using bfu::string;

	class SerializerBase
	{
	public:

		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( SerializableClassInterface )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( float )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( bool )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( stream )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( string )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( uint8_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( uint16_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( uint32_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( uint64_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( int8_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( int16_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( int32_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( int64_t )


		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( SerializableClassInterface )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( float )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( bool )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( stream )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( string )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( uint8_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( uint16_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( uint32_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( uint64_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( int8_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( int16_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( int32_t )
		GENERATE_SERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( int64_t )




		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( SerializableClassInterface )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( float )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( bool )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( stream )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( string )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( uint8_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( uint16_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( uint32_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( uint64_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( int8_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( int16_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( int32_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_SINGLE_VAR( int64_t )


		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( SerializableClassInterface )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( float )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( bool )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( stream )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( string )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( uint8_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( uint16_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( uint32_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( uint64_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( int8_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( int16_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( int32_t )
		GENERATE_DESERIALIZE_FUNCTIONS_FOR_VAR_VECTOR( int64_t )





		// virtual void Serialize( SerializableVector<SerializableClassInterface*>* data ) = 0;

		// virtual void Serialize( SerializableVector<float>* data ) = 0;

		// virtual void Serialize( SerializableVector<bool>* data ) = 0;

		// virtual void Serialize( SerializableVector<stream>* data ) = 0;

		// virtual void Serialize( SerializableVector<string>* data ) = 0;


		// virtual void Serialize( SerializableVector<uint8_t>* data ) = 0;

		// virtual void Serialize( SerializableVector<uint16_t>* data ) = 0;

		// virtual void Serialize( SerializableVector<uint32_t>* data ) = 0;

		// virtual void Serialize( SerializableVector<uint64_t>* data ) = 0;


		// virtual void Serialize( SerializableVector<int8_t>* data ) = 0;

		// virtual void Serialize( SerializableVector<int16_t>* data ) = 0;

		// virtual void Serialize( SerializableVector<int32_t>* data ) = 0;

		// virtual void Serialize( SerializableVector<int64_t>* data ) = 0;





		// //---------------





		// virtual void Deserialize( SerializableVector<SerializableClassInterface*>* data ) = 0;

		// virtual void Deserialize( SerializableVector<float>* data ) = 0;

		// virtual void Deserialize( SerializableVector<bool>* data ) = 0;

		// virtual void Deserialize( SerializableVector<stream>* data ) = 0;

		// virtual void Deserialize( SerializableVector<string>* data ) = 0;


		// virtual void Deserialize( SerializableVector<uint8_t>* data ) = 0;

		// virtual void Deserialize( SerializableVector<uint16_t>* data ) = 0;

		// virtual void Deserialize( SerializableVector<uint32_t>* data ) = 0;

		// virtual void Deserialize( SerializableVector<uint64_t>* data ) = 0;


		// virtual void Deserialize( SerializableVector<int8_t>* data ) = 0;

		// virtual void Deserialize( SerializableVector<int16_t>* data ) = 0;

		// virtual void Deserialize( SerializableVector<int32_t>* data ) = 0;

		// virtual void Deserialize( SerializableVector<int64_t>* data ) = 0;
	};
}

#endif