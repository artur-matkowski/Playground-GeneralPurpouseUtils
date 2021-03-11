#ifndef H_ObjectSerializableClassBase
#define H_ObjectSerializableClassBase
#include <vector>

namespace bfu2
{
	struct dummy{};

	struct MemberInfo
	{
		MemberInfo* next = nullptr;
		size_t offset = 0;
		const char* name = nullptr;
	};

	dummy FeedInfo(const char* name, size_t offset, MemberInfo** firstListEntry);




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



	#define SERIALIZE(C, T,i) \
		bfu2::dummy i##__LINE__ = FeedInfo(#i, offsetof(C, i), &sp_first); \
		T i; 




}


#endif