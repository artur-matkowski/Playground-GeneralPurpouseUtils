#ifndef _H_SerializableClassBase
#define _H_SerializableClassBase
#include "SerializableBase.hpp"
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
		friend class JSONStream;

    	//char  m_buff[256] = {'0'};
	protected:
    	//stream m_token;
		//member name, member reference
		
		std::map<stream
				, SerializableBase*
				, std::less<stream>
				, custom_allocator<std::pair<const stream, SerializableBase*> > >		m_membersMap;


		//you need to have a copy constructor in your class for that to work
		//virtual SerializableClassBase(const SerializableClassBase& ) = 0;
		MemBlockBase* m_mBlock;

	public:

		SerializableClassBase( MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
			:m_membersMap( custom_allocator<std::pair<const bfu::string, SerializableBase*> >(mBlock) )
			,m_mBlock(mBlock)
		{};

		virtual ~SerializableClassBase();

		virtual void Serialize(JSONStream& stream);

		virtual void Deserialize(JSONStream& stream);

		virtual void PushReferenceToMap(const char* memberName, SerializableBase* memberReference)
		{
			stream name(memberName, m_mBlock);
			
			m_membersMap[name] = memberReference;
		}

		template<typename Functor>
		void IterateOverSerializableMembers( Functor fPtr )
		{
			for(auto it = m_membersMap.begin(); it != m_membersMap.end(); ++it)
			{
				fPtr( it->first, it->second );
			}
		}


		void print();
	};

}


#endif