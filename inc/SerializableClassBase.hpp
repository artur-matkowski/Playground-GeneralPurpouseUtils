#ifndef _H_SerializableClassBase
#define _H_SerializableClassBase
#include "SerializableBase.hpp"
//#include <cstdlib>
#include <cstring>
#include <map>
#include "stream.hpp"

namespace bfu{
	
	class stream;

	struct cmpByStringLength {
	    bool operator()(const char* a, const char* b) const {
	    	return std::strcmp(a, b) < 0;
	    }
	};

	class SerializableClassBase: public SerializableBase
	{
    	stream m_token;
		//member name, member reference
		std::map<const char*, SerializableBase*, cmpByStringLength> m_membersMap;

		friend class JSONStream;

		//you need to have a copy constructor in your class for that to work
		//virtual SerializableClassBase(const SerializableClassBase& ) = 0;

	public:

		SerializableClassBase()
			:m_token()
		{};

		virtual ~SerializableClassBase();

		virtual void Serialize(JSONStream& stream);

		virtual void Deserialize(JSONStream& stream);

		virtual void PushReferenceToMap(const char* memberName, SerializableBase* memberReference)
		{
			char* token = new char[ strlen(memberName) ];
			strcpy( token, memberName );

			m_membersMap[token] = memberReference;
		}


		void print();
	};

}


#endif