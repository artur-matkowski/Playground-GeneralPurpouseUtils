#ifndef H_SerializerBase
#define H_SerializerBase
#include <cstdint>
#include "Serializable.hpp"
#include "stream.hpp"

namespace bfu2
{
	class SerializableClassInterface;

	class SerializerBase
	{
	public:

		virtual void Serialize( SerializableClassInterface* data ) = 0;
		virtual void Serialize( SerializableVector<SerializableClassInterface*>* data ) = 0;

		virtual void Serialize( float* data ) = 0;
		virtual void Serialize( SerializableVector<float>* data ) = 0;

		virtual void Serialize( double* data ) = 0;
		virtual void Serialize( SerializableVector<double>* data ) = 0;

		virtual void Serialize( bool* data ) = 0;
		virtual void Serialize( SerializableVector<bool>* data ) = 0;

		virtual void Serialize( char* data ) = 0;
		virtual void Serialize( SerializableVector<char>* data ) = 0;

		virtual void Serialize( bfu::stream* data ) = 0;
		virtual void Serialize( SerializableVector<bfu::stream>* data ) = 0;

		virtual void Serialize( bfu::string* data ) = 0;
		virtual void Serialize( SerializableVector<bfu::string>* data ) = 0;


		virtual void Serialize( uint8_t* data ) = 0;
		virtual void Serialize( SerializableVector<uint8_t>* data ) = 0;

		virtual void Serialize( uint16_t* data ) = 0;
		virtual void Serialize( SerializableVector<uint16_t>* data ) = 0;

		virtual void Serialize( uint32_t* data ) = 0;
		virtual void Serialize( SerializableVector<uint32_t>* data ) = 0;

		virtual void Serialize( uint64_t* data ) = 0;
		virtual void Serialize( SerializableVector<uint64_t>* data ) = 0;


		virtual void Serialize( int8_t* data ) = 0;
		virtual void Serialize( SerializableVector<int8_t>* data ) = 0;

		virtual void Serialize( int16_t* data ) = 0;
		virtual void Serialize( SerializableVector<int16_t>* data ) = 0;

		virtual void Serialize( int32_t* data ) = 0;
		virtual void Serialize( SerializableVector<int32_t>* data ) = 0;

		virtual void Serialize( int64_t* data ) = 0;
		virtual void Serialize( SerializableVector<int64_t>* data ) = 0;

		//---------------

		virtual void Deserialize( SerializableClassInterface* data ) = 0;
		virtual void Deserialize( SerializableVector<SerializableClassInterface*>* data ) = 0;

		virtual void Deserialize( float* data ) = 0;
		virtual void Deserialize( SerializableVector<float>* data ) = 0;

		virtual void Deserialize( double* data ) = 0;
		virtual void Deserialize( SerializableVector<double>* data ) = 0;

		virtual void Deserialize( bool* data ) = 0;
		virtual void Deserialize( SerializableVector<bool>* data ) = 0;

		virtual void Deserialize( char* data ) = 0;
		virtual void Deserialize( SerializableVector<char>* data ) = 0;

		virtual void Deserialize( bfu::stream* data ) = 0;
		virtual void Deserialize( SerializableVector<bfu::stream>* data ) = 0;

		virtual void Deserialize( bfu::string* data ) = 0;
		virtual void Deserialize( SerializableVector<bfu::string>* data ) = 0;


		virtual void Deserialize( uint8_t* data ) = 0;
		virtual void Deserialize( SerializableVector<uint8_t>* data ) = 0;

		virtual void Deserialize( uint16_t* data ) = 0;
		virtual void Deserialize( SerializableVector<uint16_t>* data ) = 0;

		virtual void Deserialize( uint32_t* data ) = 0;
		virtual void Deserialize( SerializableVector<uint32_t>* data ) = 0;

		virtual void Deserialize( uint64_t* data ) = 0;
		virtual void Deserialize( SerializableVector<uint64_t>* data ) = 0;


		virtual void Deserialize( int8_t* data ) = 0;
		virtual void Deserialize( SerializableVector<int8_t>* data ) = 0;

		virtual void Deserialize( int16_t* data ) = 0;
		virtual void Deserialize( SerializableVector<int16_t>* data ) = 0;

		virtual void Deserialize( int32_t* data ) = 0;
		virtual void Deserialize( SerializableVector<int32_t>* data ) = 0;

		virtual void Deserialize( int64_t* data ) = 0;
		virtual void Deserialize( SerializableVector<int64_t>* data ) = 0;
	};
}

#endif