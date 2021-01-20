#ifndef _H_SerializableVar
#define _H_SerializableVar
#include "JSONStream.hpp"
#include "SerializableClassBase.hpp"


namespace bfu{

	template<class T>
	class SerializableVar: public SerializableBase
	{
		T m_var;
		
		SerializableVar()
		{}
	public:

		SerializableVar(const T& val)
			:m_var(val)
		{}

		template<typename... Targs>
		SerializableVar(const char* Name, SerializableClassBase* parent, Targs... Fargs)
			:m_var(Fargs...)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}


		inline operator T() const
		{
			return m_var;
		}

		inline T& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<T>& operator=(const T& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream << (m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream >> (m_var);
		}
	};



	template<>
	class SerializableVar<bfu::string>: public SerializableBase, public bfu::string
	{
		MemBlockBase* m_mBlock = 0;

		SerializableVar()
			:bfu::string()
			{};
	public:

		SerializableVar(const bfu::string& val)
			:bfu::string(val)
			,m_mBlock(0)
		{}


		SerializableVar(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
			:bfu::string(mBlock)
			,m_mBlock(mBlock)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		explicit inline operator bfu::string() const 
		{
			return *this;
		}

		inline bfu::string& GetRef()
		{
			return *this;
		}

		inline SerializableVar<bfu::string>& operator=(const bfu::string& val)
		{
			this->assign(val);
			return *this;
		}

		inline SerializableVar<bfu::string>& operator=(const char* val)
		{
			this->assign(val);
			return *this;
		}


		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize( *(bfu::string*)this );
		}


		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize( *(bfu::string*)this );
		}

	};

}

#endif