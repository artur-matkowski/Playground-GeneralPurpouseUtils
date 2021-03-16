#ifndef H_SerializerBase
#define H_SerializerBase
#include <cstdint>
#include "Serializable.hpp"

namespace bfu2
{
	class SerializableClassInterface;

	class SerializerBase
	{
	public:

		virtual void Serialize( const SerializableClassInterface* data ) = 0;
		virtual void Serialize( const SerializableVector<SerializableClassInterface>* data ) = 0;

		virtual void Serialize( const float* data ) = 0;
		virtual void Serialize( const SerializableVector<float>* data ) = 0;

		virtual void Serialize( const double* data ) = 0;
		virtual void Serialize( const SerializableVector<double>* data ) = 0;

		virtual void Serialize( const bool* data ) = 0;
		virtual void Serialize( const SerializableVector<bool>* data ) = 0;

		virtual void Serialize( const char* data ) = 0;
		virtual void Serialize( const SerializableVector<char>* data ) = 0;


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
	};
}

#endif