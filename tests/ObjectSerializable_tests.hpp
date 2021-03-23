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

	uint8_t randI()
	{
		return rand() % 100 - 50;
	}

	bool randB()
	{
		return (rand() % 2) == 0;
	}


	template<class T>
	const T Rand()
	{
		return (rand() % 100) * 0.01 + rand() % 100 - 50;
	}

	template<>
	const uint8_t Rand<uint8_t>()
	{
		return (rand() % 100) * 0.01 + rand() % 100 - 50;
	}
	template<>
	const int8_t Rand<int8_t>()
	{
		return (rand() % 100) * 0.01 + rand() % 100 - 50;
	}
	template<>
	const bfu::string Rand<bfu::string>()
	{
		bfu::string ret;
		ret = std::to_string( (rand() % 100) * 0.01 + rand() % 100 - 50 );
		ret += " bfu::string test";
		return ret;
	}
	template<>
	const bfu::stream Rand<bfu::stream>()
	{
		bfu::stream ret ;
		ret.sprintf("bfu::stream test %d", (rand() % 100) * 0.01 + rand() % 100 - 50);
		return ret;
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
		 
		log::info << "Testing: nested Class Test" << "\n\tOriginal input:\n\t\t>"  
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
			for(int i=0; i<10; ++i) { tt.i.push_back(value);} \
			for(int i=0; i<10; ++i) { tt.ii.push_back(value);} \
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
GENERATE_TEST_FOR_VAR_VECTOR(bool, randB() );
GENERATE_TEST_FOR_VAR_VECTOR(uint8_t, Rand<uint8_t>() );
GENERATE_TEST_FOR_VAR_VECTOR(uint16_t, Rand<uint16_t>() );
GENERATE_TEST_FOR_VAR_VECTOR(uint32_t, Rand<uint32_t>() );
GENERATE_TEST_FOR_VAR_VECTOR(uint64_t, Rand<uint64_t>() );
GENERATE_TEST_FOR_VAR_VECTOR(int8_t, Rand<int8_t>() );
GENERATE_TEST_FOR_VAR_VECTOR(int16_t, Rand<int16_t>() );
GENERATE_TEST_FOR_VAR_VECTOR(int32_t, Rand<int32_t>() );
GENERATE_TEST_FOR_VAR_VECTOR(int64_t, Rand<int64_t>() );
GENERATE_TEST_FOR_VAR_VECTOR(stream, Rand<stream>() );
GENERATE_TEST_FOR_VAR_VECTOR(string, Rand<string>() );




//////////////////////////////////////////////////////////////////////////////////




namespace nestedClassVectorTest
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
		SERIALIZABLE_OBJ_VEC(B, A, i); 
		SERIALIZABLE_OBJ_VEC(B, A, ii); 
	public: 
		B() 
		{}; 
		~B(){
		for(int j=0; j<i.size(); ++j) { bfu::MemBlockBase::DeallocateUnknown(i[j]); } 
		for(int i=0; i<ii.size(); ++i) { bfu::MemBlockBase::DeallocateUnknown(ii[i]); } 
		}; 
	}; 

	bool _TESTJSONStream(bfu::MemBlockBase* memBlock) 
	{ 
		char buff1[4096]; 
		char buff2[4096]; 
		 
		bfu2::JSONSerializer serializer1(buff1, 4096, memBlock); 
		bfu2::JSONSerializer serializer2(buff2, 4096, memBlock); 
		 
		B tt; 
		B tt2;
		for(int i=0; i<10; ++i) { tt.i.push_back( A::AllocateAndInit(memBlock) ); } 
		for(int i=0; i<10; ++i) { tt.ii.push_back( A::AllocateAndInit(memBlock) ); } 
		 
		serializer1.Serialize(&tt); 
		 
		serializer1.SetCursonPos(0); 
		 
		serializer1.Deserialize(&tt2); 
		serializer2.Serialize(&tt2); 
		 
		log::info << "Testing: nested Class Vector Test" << "\n\tOriginal input:\n\t\t>"  
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



	bool ObjectSerializableTests( bfu::MemBlockBase* mBlock )
	{
		bool test = true;

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(float, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(bool, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int8_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int16_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int32_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(int64_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(uint8_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(uint16_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(uint32_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(uint64_t, mBlock);

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(string, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR(stream, mBlock);

		test = test && nestedClassTest::_TESTJSONStream( mBlock );



		test = test && PROCESS_TEST_FOR_VAR_VECTOR(float, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(bool, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(uint8_t, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(uint16_t, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(uint32_t, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(uint64_t, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(int8_t, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(int16_t, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(int32_t, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(int64_t, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(stream, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR(string, mBlock);


		test = test && nestedClassVectorTest::_TESTJSONStream( mBlock );

		return test;
	}
}
#endif