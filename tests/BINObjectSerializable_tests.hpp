#ifndef H_BINObjectSerializationTests
#define H_BINObjectSerializationTests 
#include "ObjectSerializableClassBase.hpp"
#include "BinarySerializer.hpp"
#include <vector>
#include <stdlib.h>    
#include <time.h>

std::ostream& hex_dump(std::ostream& os, const void *buffer, 
                       std::size_t bufsize, bool showPrintableChars = true)
{
    if (buffer == nullptr) {
        return os;
    }
    auto oldFormat = os.flags();
    auto oldFillChar = os.fill();
    constexpr std::size_t maxline{8};
    // create a place to store text version of string
    char renderString[maxline+1];
    char *rsptr{renderString};
    // convenience cast
    const unsigned char *buf{reinterpret_cast<const unsigned char *>(buffer)};

    for (std::size_t linecount=maxline; bufsize; --bufsize, ++buf) {
        os << std::setw(2) << std::setfill('0') << std::hex 
           << static_cast<unsigned>(*buf) << ' ';
        *rsptr++ = std::isprint(*buf) ? *buf : '.';
        if (--linecount == 0) {
            *rsptr++ = '\0';  // terminate string
            if (showPrintableChars) {
                os << " | " << renderString;
            } 
            os << '\n';
            rsptr = renderString;
            linecount = std::min(maxline, bufsize);
        }
    }
    // emit newline if we haven't already
    if (rsptr != renderString) {
        if (showPrintableChars) {
            for (*rsptr++ = '\0'; rsptr != &renderString[maxline+1]; ++rsptr) {
                 os << "   ";
            }
            os << " | " << renderString;
        }
        os << '\n';
    }

    os.fill(oldFillChar);
    os.flags(oldFormat);
    return os;
}

namespace BINObjectSerializationTests
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





#define GENERATE_TEST_FOR_SIMPLE_VAR_BIN(T, value) \
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
		bool _TESTBINStream(bfu::MemBlockBase* memBlock) \
		{ \
			char buff1[4096]; \
			char buff2[4096]; \
			 \
			bfu2::BinarySerializer serializer1(memBlock); \
			bfu2::BinarySerializer serializer2(memBlock); \
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
			log::info << "Testing: " << #T << " of sizeof( " << (int)sizeof(T) << " ) \n\tOriginal input:\n\t\t>" << tt.i << " " << tt.ii \
			 		<< "<\n\tDeserialized back to type:\n\t\t>" << tt2.i << " " << tt2.ii << std::endl; \
			std::cout << "===================\n\tSerialized to BIN:\n"; \
			hex_dump(std::cout, serializer1.buff(), serializer1.size() ); \
			std::cout << "===================\n\tSerialized to BIN2:\n"; \
			hex_dump(std::cout, serializer2.buff(), serializer2.size() ); \
 			 \
			if( serializer1 == serializer2 && tt.i==tt2.i && tt.ii==tt2.ii ) \
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

#define PROCESS_TEST_FOR_SIMPLE_VAR_BIN(T, mBlock) \
	testing_##T::_TESTBINStream(mBlock)



GENERATE_TEST_FOR_SIMPLE_VAR_BIN(int8_t, randI()%127 );
GENERATE_TEST_FOR_SIMPLE_VAR_BIN(int16_t, randI()%16000 );
GENERATE_TEST_FOR_SIMPLE_VAR_BIN(int32_t, randI() );
GENERATE_TEST_FOR_SIMPLE_VAR_BIN(int64_t, randI() );

GENERATE_TEST_FOR_SIMPLE_VAR_BIN(uint8_t, randI()%255 );
GENERATE_TEST_FOR_SIMPLE_VAR_BIN(uint16_t, randI()%16000 );
GENERATE_TEST_FOR_SIMPLE_VAR_BIN(uint32_t, randI() );
GENERATE_TEST_FOR_SIMPLE_VAR_BIN(uint64_t, randI() );

GENERATE_TEST_FOR_SIMPLE_VAR_BIN(float, randF() );

GENERATE_TEST_FOR_SIMPLE_VAR_BIN(bool, randB() );

using bfu::string;
GENERATE_TEST_FOR_SIMPLE_VAR_BIN(string, "testing bfu::string" );

using bfu::stream;
GENERATE_TEST_FOR_SIMPLE_VAR_BIN(stream, "testing bfu::stream" );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define GENERATE_TEST_FOR_VAR_VECTOR_BIN(T, value) \
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
		bool _TESTBINStream(bfu::MemBlockBase* memBlock) \
		{ \
			char buff1[4096]; \
			char buff2[4096]; \
			 \
			bfu2::BinarySerializer serializer1(memBlock); \
			bfu2::BinarySerializer serializer2(memBlock); \
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
			 \
			log::info << "Testing vector: " << #T << " of sizeof( " << (int)sizeof(T) << " ) \n\tOriginal input:" <<std::endl;  \
			std::cout << "{"; \
			for(int i=0; i<tt.i.size(); ) \
			{	 \
				std::cout << tt.i[i]; \
				++i; \
				if(i<tt.i.size())  \
					std::cout << ", "; \
			}  \
			std::cout << "},\n{"; \
			for(int i=0; i<tt.ii.size(); ) \
			{	 \
				std::cout << tt.ii[i]; \
				++i; \
				if(i<tt.ii.size())  \
					std::cout << ", "; \
			}  \
			 		std::cout<< "}<\n\tDeserialized back to type:\n{" ; \
			for(int i=0; i<tt2.i.size(); ) \
			{	 \
				std::cout << tt2.i[i]; \
				++i; \
				if(i<tt2.i.size())  \
					std::cout << ", "; \
			}  \
			std::cout << "},\n{"; \
			for(int i=0; i<tt2.ii.size(); ) \
			{	 \
				std::cout << tt2.ii[i]; \
				++i; \
				if(i<tt2.ii.size())  \
					std::cout << ", "; \
			}  \
			std::cout << "}\n"; \
			std::cout << "===================\n\tSerialized to BIN: size( "<< serializer1.size() <<" )\n"; \
			hex_dump(std::cout, serializer1.buff(), serializer1.size() ); \
			std::cout << "===================\n\tSerialized to BIN2: size( "<< serializer2.size() <<" )\n"; \
			hex_dump(std::cout, serializer2.buff(), serializer2.size() ); \
 			 \
			if( serializer1 == serializer2 ) \
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

#define PROCESS_TEST_FOR_VAR_VECTOR_BIN(T, mBlock) \
	testing_v_##T::_TESTBINStream(mBlock)

GENERATE_TEST_FOR_VAR_VECTOR_BIN( float, randF() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( bool, randB() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( uint8_t, randI() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( uint16_t, randI() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( uint32_t, randI() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( uint64_t, randI() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( int8_t, randI() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( int16_t, randI() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( int32_t, randI() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN( int64_t, randI() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN(stream, Rand<stream>() );
GENERATE_TEST_FOR_VAR_VECTOR_BIN(string, Rand<string>() );







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
		~B(){}; 
	}; 

	bool _TESTBINStream(bfu::MemBlockBase* memBlock) 
	{ 
		bfu2::BinarySerializer serializer1(memBlock);
		bfu2::BinarySerializer serializer2(memBlock);
		 
		B tt; 
		B tt2;
		for(int i=0; i<10; ++i) { tt.i.push_back( A::AllocateAndInit(memBlock) ); } 
		for(int i=0; i<10; ++i) { tt.ii.push_back( A::AllocateAndInit(memBlock) ); } 
		 
		serializer1.Serialize(&tt); 
		 
		serializer1.SetCursonPos(0); 
		 
		serializer1.Deserialize(&tt2); 
		serializer2.Serialize(&tt2); 
		 
		log::info << "Testing: nested Class Vector Test" << std::endl; 
		std::cout << "===================\n\tSerialized to BIN: size( "<< serializer1.size() <<" )\n"; 
		hex_dump(std::cout, serializer1.buff(), serializer1.size() ); 
		std::cout << "===================\n\tSerialized to BIN2: size( "<< serializer2.size() <<" )\n"; 
		hex_dump(std::cout, serializer2.buff(), serializer2.size() ); 
				 
		if( serializer1 == serializer2  ) 
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool ObjectSerializableTests( bfu::MemBlockBase* mBlock )
	{
		bool test = true;

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(float, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(bool, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(int8_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(int16_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(int32_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(int64_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(uint8_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(uint16_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(uint32_t, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(uint64_t, mBlock);

		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(string, mBlock);
		test = test && PROCESS_TEST_FOR_SIMPLE_VAR_BIN(stream, mBlock);



		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( float, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( bool, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( uint8_t, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( uint16_t, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( uint32_t, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( uint64_t, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( int8_t, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( int16_t, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( int32_t, mBlock );
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN( int64_t, mBlock );

		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN(string, mBlock);
		test = test && PROCESS_TEST_FOR_VAR_VECTOR_BIN(stream, mBlock);

		test = test && nestedClassVectorTest::_TESTBINStream( mBlock );

		return test;
	}
}

#endif