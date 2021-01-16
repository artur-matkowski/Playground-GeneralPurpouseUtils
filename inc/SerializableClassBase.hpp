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
    	char  m_buff[1024] = {'0'};
    	stream m_token;
		//member name, member reference
		std::map<std::string, SerializableBase*> m_membersMap;

		friend class JSONStream;

		//you need to have a copy constructor in your class for that to work
		//virtual SerializableClassBase(const SerializableClassBase& ) = 0;

	public:

		SerializableClassBase(std::allocator<char> alloc = std::allocator<char>() )
			:m_token(m_buff, 1024, alloc)
		{};

		virtual ~SerializableClassBase();

		virtual void Serialize(JSONStream& stream);

		virtual void Deserialize(JSONStream& stream);

		virtual void PushReferenceToMap(const char* memberName, SerializableBase* memberReference)
		{
			m_membersMap[memberName] = memberReference;
		}


		void print();
	};

}


#endif