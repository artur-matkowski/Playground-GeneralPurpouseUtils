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

#define PROCESS_TEST_FOR_SIMPLE_VAR(T, mBlock) \
	testing_##T::_TESTBINStream(mBlock)



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

		return test;
	}
}

#endif