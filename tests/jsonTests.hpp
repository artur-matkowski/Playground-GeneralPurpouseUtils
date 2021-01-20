#ifndef _H_jsonTests
#define _H_jsonTests

#include "SerializableVarVector.hpp"
#include <stdlib.h>    
#include <time.h>


float randf()
{
	return (rand() % 100) * 0.01 + rand() % 100 - 50;
}

int randi()
{
	return rand() % 100 - 50;
}

bool randb()
{
	return (rand() % 2) == 0;
}



bfu::MonotonicMemBlock<1024*1024 * 2> memBlock;



template<typename T>
bool _TESTJSONStream(const char* _typename, const T& val)
{

	bfu::JSONStream json(&memBlock);
	bfu::JSONStream json2(&memBlock);
	bfu::SerializableVar<T> tt(_typename, 0);
	bfu::SerializableVar<T> tt2(_typename, 0);
	tt = val;

	json << tt;

	json.SetCursonPos(0);

	json >> tt2;
	json2 << tt2;

	log::info << "Testing: " << _typename << "\n\tOriginal input:\n\t\t>" << tt 
	 		<< "<\n\tSerialized to JSON:\n\t\t>" << json.str()  
	 		<< "<\n\tDeserialized back to type:\n\t\t>" << tt2
	 		<< "<\n\tSerialized to JSON2:\n\t\t>" << json2.str()  
			<< "<\n" << std::endl;

	if( std::strcmp(json.str().c_str(), json2.str().c_str() )==0 )
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


#define TESTJSONStream(T,v) _TESTJSONStream<T>(#T, (T)v)


template<typename T>
bool _TESTJSONStreamVector(const char* _typename, const std::vector<T> input)
{
	bfu::JSONStream json(&memBlock);
	bfu::JSONStream json2(&memBlock);

	bfu::SerializableVarVector<T> var("var",0, &memBlock);
	bfu::SerializableVarVector<T> var2("var2",0, &memBlock);
	var = input;

	json << var;

	json.SetCursonPos(0);

	json >> var2;
	json2 << var2;

	log::info << "Testing: " << _typename
	 		<< "<\n\tSerialized to JSON:\n\t\t>" << json.str()  
	 		<< "<\n\tSerialized to JSON:\n\t\t>" << json2.str()  
			<< "<\n" << std::endl;


	if( std::strcmp(json.str().c_str(), json2.str().c_str() )==0 )
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

#define TESTJSONStreamVector(T,...) _TESTJSONStreamVector<T>( #T , {__VA_ARGS__})

bool _TESTclass()
{

	class testClass: public bfu::SerializableClassBase
	{
	public:
		bfu::SerializableVar<bool> m_var;
		bfu::SerializableVar<float> m_var2;
		bfu::SerializableVarVector<float> m_var3;
		//bfu::SerializableVar<std::string> m_var4;



	public:
		testClass()
			:bfu::SerializableClassBase((&memBlock))
			,m_var("m_var",this)
			,m_var2("m_var2",this)
			,m_var3("m_var3",this, &memBlock)
			//,m_var4("m_var4",this)
		{
			m_var = randb();
			m_var2 = randf();

			m_var3.push_back(randf());
			m_var3.push_back(randf());

			//m_var4 = "testing \"std::string";
		}

		testClass(const testClass& copy)
			:bfu::SerializableClassBase((&memBlock))
			,m_var("m_var",this)
			,m_var2("m_var2",this)
			,m_var3("m_var3",this, &memBlock)
			//,m_var4("m_var4",this)
		{
			m_var = copy.m_var;
			m_var2 = copy.m_var2;

			m_var3 = copy.m_var3;

			//m_var4 = copy.m_var4;
		}
	};

	bfu::JSONStream json;
	bfu::JSONStream json2;
	testClass tt;
	testClass tt2;

	std::cout << "tt:";

	
	std::cout << "tt2:";

	json << tt;

	json.SetCursonPos(0);

	json >> tt2;
	json2 << tt2;


	std::cout << "tt2 after deseriailze:";
	//tt2.print();

	log::info << "Testing: testClass2" 
			//<< "\n\tOriginal input:\n\t\t>" << tt 
	 		<< "<\n\tSerialized to JSON:\n\t\t>" << json.c_str()  
	 		//<< "<\n\tDeserialized back to type:\n\t\t>" << tt2
	 		<< "<\n\tSerialized to JSON2:\n\t\t>" << json2.c_str()  
			<< "<\n" << std::endl;

	if( std::strcmp(json.c_str(), json2.c_str() )==0 )
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
bool _TESTclassNested()
{

	class testClassChild: public bfu::SerializableClassBase
	{
	public:
		bfu::SerializableVar<bool> m_var;
		bfu::SerializableVar<float> m_var2;
		bfu::SerializableVarVector<float> m_var3;
		bfu::SerializableVar<std::string> m_var4;



	public:
		testClassChild()
			:bfu::SerializableClassBase((&memBlock))
			,m_var("m_var",this)
			,m_var2("m_var2",this)
			,m_var3("m_var3",this, &memBlock)
			,m_var4("m_var4",this)
		{
			m_var = randb();
			m_var2 = randf();

			m_var3.push_back(randf());
			m_var3.push_back(randf());

			m_var4 = "testing \"std::string";
		}

		testClassChild(const testClassChild& copy)
			:bfu::SerializableClassBase((&memBlock))
			,m_var("m_var",this)
			,m_var2("m_var2",this)
			,m_var3("m_var3",this, &memBlock)
			,m_var4("m_var4",this)
		{
			m_var = copy.m_var;
			m_var2 = copy.m_var2;

			m_var3 = copy.m_var3;

			m_var4 = copy.m_var4;
		}
	};


	class testClass: public bfu::SerializableClassBase
	{
	public:
		bfu::SerializableVar<bool> m_var;
		bfu::SerializableVar<float> m_var2;
		bfu::SerializableVarVector<float> m_var3;

		bfu::SerializableVar<testClassChild> m_var4;
		bfu::SerializableVarVector<testClassChild> m_var5;



	public:
		testClass()
			:bfu::SerializableClassBase((&memBlock))
			,m_var("m_var",this)
			,m_var2("m_var2",this)
			,m_var3("m_var3",this, &memBlock)
			,m_var4("m_var4",this)
			,m_var5("m_var5",this, &memBlock)
		{
			m_var = randb();
			m_var2 = randf();

			m_var3.push_back(randf());
			m_var3.push_back(randf());
			m_var3.push_back(randf());
			m_var3.push_back(randf());


			m_var5.push_back( testClassChild() );
			m_var5.push_back( testClassChild() );
			m_var5.push_back( testClassChild() );
		}
	};

	bfu::JSONStream json;
	bfu::JSONStream json2;
	testClass tt;
	testClass tt2;
	//tt = val;

	json << tt;

	json.SetCursonPos(0);

	json >> tt2;
	json2 << tt2;

	log::info << "Testing: testClass nested" 
			//<< "\n\tOriginal input:\n\t\t>" << tt 
	 		<< "<\n\tSerialized to JSON:\n\t\t>" << json.c_str()  
	 		//<< "<\n\tDeserialized back to type:\n\t\t>" << tt2
	 		<< "<\n\tSerialized to JSON2:\n\t\t>" << json2.c_str()  
			<< "<\n" << std::endl;

	if( std::strcmp(json.c_str(), json2.c_str() )==0 )
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

bool _TESTclassNestedJSON()
{
	class testClassChild: public bfu::SerializableClassBase
	{
	public:
		bfu::SerializableVar<bool> m_var;
		bfu::SerializableVar<float> m_var2;
		bfu::SerializableVarVector<float> m_var3;
		bfu::SerializableVar<std::string> m_var4;



	public:
		testClassChild()
			:bfu::SerializableClassBase()
			,m_var("m_var",this)
			,m_var2("m_var2",this)
			,m_var3("m_var3",this, &memBlock)
			,m_var4("m_var4",this)
		{
			m_var = randb();
			m_var2 = randf();

			m_var3.push_back(randf());
			m_var3.push_back(randf());

			m_var4 = "testing \"std::string";
		}

		testClassChild(const testClassChild& copy)
			:bfu::SerializableClassBase()
			,m_var("m_var",this)
			,m_var2("m_var2",this)
			,m_var3("m_var3",this, &memBlock)
			,m_var4("m_var4",this)
		{
			m_var = copy.m_var;
			m_var2 = copy.m_var2;

			m_var3 = copy.m_var3;

			m_var4 = copy.m_var4;
		}
	};


	class testClass: public bfu::SerializableClassBase
	{
	public:
		bfu::SerializableVar<bool> m_var;
		bfu::SerializableVar<float> m_var2;

		bfu::SerializableVar<bfu::JSONStream> m_var4;



	public:
		testClass()
			:bfu::SerializableClassBase()
			,m_var("m_var",this)
			,m_var2("m_var2",this)
			,m_var4("m_var4",this, &memBlock)
		{
			m_var = randb();
			m_var2 = randf();
		}
	};


	bfu::JSONStream json;
	bfu::JSONStream json2;
	testClassChild serializableObj;
	testClass tt;
	testClass tt2;


	json << serializableObj;
	//json.SetCursonPos(0);
	tt.m_var4 = json;
	

	json.clear();

	json << tt;


	json >> tt2;
	json2 << tt2;

	log::info << "Testing: nested serializableObj" 
			//<< "\n\tOriginal input:\n\t\t>" << tt 
	 		<< "<\n\tSerialized to JSON:\n\t\t>" << json.c_str()  
	 		//<< "<\n\tDeserialized back to type:\n\t\t>" << tt2
	 		<< "<\n\tSerialized to JSON2:\n\t\t>" << json2.c_str()  
			<< "<\n" << std::endl;

	if( std::strcmp(json.c_str(), json2.c_str() )==0 )
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

bool jsonTests()
{

#define SEED 1584641152

#if SEED!=0
	srand (SEED);
#else
	srand (time(NULL));

	std::cout << std::endl << "time(NULL): " << time(NULL) << std::endl;
#endif


	bool test = true;
	
	test = test && TESTJSONStream(float, randf() );
	test = test && TESTJSONStream(float, randf() );


	test = test && TESTJSONStream(int, randi() );
	test = test && TESTJSONStream(int, randi() );

	test = test && TESTJSONStream(int64_t, randi() );
	test = test && TESTJSONStream(int64_t, randi() );

	test = test && TESTJSONStream(uint64_t, (randi()+50) );
	test = test && TESTJSONStream(uint64_t, (randi()+50) );

	test = test && TESTJSONStream(int32_t, randi() );
	test = test && TESTJSONStream(int32_t, randi() );

	test = test && TESTJSONStream(uint32_t, (randi()+50) );
	test = test && TESTJSONStream(uint32_t, (randi()+50) );

	test = test && TESTJSONStream(int16_t, randi() );
	test = test && TESTJSONStream(int16_t, randi() );

	test = test && TESTJSONStream(uint16_t, (randi()+50) );
	test = test && TESTJSONStream(uint16_t, (randi()+50) );

	test = test && TESTJSONStream(int8_t, randi() );
	test = test && TESTJSONStream(int8_t, randi() );

	test = test && TESTJSONStream(uint8_t, (randi()+50) );
	test = test && TESTJSONStream(uint8_t, (randi()+50) );


	test = test && TESTJSONStream(bool, randb() );
	test = test && TESTJSONStream(bool, randb() );


	test = test && TESTJSONStream(std::string, "gowno test \"213.ad,das");



	test = test && TESTJSONStreamVector(bool, randb(), randb(), randb(), randb()); 

	test = test && TESTJSONStreamVector(float, randf(), randf(), randf(), randf() ); 

	test = test && TESTJSONStreamVector(int, randi(), randi(), randi(), randi(), randi() ); 

	test = test && TESTJSONStreamVector(std::string, "test 1", "test 2", "test 3", "test 4", "test 5" ); 


	test = test && _TESTclass();
/*
	test = test && _TESTclassNested();

	test = test && _TESTclassNestedJSON();
*/

	if( test )
	{
		log::warning << "<<<<<<<<<<<<<<<< JOSN TESTS concluded : SUCCES\n" << std::endl;
	}
	else
	{
		log::error << "<<<<<<<<<<<<<<<< JOSN TESTS concluded : FAILED\n" << std::endl;	
	}

	return test;
}

#endif