#ifndef H_ObjectSerializationTests
#define H_ObjectSerializationTests 
#include "ObjectSerializableClassBase.hpp"
#include <vector>


class customSerializatorTest: bfu2::SerializableClassBase<customSerializatorTest>
{
	SERIALIZE(customSerializatorTest, int, i);
	SERIALIZE(customSerializatorTest, std::vector<float>, ii);


public:
	customSerializatorTest()
	{};
	~customSerializatorTest(){};


	
};


bool ObjectSerializableTests( bfu::MemBlockBase* mBlock )
{
	customSerializatorTest s;

	return true;
}

#endif