#ifndef H_ObjectSerializationTests
#define H_ObjectSerializationTests 
#include "ObjectSerializableClassBase.hpp"
#include "JSONSerializer.hpp"
#include <vector>
#include <stdlib.h>    
#include <time.h>

namespace ObjectSerializationTests
{
	float randF()
	{
		return (rand() % 100) * 0.01 + rand() % 100 - 50;
	}

	int randI()
	{
		return rand() % 100 - 50;
	}

	bool randB()
	{
		return (rand() % 2) == 0;
	}




	template<class T>
	class customSerializatorTest: public bfu2::SerializableClassBase<customSerializatorTest<T>>
	{
	public:
		SERIALIZABLE_VAR(customSerializatorTest, T, i);


	public:
		customSerializatorTest()
		{};
		~customSerializatorTest(){};


		
	};


	template<typename T>
	bool _TESTJSONStream(const char* _typename, const T& val, bfu::MemBlockBase* memBlock)
	{
		char buff1[4096];
		char buff2[4096];

		bfu2::JSONSerializer serializer1(buff1, 4096, memBlock);
		bfu2::JSONSerializer serializer2(buff2, 4096, memBlock);

		customSerializatorTest<T> tt;
		customSerializatorTest<T> tt2;
		tt.i = val;

		serializer1.Serialize(&tt);
		//json << tt;

		serializer1.SetCursonPos(0);

		serializer1.Deserialize(&tt2);
		//json >> tt2;
		serializer2.Serialize(&tt2);
		//json2 << tt2;

		log::info << "Testing: " << _typename << "\n\tOriginal input:\n\t\t>" << tt.i
		 		<< "<\n\tSerialized to JSON:\n\t\t>" << serializer1.str()  
		 		<< "<\n\tDeserialized back to type:\n\t\t>" << tt2.i
		 		<< "<\n\tSerialized to JSON2:\n\t\t>" << serializer2.str()  
				<< "<\n" << std::endl;

		if( std::strcmp(serializer1.str().c_str(), serializer2.str().c_str() )==0 && tt.i==tt2.i )
		{
			log::warning << "<<<<<<<<<<<<<<<< Test concluded : SUCCES\n" << std::endl;
			return true;
		}
		else
		{
			log::error << "<<<<<<<<<<<<<<<< Test concluded : FAILED\n" << std::endl;
			return false;		
		}
	}

	#define TTESTJSONStream(T,v, m) _TESTJSONStream<T>(#T, (T)v, m)


	bool ObjectSerializableTests( bfu::MemBlockBase* mBlock )
	{
		bool test = true;

		test = test && TTESTJSONStream(float, randF(), mBlock);

		//bfu2::SerializableClassInterface* p = new customSerializatorTest<float>();

		return test;
	}
}
#endif