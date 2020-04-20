#ifndef _H_SerializableBase
#define _H_SerializableBase

#define STRINGIFY(x) #x

namespace bfu{

	class JSONStream;

	class SerializableBase
	{
		
	public:

		virtual ~SerializableBase(){}
		
		virtual void Serialize(JSONStream& stream) = 0;

		virtual void Deserialize(JSONStream& stream) = 0;
	};

}


#endif