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
			SERIALIZABLE_VAR(A, T, ii); \
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
			tt.ii = value; \
			 \
			serializer1.Serialize(&tt); \
			 \
			serializer1.SetCursonPos(0); \
			 \
			serializer1.Deserialize(&tt2); \
			serializer2.Serialize(&tt2); \
			 \
			log::info << "Testing: " << #T << "\n\tOriginal input:\n\t\t>" << tt.i << " " << tt.ii \
			 		<< "<\n\tSerialized to JSON:\n\t\t>" << serializer1.str()   \
			 		<< "<\n\tDeserialized back to type:\n\t\t>" << tt2.i << " " << tt2.ii \
			 		<< "<\n\tSerialized to JSON2:\n\t\t>" << serializer2.str()   \
					<< "<\n" << std::endl; \
					 \
			if( std::strcmp(serializer1.str().c_str(), serializer2.str().c_str() )==0 && tt.i==tt2.i && tt.ii==tt2.ii ) \
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


GENERATE_TEST_FOR_SIMPLE_VAR(int8_t, randI()%127 );
GENERATE_TEST_FOR_SIMPLE_VAR(int16_t, randI()%16000 );
GENERATE_TEST_FOR_SIMPLE_VAR(int32_t, randI() );
GENERATE_TEST_FOR_SIMPLE_VAR(int64_t, randI() );

GENERATE_TEST_FOR_SIMPLE_VAR(uint8_t, randI()%255 );
GENERATE_TEST_FOR_SIMPLE_VAR(uint16_t, randI()%16000 );
GENERATE_TEST_FOR_SIMPLE_VAR(uint32_t, randI() );
GENERATE_TEST_FOR_SIMPLE_VAR(uint64_t, randI() );

GENERATE_TEST_FOR_SIMPLE_VAR(float, randF() );

GENERATE_TEST_FOR_SIMPLE_VAR(bool, randB() );

using bfu::string;
GENERATE_TEST_FOR_SIMPLE_VAR(string, "testing bfu::string" );

using bfu::stream;
GENERATE_TEST_FOR_SIMPLE_VAR(stream, "testing bfu::stream" );


//////////////////////////////////////////////////////////////////////////////////////

namespace nestedClassTest
{
	class A: public bfu2::SerializableClassBase<A> 
	{ 
	public: 
		SERIALIZABLE_VAR(A, int32_t, i); 
		SERIALIZABLE_VAR(A, float, ii); 
	public: 
		A() 
		{
			i = randI();
			ii = randF();
		}; 
		~A(){}; 
	}; 

	class B: public bfu2::SerializableClassBase<B> 
	{ 
	public: 
		SERIALIZABLE_OBJ(B, A, i); 
		SERIALIZABLE_OBJ(B, A, ii); 
	public: 
		B() 
		{}; 
		~B(){}; 
	}; 

	bool _TESTJSONStream(bfu::MemBlockBase* memBlock) 
	{ 
		char buff1[4096]; 
		char buff2[4096]; 
		 
		bfu2::JSONSerializer serializer1(buff1, 4096, memBlock); 
		bfu2::JSONSerializer serializer2(buff2, 4096, memBlock); 
		 
		B tt; 
		B tt2; 
		 
		serializer1.Serialize(&tt); 
		 
		serializer1.SetCursonPos(0); 
		 
		serializer1.Deserialize(&tt2); 
		serializer2.Serialize(&tt2); 
		 
		log::info << "Testing: nestedClassTest" << "\n\tOriginal input:\n\t\t>"  
		 		<< "<\n\tSerialized to JSON:\n\t\t>" << serializer1.str()   
		 		<< "<\n\tDeserialized back to type:\n\t\t>" 
		 		<< "<\n\tSerialized to JSON2:\n\t\t>" << serializer2.str()   
				<< "<\n" << std::endl; 
				 
		if( std::strcmp(serializer1.str().c_str(), serializer2.str().c_str() )==0  ) 
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
}

//////////////////////////////////////////////////////////////////////////////////


#define GENERATE_TEST_FOR_VAR_VECTOR(T, value) \
	namespace testing_v_##T \
	{ \
		class A: public bfu2::SerializableClassBase<A> \
		{ \
		public: \
			SERIALIZABLE_VAR_VEC(A, T, i); \
			SERIALIZABLE_VAR_VEC(A, T, ii); \
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
			tt.i = { value, value, value, value, value, value, value, value, value }; \
			tt.ii = { value, value, value, value, value, value, value, value, value }; \
			 \
			serializer1.Serialize(&tt); \
			 \
			serializer1.SetCursonPos(0); \
			 \
			serializer1.Deserialize(&tt2); \
			serializer2.Serialize(&tt2); \
			 \
			log::info << "Testing: " << #T << "\n\tOriginal input:\n\t\t>"  \
			 		<< "<\n\tSerialized to JSON:\n\t\t>" << serializer1.str()   \
			 		<< "<\n\tDeserialized back to type:\n\t\t>"  \
			 		<< "<\n\tSerialized to JSON2:\n\t\t>" << serializer2.str()   \
					<< "<\n" << std::endl; \
					 \
			if( std::strcmp(serializer1.str().c_str(), serializer2.str().c_str() )==0 && tt.i==tt2.i && tt.ii==tt2.ii ) \
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

#define PROCESS_TEST_FOR_VAR_VECTOR(T, mBlock) \
	testing_v_##T::_TESTJSONStream(mBlock)


GENERATE_TEST_FOR_VAR_VECTOR(float, randF() );




//////////////////////////////////////////////////////////////////////////////////



class A: public bfu2::SerializableClassBase<A> 
{ 
public: 
	SERIALIZABLE_VAR_VEC(A, float, i); 
public: 
	A() 
	{}; 
	~A(){}; 
}; 

	bool ObjectSerializableTests( bfu::MemBlockBase* mBlock )
	{
		bool test = true;

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int8_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int16_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int32_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int64_t, mBlock);

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(uint8_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(uint16_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(uint32_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(uint64_t, mBlock);

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(float, mBlock);

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(bool, mBlock);

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(string, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(stream, mBlock);


		test = test && nestedClassTest::_TESTJSONStream( mBlock );

		test = test && PROCESS_TEST_FOR_VAR_VECTOR(float, mBlock);


		return test;
	}
}
#endif