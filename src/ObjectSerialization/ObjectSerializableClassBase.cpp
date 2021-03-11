#include "ObjectSerializableClassBase.hpp"
#include <iostream>

namespace bfu2
{
	MemberInfo infos[1024];

	//cant be constexpr as I need to be able togrow array if is to shr
	dummy FeedInfo(const char* name, size_t offset, SerializationFunc serializationFunc, MemberInfo** firstListEntry)
	{
		//std::cout <<  name << "\n";
		static int freeIndex = 0;

		MemberInfo* free = &infos[freeIndex];
		++freeIndex;

		free->name = name;
		free->offset = offset;


		if(*firstListEntry==nullptr)
		{
			*firstListEntry = free;
		}
		else
		{
			MemberInfo* lastListEntry = *firstListEntry;

			for(; 	lastListEntry->next!=0; 
					lastListEntry = lastListEntry->next );

			lastListEntry->next = free;
		}

		return dummy();
	}

}