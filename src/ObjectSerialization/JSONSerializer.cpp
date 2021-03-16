#include "JSONSerializer.hpp"

namespace bfu2
{
	void JSONSerializer::Serialize( const SerializableClassInterface* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<SerializableClassInterface*>* data )
	{

	}

	void JSONSerializer::Serialize( const float* data )
	{
   		this->sprintf("%f", *data);
	}
	void JSONSerializer::Serialize( const SerializableVector<float>* data )
	{

	}

	void JSONSerializer::Serialize( const double* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<double>* data )
	{

	}

	void JSONSerializer::Serialize( const bool* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<bool>* data )
	{

	}

	void JSONSerializer::Serialize( const char* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<char>* data )
	{

	}

	void JSONSerializer::Serialize( const bfu::stream* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<bfu::stream>* data )
	{

	}

	void JSONSerializer::Serialize( const bfu::string* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<bfu::string>* data )
	{

	}
		

	void JSONSerializer::Serialize( const uint8_t* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<uint8_t>* data )
	{

	}

	void JSONSerializer::Serialize( const uint16_t* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<uint16_t>* data )
	{

	}

	void JSONSerializer::Serialize( const uint32_t* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<uint32_t>* data )
	{

	}

	void JSONSerializer::Serialize( const uint64_t* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<uint64_t>* data )
	{

	}


	void JSONSerializer::Serialize( const int8_t* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<int8_t>* data )
	{

	}

	void JSONSerializer::Serialize( const int16_t* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<int16_t>* data )
	{

	}

	void JSONSerializer::Serialize( const int32_t* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<int32_t>* data )
	{

	}

	void JSONSerializer::Serialize( const int64_t* data )
	{

	}
	void JSONSerializer::Serialize( const SerializableVector<int64_t>* data )
	{

	}

	//---------------

	void JSONSerializer::Deserialize( const SerializableClassInterface* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<SerializableClassInterface*>* data )
	{

	}

	void JSONSerializer::Deserialize( const float* data )
	{
		skipToOneOf("-.0123456789");

		m_readCursor += sscanf(m_readCursor, "%f", data);
		skipToOneOf(",]}");
	}
	void JSONSerializer::Deserialize( const SerializableVector<float>* data )
	{

	}

	void JSONSerializer::Deserialize( const double* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<double>* data )
	{

	}

	void JSONSerializer::Deserialize( const bool* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<bool>* data )
	{

	}

	void JSONSerializer::Deserialize( const char* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<char>* data )
	{

	}

	void JSONSerializer::Deserialize( const bfu::stream* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<bfu::stream>* data )
	{

	}

	void JSONSerializer::Deserialize( const bfu::string* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<bfu::string>* data )
	{

	}

	void JSONSerializer::Deserialize( const uint8_t* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<uint8_t>* data )
	{

	}

	void JSONSerializer::Deserialize( const uint16_t* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<uint16_t>* data )
	{

	}

	void JSONSerializer::Deserialize( const uint32_t* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<uint32_t>* data )
	{

	}

	void JSONSerializer::Deserialize( const uint64_t* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<uint64_t>* data )
	{

	}


	void JSONSerializer::Deserialize( const int8_t* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<int8_t>* data )
	{

	}

	void JSONSerializer::Deserialize( const int16_t* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<int16_t>* data )
	{

	}

	void JSONSerializer::Deserialize( const int32_t* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<int32_t>* data )
	{

	}

	void JSONSerializer::Deserialize( const int64_t* data )
	{

	}
	void JSONSerializer::Deserialize( const SerializableVector<int64_t>* data )
	{

	}
}