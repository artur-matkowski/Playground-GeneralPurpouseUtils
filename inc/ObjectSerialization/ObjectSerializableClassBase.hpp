#ifndef H_ObjectSerializableClassBase
#define H_ObjectSerializableClassBase
#include <vector>
#include "SerializerBase.hpp"

namespace bfu2
{
	

	typedef void (*SerializationFunc)(SerializerBase&, std::vector<char>&, void*);


	struct dummy{};

	struct MemberInfo
	{
		MemberInfo* next = nullptr;
		size_t offset = 0;
		SerializationFunc serializationFunc;
		const char* name = nullptr;
	};

	dummy FeedInfo(const char* name, size_t offset, SerializationFunc serializationFunc, MemberInfo** firstListEntry);




	template<class T>
	class SerializableClassBase
	{
	protected:

		static char s_className[255];
		static dummy initialized;


		constexpr static dummy className()
		{
			const int strl = strlen(__PRETTY_FUNCTION__);
			int i = strl;
			for(; __PRETTY_FUNCTION__[i]!=' ' && __PRETTY_FUNCTION__[i]!=':' ; --i);

			strncpy(s_className, &__PRETTY_FUNCTION__[i+1], 255 );
			s_className[ strlen(&__PRETTY_FUNCTION__[i+1])-1 ] = '\0';
			return dummy();
		}


	public:
		static MemberInfo* sp_first;
	};

	template<class T>
	MemberInfo* SerializableClassBase<T>::sp_first = nullptr;
	template<class T>
	char SerializableClassBase<T>::s_className[255];
	template<class T>
	dummy SerializableClassBase<T>::initialized /*__attribute__((__used__))*/ = SerializableClassBase<T>::className();


	template<class T>
	void Serialize(SerializerBase& serializator, std::vector<char>& v_buff, void* datafield)
	{
		serializator.Serialize(v_buff, (T*)datafield);
	}


	#define SERIALIZE(C, T,i) \
		bfu2::dummy _##i##__LINE__ = FeedInfo(#i, offsetof(C, i), \
			bfu2::Serialize<T>,  &sp_first); \
		T i; 




}


#endif