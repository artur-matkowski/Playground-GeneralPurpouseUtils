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

#define GENERATE_TEST_FOR_SIMPLE_VAR(T, value) \
	namespace testing_##T \
	{ \
		class A: public bfu2::SerializableClassBase<A> \
		{ \
		public: \
			SERIALIZABLE_VAR(A, T, i); \
		public: \
			A() \
			{}; \
			~A(){}; \
		}; \
		bool _TESTJSONStream(bfu::MemBlockBase* memBlock) \
		{ \
			char buff1[4096]; \
			char buff2[4096]; \
			 \
			bfu2::JSONSerializer serializer1(buff1, 4096, memBlock); \
			bfu2::JSONSerializer serializer2(buff2, 4096, memBlock); \
			 \
			A tt; \
			A tt2; \
			tt.i = value; \
			 \
			serializer1.Serialize(&tt); \
			 \
			serializer1.SetCursonPos(0); \
			 \
			serializer1.Deserialize(&tt2); \
			serializer2.Serialize(&tt2); \
			 \
			log::info << "Testing: " << #T << "\n\tOriginal input:\n\t\t>" << tt.i \
			 		<< "<\n\tSerialized to JSON:\n\t\t>" << serializer1.str()   \
			 		<< "<\n\tDeserialized back to type:\n\t\t>" << tt2.i \
			 		<< "<\n\tSerialized to JSON2:\n\t\t>" << serializer2.str()   \
					<< "<\n" << std::endl; \
					 \
			if( std::strcmp(serializer1.str().c_str(), serializer2.str().c_str() )==0 && tt.i==tt2.i ) \
			{ \
				log::warning << "<<<<<<<<<<<<<<<< Test concluded : SUCCES\n" << std::endl; \
				return true; \
			} \
			else \
			{ \
				log::error << "<<<<<<<<<<<<<<<< Test concluded : FAILED\n" << std::endl; \
				return false;		 \
			} \
		} \
	}

#define PROCESS_TEST_FOR_SIMPLE_VAR(T, mBlock) \
	testing_##T::_TESTJSONStream(mBlock)


GENERATE_TEST_FOR_SIMPLE_VAR(int, randI() );
GENERATE_TEST_FOR_SIMPLE_VAR(float, randF() );


	bool ObjectSerializableTests( bfu::MemBlockBase* mBlock )
	{
		bool test = true;

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(float, mBlock);


		return test;
	}
}
#endif