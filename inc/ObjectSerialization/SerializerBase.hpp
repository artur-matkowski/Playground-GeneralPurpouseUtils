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

		virtual void Serialize( const SerializableClassInterface* data ) = 0;
		virtual void Serialize( const SerializableVector<SerializableClassInterface*>* data ) = 0;

		virtual void Serialize( const float* data ) = 0;
		virtual void Serialize( const SerializableVector<float>* data ) = 0;

		virtual void Serialize( const double* data ) = 0;
		virtual void Serialize( const SerializableVector<double>* data ) = 0;

		virtual void Serialize( const bool* data ) = 0;
		virtual void Serialize( const SerializableVector<bool>* data ) = 0;

		virtual void Serialize( const char* data ) = 0;
		virtual void Serialize( const SerializableVector<char>* data ) = 0;

		virtual void Serialize( const bfu::stream* data ) = 0;
		virtual void Serialize( const SerializableVector<bfu::stream>* data ) = 0;

		virtual void Serialize( const bfu::string* data ) = 0;
		virtual void Serialize( const SerializableVector<bfu::string>* data ) = 0;


		virtual void Serialize( const uint8_t* data ) = 0;
		virtual void Serialize( const SerializableVector<uint8_t>* data ) = 0;

		virtual void Serialize( const uint16_t* data ) = 0;
		virtual void Serialize( const SerializableVector<uint16_t>* data ) = 0;

		virtual void Serialize( const uint32_t* data ) = 0;
		virtual void Serialize( const SerializableVector<uint32_t>* data ) = 0;

		virtual void Serialize( const uint64_t* data ) = 0;
		virtual void Serialize( const SerializableVector<uint64_t>* data ) = 0;


		virtual void Serialize( const int8_t* data ) = 0;
		virtual void Serialize( const SerializableVector<int8_t>* data ) = 0;

		virtual void Serialize( const int16_t* data ) = 0;
		virtual void Serialize( const SerializableVector<int16_t>* data ) = 0;

		virtual void Serialize( const int32_t* data ) = 0;
		virtual void Serialize( const SerializableVector<int32_t>* data ) = 0;

		virtual void Serialize( const int64_t* data ) = 0;
		virtual void Serialize( const SerializableVector<int64_t>* data ) = 0;

		//---------------

		virtual void Deserialize( const SerializableClassInterface* data ) = 0;
		virtual void Deserialize( const SerializableVector<SerializableClassInterface*>* data ) = 0;

		virtual void Deserialize( const float* data ) = 0;
		virtual void Deserialize( const SerializableVector<float>* data ) = 0;

		virtual void Deserialize( const double* data ) = 0;
		virtual void Deserialize( const SerializableVector<double>* data ) = 0;

		virtual void Deserialize( const bool* data ) = 0;
		virtual void Deserialize( const SerializableVector<bool>* data ) = 0;

		virtual void Deserialize( const char* data ) = 0;
		virtual void Deserialize( const SerializableVector<char>* data ) = 0;

		virtual void Deserialize( const bfu::stream* data ) = 0;
		virtual void Deserialize( const SerializableVector<bfu::stream>* data ) = 0;

		virtual void Deserialize( const bfu::string* data ) = 0;
		virtual void Deserialize( const SerializableVector<bfu::string>* data ) = 0;
		

		virtual void Deserialize( const uint8_t* data ) = 0;
		virtual void Deserialize( const SerializableVector<uint8_t>* data ) = 0;

		virtual void Deserialize( const uint16_t* data ) = 0;
		virtual void Deserialize( const SerializableVector<uint16_t>* data ) = 0;

		virtual void Deserialize( const uint32_t* data ) = 0;
		virtual void Deserialize( const SerializableVector<uint32_t>* data ) = 0;

		virtual void Deserialize( const uint64_t* data ) = 0;
		virtual void Deserialize( const SerializableVector<uint64_t>* data ) = 0;


		virtual void Deserialize( const int8_t* data ) = 0;
		virtual void Deserialize( const SerializableVector<int8_t>* data ) = 0;

		virtual void Deserialize( const int16_t* data ) = 0;
		virtual void Deserialize( const SerializableVector<int16_t>* data ) = 0;

		virtual void Deserialize( const int32_t* data ) = 0;
		virtual void Deserialize( const SerializableVector<int32_t>* data ) = 0;

		virtual void Deserialize( const int64_t* data ) = 0;
		virtual void Deserialize( const SerializableVector<int64_t>* data ) = 0;
	};
}

#endif