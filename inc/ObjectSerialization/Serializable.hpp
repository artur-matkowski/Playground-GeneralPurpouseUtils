#ifndef H_Serializable
#define H_Serializable
#include <vector>
#include "stream.hpp"
#include "ObjectSerializableClassBase.hpp"
#include "CustomAllocator.hpp"

namespace bfu2
{
	#define SERIALIZABLE_VECTOR(T) \
		template<> \
		class SerializableVector<T>: public std::vector<T, bfu::custom_allocator<T>> \
		{ \
			bfu::MemBlockBase* m_mBlock = 0; \
		public: \
			using std::vector<T, bfu::custom_allocator<T>>::vector; \
			\
			SerializableVector( bfu::MemBlockBase* mBlock = bfu::StdAllocatorMemBlock::GetMemBlock() )  \
				:std::vector<T, bfu::custom_allocator<T>>( bfu::custom_allocator<T>(mBlock) ) \
				,m_mBlock(mBlock) \
			{} \
			bfu::MemBlockBase* mBlock() { return m_mBlock; } \
		}

	class SerializableClassInterface;

	template<class T>
	class SerializableVector: public std::vector<SerializableClassInterface*, bfu::custom_allocator<SerializableClassInterface*>> 
	{
		bfu::MemBlockBase* m_mBlock = 0;
	public:
		using std::vector<SerializableClassInterface*, bfu::custom_allocator<SerializableClassInterface*>>::vector;
		AllocateAndInit allocateAndInit = nullptr;

		SerializableVector( bfu::MemBlockBase* mBlock = bfu::StdAllocatorMemBlock::GetMemBlock() )
			:std::vector<SerializableClassInterface*, bfu::custom_allocator<SerializableClassInterface*>>( bfu::custom_allocator<SerializableClassInterface*>(mBlock) )
			,m_mBlock(mBlock)
		{
			allocateAndInit = T::AllocateAndInit;
		}

		~SerializableVector()
		{
			for(int j=0; j<size(); ++j) 
			{ 
				( (T*) this->operator[](j) )->~T();
				bfu::MemBlockBase::DeallocateUnknown( this->operator[](j) ); 
			}
		}

		bfu::MemBlockBase* mBlock() { return m_mBlock; }
	};

	SERIALIZABLE_VECTOR( uint8_t );
	SERIALIZABLE_VECTOR( int8_t );
	SERIALIZABLE_VECTOR( uint16_t );
	SERIALIZABLE_VECTOR( int16_t );
	SERIALIZABLE_VECTOR( uint32_t );
	SERIALIZABLE_VECTOR( int32_t );
	SERIALIZABLE_VECTOR( uint64_t );
	SERIALIZABLE_VECTOR( int64_t );
	SERIALIZABLE_VECTOR( float );
	SERIALIZABLE_VECTOR( bool );
	SERIALIZABLE_VECTOR( bfu::string );
	SERIALIZABLE_VECTOR( bfu::stream );

	template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
	{
	    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
	}

	#define SERIALIZABLE_VAR(C, T, i) \
		T i; \
		static inline void initVar_##i() __attribute__((constructor)) \
		{ \
			static bool isRegistered = false; \
			if( isRegistered==false ) \
			{ \
				FeedInfo(#i, offsetOf(&C::i), typeid(T).hash_code(), &C::sp_first, \
				bfu2::SerializerBase::Serialize_##T, \
				bfu2::SerializerBase::Deserialize_##T); \
				isRegistered = true; \
			} \
		} 

	#define SERIALIZABLE_OBJ(C, T, i) \
		T i; \
		static inline void initVar_##i() __attribute__((constructor)) \
		{ \
			static bool isRegistered = false; \
			if( isRegistered==false ) \
			{ \
				FeedInfo(#i, offsetOf(&C::i), typeid(T).hash_code(), &C::sp_first, \
				bfu2::SerializerBase::Serialize_SerializableClassInterface, \
				bfu2::SerializerBase::Deserialize_SerializableClassInterface); \
				isRegistered = true; \
			} \
		} 


	#define SERIALIZABLE_VAR_VEC(C, T, i) \
		bfu2::SerializableVector<T> i; \
		static inline void initVar_v_##i() __attribute__((constructor)) \
		{ \
			static bool isRegistered = false; \
			if( isRegistered==false ) \
			{ \
				FeedInfo(#i, offsetOf(&C::i), typeid(T).hash_code(), &C::sp_first, \
				bfu2::SerializerBase::Serialize_v_##T, \
				bfu2::SerializerBase::Deserialize_v_##T); \
				isRegistered = true; \
			} \
		} 

	#define SERIALIZABLE_OBJ_VEC(C, T, i) \
		bfu2::SerializableVector<T> i; \
		static inline void initVar_v_##i() __attribute__((constructor)) \
		{ \
			static bool isRegistered = false; \
			if( isRegistered==false ) \
			{ \
				FeedInfo(#i, offsetOf(&C::i), typeid(T).hash_code(), &C::sp_first, \
				bfu2::SerializerBase::Serialize_v_SerializableClassInterface, \
				bfu2::SerializerBase::Deserialize_v_SerializableClassInterface); \
				isRegistered = true; \
			} \
		} 
}

#endif
