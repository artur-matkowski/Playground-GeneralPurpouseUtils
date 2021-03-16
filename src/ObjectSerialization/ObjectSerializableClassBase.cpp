#include "ObjectSerializableClassBase.hpp"
#include <iostream>

namespace bfu2
{
	ClassInfo infos[1024];

	//cant be constexpr as I need to be able togrow array if is to shr
	int FeedInfo(const char* name, size_t offset, ClassInfo** firstListEntry)
	{
		printf("%s\n", name);
		static int freeIndex = 0;

		ClassInfo* free = &infos[freeIndex];
		++freeIndex;

		free->name = name;
		free->offset = offset;


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