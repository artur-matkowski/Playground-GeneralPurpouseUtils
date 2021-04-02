#include "ObjectSerializableClassBase.hpp"
#include <iostream>

namespace bfu
{
	ClassInfo* ClassInfo::operator[](const char* name)
	{
		ClassInfo* it = this;

		for(; it!=nullptr; it = it->next)
		{
			if(strcmp(name, it->name)==0)
				break;
		}
		return it;
	}


	ClassInfo infos[1024];

	//cant be constexpr as I need to be able togrow array if is to shr
	int  FeedInfo(const char* name
				, size_t offset
				, size_t hash_code
				, ClassInfo** firstListEntry
				, Func jsonserialize
				, Func jsondeserialize)
	{
		static int freeIndex = 0;

		ClassInfo* free = &infos[freeIndex];
		++freeIndex;

		free->name = name;
		free->offset = offset;
		free->hash_code = hash_code;
		free->jsonSerializeFunc = jsonserialize;
		free->jsonDeserializeFunc = jsondeserialize;


		if(*firstListEntry==nullptr)
		{
			*firstListEntry = free;
		}
		else
		{
			ClassInfo* lastListEntry = *firstListEntry;

			for(; 	lastListEntry->next!=0; 
					lastListEntry = lastListEntry->next );

			lastListEntry->next = free;
		}

		return 0;
	}
}