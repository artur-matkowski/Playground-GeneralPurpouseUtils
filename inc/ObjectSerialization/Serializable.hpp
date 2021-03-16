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


	#define SERIALIZABLE_VAR(C, T,i) \
		T i; \
		static inline void initVar_##i() __attribute__((constructor)) \
		{ \
			static bool isRegistered = false; \
			if( isRegistered==false ){ \
				FeedInfo(#i, offsetof(C, i), &C::sp_first); \
				isRegistered = true;} \
		}
}

#endif
