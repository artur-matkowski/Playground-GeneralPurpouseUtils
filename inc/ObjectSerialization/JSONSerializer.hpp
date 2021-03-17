#ifndef H_JSONSerializer
#define H_JSONSerializer 
#include "SerializerBase.hpp"

namespace bfu2
{
	class JSONSerializer: public SerializerBase, public bfu::stream
	{
	public:
		using bfu::stream::stream;

		virtual void Serialize( SerializableClassInterface* data ) override;
		
		virtual void Serialize( SerializableVector<SerializableClassInterface*>* data ) override;

		virtual void Serialize( float* data ) override;
		
		virtual void Serialize( SerializableVector<float>* data ) override;

		virtual void Serialize( double* data ) override;
		
		virtual void Serialize( SerializableVector<double>* data ) override;

		virtual void Serialize( bool* data ) override;
		
		virtual void Serialize( SerializableVector<bool>* data ) override;

		virtual void Serialize( char* data ) override;
		
		virtual void Serialize( SerializableVector<char>* data ) override;

		virtual void Serialize( bfu::stream* data ) override;
		
		virtual void Serialize( SerializableVector<bfu::stream>* data ) override;

		virtual void Serialize( bfu::string* data ) override;
		
		virtual void Serialize( SerializableVector<bfu::string>* data ) override;
		

		virtual void Serialize( uint8_t* data ) override;
		
		virtual void Serialize( SerializableVector<uint8_t>* data ) override;

		virtual void Serialize( uint16_t* data ) override;
		
		virtual void Serialize( SerializableVector<uint16_t>* data ) override;

		virtual void Serialize( uint32_t* data ) override;
		
		virtual void Serialize( SerializableVector<uint32_t>* data ) override;

		virtual void Serialize( uint64_t* data ) override;
		
		virtual void Serialize( SerializableVector<uint64_t>* data ) override;


		virtual void Serialize( int8_t* data ) override;
		
		virtual void Serialize( SerializableVector<int8_t>* data ) override;

		virtual void Serialize( int16_t* data ) override;
		
		virtual void Serialize( SerializableVector<int16_t>* data ) override;

		virtual void Serialize( int32_t* data ) override;
		
		
		virtual void Serialize( SerializableVector<int32_t>* data ) override;

		virtual void Serialize( int64_t* data ) override;
		
		virtual void Serialize( SerializableVector<int64_t>* data ) override;





		//---------------





		virtual void Deserialize( SerializableClassInterface* data ) override;
		
		virtual void Deserialize( SerializableVector<SerializableClassInterface*>* data ) override;

		virtual void Deserialize( float* data ) override;
		
		virtual void Deserialize( SerializableVector<float>* data ) override;

		virtual void Deserialize( double* data ) override;
		
		virtual void Deserialize( SerializableVector<double>* data ) override;

		virtual void Deserialize( bool* data ) override;
		
		virtual void Deserialize( SerializableVector<bool>* data ) override;

		virtual void Deserialize( char* data ) override;
		
		virtual void Deserialize( SerializableVector<char>* data ) override;

		virtual void Deserialize( bfu::stream* data ) override;
		
		virtual void Deserialize( SerializableVector<bfu::stream>* data ) override;

		virtual void Deserialize( bfu::string* data ) override;
		
		virtual void Deserialize( SerializableVector<bfu::string>* data ) override;
		

		virtual void Deserialize( uint8_t* data ) override;
		
		virtual void Deserialize( SerializableVector<uint8_t>* data ) override;

		virtual void Deserialize( uint16_t* data ) override;
		
		virtual void Deserialize( SerializableVector<uint16_t>* data ) override;

		virtual void Deserialize( uint32_t* data ) override;
		
		virtual void Deserialize( SerializableVector<uint32_t>* data ) override;

		virtual void Deserialize( uint64_t* data ) override;
		
		virtual void Deserialize( SerializableVector<uint64_t>* data ) override;


		virtual void Deserialize( int8_t* data ) override;
		
		virtual void Deserialize( SerializableVector<int8_t>* data ) override;

		virtual void Deserialize( int16_t* data ) override;
		
		virtual void Deserialize( SerializableVector<int16_t>* data ) override;

		virtual void Deserialize( int32_t* data ) override;
		
		
		virtual void Deserialize( SerializableVector<int32_t>* data ) override;

		virtual void Deserialize( int64_t* data ) override;
		
		virtual void Deserialize( SerializableVector<int64_t>* data ) override;
	};
}

#endif