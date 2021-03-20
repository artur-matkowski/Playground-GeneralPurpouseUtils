#ifndef H_Serializable
#define H_Serializable
#include <vector>
#include "ObjectSerializableClassBase.hpp"

namespace bfu2
{
	#define SERIALIZABLE_VECTOR(T) \
		template<> \
		class SerializableVector<T>: public std::vector<T> \
		{ \
		public: \
			using std::vector<T>::vector; \
		}

	template<class T>
	class SerializableVector: public std::vector<T*> 
	{
	public:
		using std::vector<T*>::vector;
	};


	class SerializableClassInterface;

	template<>
	class SerializableVector<SerializableClassInterface>: public std::vector<SerializableClassInterface*> 
	{
	public:
		using std::vector<SerializableClassInterface*>::vector;
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
				FeedInfo(#i, offsetOf(&C::i), sizeof(T), &C::sp_first, \
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
				FeedInfo(#i, offsetOf(&C::i), sizeof(i), &C::sp_first, \
				bfu2::SerializerBase::Serialize_SerializableClassInterface, \
				bfu2::SerializerBase::Deserialize_SerializableClassInterface); \
				isRegistered = true; \
			} \
		} 
}

#endif
