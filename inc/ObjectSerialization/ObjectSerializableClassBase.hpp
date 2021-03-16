#ifndef H_ObjectSerializableClassBase
#define H_ObjectSerializableClassBase
#include <vector>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include "SerializerBase.hpp"

namespace bfu2
{
	struct ClassInfo
	{
		ClassInfo* next = nullptr;
		size_t offset = 0;
		const char* name = nullptr;
	};


	int FeedInfo(const char* name, size_t offset, ClassInfo** firstListEntry);

	struct SerializableClassInterface{};

	template<class T>
	class SerializableClassBase: public SerializableClassInterface
	{
	protected:
		static char s_className[255];
		static char s_NamespacedClassName[1024];

		static constexpr ClassInfo* className()
		{
			const int strl = strlen(__PRETTY_FUNCTION__);
			int i = strl;
			for(; __PRETTY_FUNCTION__[i]!=' ' && __PRETTY_FUNCTION__[i]!=':' ; --i);

			strncpy(s_className, &__PRETTY_FUNCTION__[i+1], 255 );
			s_className[ strlen(s_className)-1 ] = '\0';


			for(i = strl; __PRETTY_FUNCTION__[i]!=' ' && __PRETTY_FUNCTION__[i]!=' ' ; --i);

			strncpy(s_NamespacedClassName, &__PRETTY_FUNCTION__[i+1], 1024 );
			s_NamespacedClassName[ strlen(s_NamespacedClassName)-1 ] = '\0';

			return sp_first;
		}


	public:

		static ClassInfo* sp_first;

		SerializableClassBase()
		{
			// if(sp_first==nullptr)
			// 	std::cout<< "did not initialized\n";
		}

		static T* AllocateAndInit()
		{
			return new T();
		}
	};

	template<class T>
	char SerializableClassBase<T>::s_className[255];

	template<class T>
	char SerializableClassBase<T>::s_NamespacedClassName[1024];

	template<class T>
	ClassInfo* SerializableClassBase<T>::sp_first = className();

}


#endif