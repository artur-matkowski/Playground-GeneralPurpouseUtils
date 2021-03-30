#ifndef H_BinarySerializer
#define H_BinarySerializer 
#include "ObjectSerialization/SerializerBase.hpp"
//#include "Allocators/CustomAllocator.hpp"
#include <vector>

namespace bfu2
{
	class BinarySerializer: public SerializerBase
	{
		std::vector<char, bfu::custom_allocator<char>> m_buff;
		uint32_t m_readCursor = 0;
	public:
		inline void SetCursonPos(int i){ m_readCursor = i;}
		//enum class Mode {Serialize, Deserialize};

		bool operator==(const BinarySerializer&);
		void growToFitNextData(int incomingbuffsize);
		char* buff();
		uint32_t size();

		BinarySerializer( bfu::MemBlockBase* memBlock = bfu::StdAllocatorMemBlock::GetMemBlock() );
		BinarySerializer(BinarySerializer&&);

		virtual void SERIALIZER_SECTION Serialize( SerializableClassInterface* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<SerializableClassInterface>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( float* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<float>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( bool* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<bool>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( bfu::stream* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<bfu::stream>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( bfu::string* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<bfu::string>* data ) override;
		
		virtual void SERIALIZER_SECTION Serialize( uint8_t* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<uint8_t>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( uint16_t* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<uint16_t>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( uint32_t* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<uint32_t>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( uint64_t* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<uint64_t>* data ) override;

		virtual void SERIALIZER_SECTION Serialize( int8_t* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<int8_t>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( int16_t* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<int16_t>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( int32_t* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<int32_t>* data ) override;
		virtual void SERIALIZER_SECTION Serialize( int64_t* data ) override;
		virtual void SERIALIZER_SECTION Serialize( SerializableVector<int64_t>* data ) override;





		//---------------




		virtual void DESERIALIZER_SECTION Deserialize( SerializableClassInterface* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<SerializableClassInterface>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( float* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<float>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( bool* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<bool>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( bfu::stream* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<bfu::stream>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( bfu::string* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<bfu::string>* data ) override;
		
		virtual void DESERIALIZER_SECTION Deserialize( uint8_t* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<uint8_t>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( uint16_t* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<uint16_t>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( uint32_t* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<uint32_t>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( uint64_t* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<uint64_t>* data ) override;

		virtual void DESERIALIZER_SECTION Deserialize( int8_t* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<int8_t>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( int16_t* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<int16_t>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( int32_t* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<int32_t>* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( int64_t* data ) override;
		virtual void DESERIALIZER_SECTION Deserialize( SerializableVector<int64_t>* data ) override;


	};
}

#endif