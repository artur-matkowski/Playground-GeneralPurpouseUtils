#ifndef _H_jsonTests
#define _H_jsonTests

#include "SerializableVarVector.hpp"

using namespace bfu;

class testClass2: public SerializableClassBase
{
public:
	SerializableVar<bool> m_var;
	SerializableVar<float> m_var2;
	SerializableVarVector<float> m_var3;
	SerializableVar<std::string> m_var4;



public:
	testClass2()
		:SerializableClassBase()
		,m_var("m_var",this)
		,m_var2("m_var2",this)
		,m_var3("m_var3",this)
		,m_var4("m_var4",this)
	{
		m_var = true;
		m_var2 = 2.00123;

		m_var3.push_back(1.2);
		m_var3.push_back(1.1);

		m_var4 = "testing \"std::string";
	}

	testClass2(const testClass2& copy)
		:SerializableClassBase()
		,m_var("m_var",this)
		,m_var2("m_var2",this)
		,m_var3("m_var3",this)
		,m_var4("m_var4",this)
	{
		m_var = true;
		m_var2 = 2.00123;

		m_var3.push_back(1.2);
		m_var3.push_back(1.1);

		m_var4 = "testing \"std::string";
	}
};


class testClass: public SerializableClassBase
{
public:
	SerializableVar<bool> m_var;
	SerializableVar<float> m_var2;
	SerializableVarVector<float> m_var3;

	SerializableVar<testClass2> m_var4;
	SerializableVarVector<testClass2> m_var5;



public:
	testClass()
		:SerializableClassBase()
		,m_var("m_var",this)
		,m_var2("m_var2",this)
		,m_var3("m_var3",this)
		,m_var4("m_var4",this)
		,m_var5("m_var5",this)
	{
		m_var = true;
		m_var2 = 2.00123;

		m_var3.push_back(1.2);
		m_var3.push_back(1.1);
		m_var3.push_back(3.2);
		m_var3.push_back(13.2);


		m_var5.push_back( testClass2() );
		m_var5.push_back(testClass2());
		m_var5.push_back(testClass2());
	}
};



template<typename T>
bool _TESTJSONStream(const char* _typename, const T& val)
{
	JSONStream json;
	JSONStream json2;
	SerializableVar<T> tt(_typename, 0);
	SerializableVar<T> tt2(_typename, 0);
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


#define TESTJSONStream(T,v) _TESTJSONStream<T>(#T, v)


template<typename T>
bool _TESTJSONStreamVector(const char* _typename, const std::vector<T> input)
{
	JSONStream json;
	JSONStream json2;

	SerializableVarVector<T> var("var",0);
	SerializableVarVector<T> var2("var2",0);
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


void jsonTests()
{
		bool test = true;
	
	test = test && TESTJSONStream(float, -2.342);
	test = test && TESTJSONStream(float, 2);


	test = test && TESTJSONStream(int, 3);
	test = test && TESTJSONStream(int, -2);


	test = test && TESTJSONStream(bool, false);
	test = test && TESTJSONStream(bool, true);


	test = test && TESTJSONStream(std::string, "gowno test \\\"213.ad,das");



	test = test && TESTJSONStreamVector(bool, true, false, true, true); 

	test = test && TESTJSONStreamVector(float, 1.2, -2.3, 3.4, -4.5 ); 

	test = test && TESTJSONStreamVector(int, 1, -2, 3, -4, 7 ); 

	test = test && TESTJSONStreamVector(std::string, "test 1", "test 2", "test 3", "test 4", "test 5" ); 




	{
		JSONStream json;
		JSONStream json2;
		testClass tt;
		testClass tt2;
		//tt = val;

		json << tt;

		json.SetCursonPos(0);

		json >> tt2;
		json2 << tt2;

		log::info << "Testing: testClass2" 
				//<< "\n\tOriginal input:\n\t\t>" << tt 
		 		<< "<\n\tSerialized to JSON:\n\t\t>" << json.str()  
		 		//<< "<\n\tDeserialized back to type:\n\t\t>" << tt2
		 		<< "<\n\tSerialized to JSON2:\n\t\t>" << json2.str()  
				<< "<\n" << std::endl;

		if( std::strcmp(json.str().c_str(), json2.str().c_str() )==0 )
		{
			log::warning << "<<<<<<<<<<<<<<<< Test concluded : SUCCES\n" << std::endl;
			test = test && true;
		}
		else
		{
			log::error << "<<<<<<<<<<<<<<<< Test concluded : FAILED\n" << std::endl;
			test = test && false;		
		}
	}


	if( test )
	{
		log::warning << "<<<<<<<<<<<<<<<< TESTS concluded : SUCCES\n" << std::endl;
	}
	else
	{
		log::error << "<<<<<<<<<<<<<<<< TESTS concluded : FAILED\n" << std::endl;	
	}
}

#endif