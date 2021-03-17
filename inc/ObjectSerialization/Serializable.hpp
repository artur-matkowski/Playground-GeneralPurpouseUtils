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

	SERIALIZABLE_VECTOR( char );
	SERIALIZABLE_VECTOR( uint8_t );
	SERIALIZABLE_VECTOR( int8_t );
	SERIALIZABLE_VECTOR( uint16_t );
	SERIALIZABLE_VECTOR( int16_t );
	SERIALIZABLE_VECTOR( uint32_t );
	SERIALIZABLE_VECTOR( int32_t );
	SERIALIZABLE_VECTOR( uint64_t );
	SERIALIZABLE_VECTOR( int64_t );
	SERIALIZABLE_VECTOR( float );
	SERIALIZABLE_VECTOR( double );

	class JSONSerializer;
	typedef void (JSONSerializer::*funcFlaot)(const float*);
	//typedef void (JSONSerializer::*Func)(void*);


	#define SERIALIZABLE_VAR(C, T,i) \
		T i; \
		static inline void initVar_##i() __attribute__((constructor)) \
		{ \
			static bool isRegistered = false; \
			if( isRegistered==false ) \
			{ \
				FeedInfo(#i, offsetof(C, i), sizeof(i), &C::sp_first, \
				bfu2::JSONSerializer::Serialize_##T, \
				0); \
				isRegistered = true; \
			} \
		}
}

		// 		(bfu2::Func) (bfu2::funcFlaot) bfu2::JSONSerializer::Serialize, \
		// 		(bfu2::Func) (bfu2::funcFlaot) bfu2::JSONSerializer::Deserialize); \
		// 		isRegistered = true;} \
		// }
#endif
