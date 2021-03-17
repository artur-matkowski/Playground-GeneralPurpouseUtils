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
		void Serialize_SerializablSerializableClassInterface(void* data);
		virtual void Serialize( SerializableVector<SerializableClassInterface*>* data ) override;

		virtual void Serialize( float* data ) override;
		static void Serialize_float(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<float>* data ) override;

		virtual void Serialize( double* data ) override;
		void Serialize_double(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<double>* data ) override;

		virtual void Serialize( bool* data ) override;
		void Serialize_bool(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<bool>* data ) override;

		virtual void Serialize( char* data ) override;
		void Serialize_char(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<char>* data ) override;

		virtual void Serialize( bfu::stream* data ) override;
		void Serialize_stream(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<bfu::stream>* data ) override;

		virtual void Serialize( bfu::string* data ) override;
		void Serialize_string(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<bfu::string>* data ) override;
		

		virtual void Serialize( uint8_t* data ) override;
		void Serialize_uint8_t(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<uint8_t>* data ) override;

		virtual void Serialize( uint16_t* data ) override;
		void Serialize_uint16_t(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<uint16_t>* data ) override;

		virtual void Serialize( uint32_t* data ) override;
		void Serialize_uint32_t(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<uint32_t>* data ) override;

		virtual void Serialize( uint64_t* data ) override;
		void Serialize_uint64_t(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<uint64_t>* data ) override;


		virtual void Serialize( int8_t* data ) override;
		void Serialize_int8_t(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<int8_t>* data ) override;

		virtual void Serialize( int16_t* data ) override;
		void Serialize_int16_t(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<int16_t>* data ) override;

		virtual void Serialize( int32_t* data ) override;
		static void Serialize_int32_t(JSONSerializer* serializer, void* data);
		static void Serialize_int(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<int32_t>* data ) override;

		virtual void Serialize( int64_t* data ) override;
		void Serialize_int64_t(JSONSerializer* serializer, void* data);
		virtual void Serialize( SerializableVector<int64_t>* data ) override;

		//---------------

		virtual void Deserialize( SerializableClassInterface* data ) override;
		void Deserialize_SerializablSerializableClassInterface(void* data);
		virtual void Deserialize( SerializableVector<SerializableClassInterface*>* data ) override;

		virtual void Deserialize( float* data ) override;
		void Deserialize_float(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<float>* data ) override;

		virtual void Deserialize( double* data ) override;
		void Deserialize_double(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<double>* data ) override;

		virtual void Deserialize( bool* data ) override;
		void Deserialize_bool(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<bool>* data ) override;

		virtual void Deserialize( char* data ) override;
		void Deserialize_char(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<char>* data ) override;

		virtual void Deserialize( bfu::stream* data ) override;
		void Deserialize_stream(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<bfu::stream>* data ) override;

		virtual void Deserialize( bfu::string* data ) override;
		void Deserialize_string(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<bfu::string>* data ) override;
		

		virtual void Deserialize( uint8_t* data ) override;
		void Deserialize_uint8_t(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<uint8_t>* data ) override;

		virtual void Deserialize( uint16_t* data ) override;
		void Deserialize_uint16_t(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<uint16_t>* data ) override;

		virtual void Deserialize( uint32_t* data ) override;
		void Deserialize_uint32_t(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<uint32_t>* data ) override;

		virtual void Deserialize( uint64_t* data ) override;
		void Deserialize_uint64_t(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<uint64_t>* data ) override;


		virtual void Deserialize( int8_t* data ) override;
		void Deserialize_int8_t(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<int8_t>* data ) override;

		virtual void Deserialize( int16_t* data ) override;
		void Deserialize_int16_t(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<int16_t>* data ) override;

		virtual void Deserialize( int32_t* data ) override;
		static void Deserialize_int32_t(JSONSerializer* serializer, void* data);
		static void Deserialize_int(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<int32_t>* data ) override;

		virtual void Deserialize( int64_t* data ) override;
		void Deserialize_int64_t(JSONSerializer* serializer, void* data);
		virtual void Deserialize( SerializableVector<int64_t>* data ) override;
	};
}

#endif