#ifndef H_ObjectSerializableClassBase
#define H_ObjectSerializableClassBase
#include <vector>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include "SerializerBase.hpp"

namespace bfu2
{
	class JSONSerializer;
	typedef void (*Func)(JSONSerializer*, void*);

	struct ClassInfo
	{
		ClassInfo* next = nullptr;
		size_t offset = 0;
		size_t sizeOf = 0;
		Func jsonSerializeFunc = nullptr;
		Func jsonDeserializeFunc = nullptr;
		const char* name = nullptr;

		ClassInfo* operator[](const char*);
	};


	int FeedInfo(const char* name, size_t offset, size_t sizeOf, ClassInfo** firstListEntry, Func jsonserialize, Func jsondeserialize);

	class SerializableClassInterface
	{
	public:
	public:
		virtual ClassInfo* GetFirstClassInfo() const = 0;
	};

	template<class T>
	class SerializableClassBase: public SerializableClassInterface
	{
	protected:
		static char s_className[255];
		static char s_NamespacedClassName[1024];
		int s;

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

		virtual ClassInfo* GetFirstClassInfo() const override { return sp_first; };

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