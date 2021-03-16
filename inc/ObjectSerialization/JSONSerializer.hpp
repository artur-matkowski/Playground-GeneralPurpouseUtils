#ifndef H_JSONSerializer
#define H_JSONSerializer 
#include "SerializerBase.hpp"

namespace bfu2
{
	class JSONSerializer: public SerializerBase, public bfu::stream
	{
	public:
		using bfu::stream::stream;
		
		virtual void Serialize( const SerializableClassInterface* data ) override;
		virtual void Serialize( const SerializableVector<SerializableClassInterface*>* data ) override;

		virtual void Serialize( const float* data ) override;
		virtual void Serialize( const SerializableVector<float>* data ) override;

		virtual void Serialize( const double* data ) override;
		virtual void Serialize( const SerializableVector<double>* data ) override;

		virtual void Serialize( const bool* data ) override;
		virtual void Serialize( const SerializableVector<bool>* data ) override;

		virtual void Serialize( const char* data ) override;
		virtual void Serialize( const SerializableVector<char>* data ) override;

		virtual void Serialize( const bfu::stream* data ) override;
		virtual void Serialize( const SerializableVector<bfu::stream>* data ) override;

		virtual void Serialize( const bfu::string* data ) override;
		virtual void Serialize( const SerializableVector<bfu::string>* data ) override;
		

		virtual void Serialize( const uint8_t* data ) override;
		virtual void Serialize( const SerializableVector<uint8_t>* data ) override;

		virtual void Serialize( const uint16_t* data ) override;
		virtual void Serialize( const SerializableVector<uint16_t>* data ) override;

		virtual void Serialize( const uint32_t* data ) override;
		virtual void Serialize( const SerializableVector<uint32_t>* data ) override;

		virtual void Serialize( const uint64_t* data ) override;
		virtual void Serialize( const SerializableVector<uint64_t>* data ) override;


		virtual void Serialize( const int8_t* data ) override;
		virtual void Serialize( const SerializableVector<int8_t>* data ) override;

		virtual void Serialize( const int16_t* data ) override;
		virtual void Serialize( const SerializableVector<int16_t>* data ) override;

		virtual void Serialize( const int32_t* data ) override;
		virtual void Serialize( const SerializableVector<int32_t>* data ) override;

		virtual void Serialize( const int64_t* data ) override;
		virtual void Serialize( const SerializableVector<int64_t>* data ) override;

		//---------------

		virtual void Deserialize( const SerializableClassInterface* data ) override;
		virtual void Deserialize( const SerializableVector<SerializableClassInterface*>* data ) override;

		virtual void Deserialize( const float* data ) override;
		virtual void Deserialize( const SerializableVector<float>* data ) override;

		virtual void Deserialize( const double* data ) override;
		virtual void Deserialize( const SerializableVector<double>* data ) override;

		virtual void Deserialize( const bool* data ) override;
		virtual void Deserialize( const SerializableVector<bool>* data ) override;

		virtual void Deserialize( const char* data ) override;
		virtual void Deserialize( const SerializableVector<char>* data ) override;

		virtual void Deserialize( const bfu::stream* data ) override;
		virtual void Deserialize( const SerializableVector<bfu::stream>* data ) override;

		virtual void Deserialize( const bfu::string* data ) override;
		virtual void Deserialize( const SerializableVector<bfu::string>* data ) override;
		

		virtual void Deserialize( const uint8_t* data ) override;
		virtual void Deserialize( const SerializableVector<uint8_t>* data ) override;

		virtual void Deserialize( const uint16_t* data ) override;
		virtual void Deserialize( const SerializableVector<uint16_t>* data ) override;

		virtual void Deserialize( const uint32_t* data ) override;
		virtual void Deserialize( const SerializableVector<uint32_t>* data ) override;

		virtual void Deserialize( const uint64_t* data ) override;
		virtual void Deserialize( const SerializableVector<uint64_t>* data ) override;


		virtual void Deserialize( const int8_t* data ) override;
		virtual void Deserialize( const SerializableVector<int8_t>* data ) override;

		virtual void Deserialize( const int16_t* data ) override;
		virtual void Deserialize( const SerializableVector<int16_t>* data ) override;

		virtual void Deserialize( const int32_t* data ) override;
		virtual void Deserialize( const SerializableVector<int32_t>* data ) override;

		virtual void Deserialize( const int64_t* data ) override;
		virtual void Deserialize( const SerializableVector<int64_t>* data ) override;
	};
}

#endif