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

		SerializableVar(const char* Name, SerializableClassBase* parent)
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
			stream << m_var;
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream >> m_var;
		}
	};

	template<>
	class SerializableVar<int64_t>: public SerializableBase
	{
		int64_t m_var;
	public:

		SerializableVar(const int64_t& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator int64_t() const
		{
			return m_var;
		}
		inline int64_t& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<int64_t>& operator=(const int64_t& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};
	template<>
	class SerializableVar<int32_t>: public SerializableBase
	{
		int32_t m_var;
	public:

		SerializableVar(const int32_t& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator int32_t() const
		{
			return m_var;
		}
		inline int32_t& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<int32_t>& operator=(const int32_t& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};
	template<>
	class SerializableVar<int16_t>: public SerializableBase
	{
		int16_t m_var;
	public:

		SerializableVar(const int16_t& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator int16_t() const
		{
			return m_var;
		}
		inline int16_t& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<int16_t>& operator=(const int16_t& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};
	template<>
	class SerializableVar<int8_t>: public SerializableBase
	{
		int8_t m_var;
	public:

		SerializableVar(const int8_t& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator int8_t() const
		{
			return m_var;
		}
		inline int8_t& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<int8_t>& operator=(const int8_t& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};

	template<>
	class SerializableVar<uint64_t>: public SerializableBase
	{
		uint64_t m_var;
	public:

		SerializableVar(const uint64_t& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator uint64_t() const
		{
			return m_var;
		}
		inline uint64_t& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<uint64_t>& operator=(const uint64_t& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};
	template<>
	class SerializableVar<uint32_t>: public SerializableBase
	{
		uint32_t m_var;
	public:

		SerializableVar(const uint32_t& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator uint32_t() const
		{
			return m_var;
		}
		inline uint32_t& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<uint32_t>& operator=(const uint32_t& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};
	template<>
	class SerializableVar<uint16_t>: public SerializableBase
	{
		uint16_t m_var;
	public:

		SerializableVar(const uint16_t& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator uint16_t() const
		{
			return m_var;
		}
		inline uint16_t& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<uint16_t>& operator=(const uint16_t& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};
	template<>
	class SerializableVar<uint8_t>: public SerializableBase
	{
		uint8_t m_var;
	public:

		SerializableVar(const uint8_t& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator uint8_t() const
		{
			return m_var;
		}
		inline uint8_t& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<uint8_t>& operator=(const uint8_t& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};

	template<>
	class SerializableVar<float>: public SerializableBase
	{
		float m_var;
	public:

		SerializableVar(const float& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator float() const
		{
			return m_var;
		}

		inline float& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<float>& operator=(const float& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};

	template<>
	class SerializableVar<bool>: public SerializableBase
	{
		bool m_var;
		char buff[6] = {0};
	public:

		SerializableVar(const bool& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator bool() const
		{
			return m_var;
		}

		inline bool& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<bool>& operator=(const bool& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}


		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};

	template<>
	class SerializableVar<bfu::stream>: public SerializableBase
	{
		bfu::stream m_var;
	public:

		SerializableVar(const bfu::stream& val)
			:m_var(val)
		{}

		SerializableVar(const char* Name, SerializableClassBase* parent)
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator bfu::stream() const
		{
			return m_var;
		}

		inline bfu::stream& GetRef()
		{
			return m_var;
		}

		inline SerializableVar<bfu::stream>& operator=(const bfu::stream& val)
		{
			m_var = val;
			return *this;
		}

		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize(m_var);
		}
		
		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize(m_var);
		}
	};


	template<>
	class SerializableVar<std::string>: public SerializableBase, public std::string
	{
		SerializableVar()
			:std::string()
			{};
	public:

		SerializableVar(const std::string& val)
			:std::string(val)
		{}


		SerializableVar(const char* Name, SerializableClassBase* parent)
			:std::string()
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		inline operator std::string() const
		{
			return *this;
		}

		inline SerializableVar<std::string>& operator=(const std::string& val)
		{
			this->assign(val);
			return *this;
		}

		inline SerializableVar<std::string>& operator=(const char* val)
		{
			this->assign(val);
			return *this;
		}


		virtual void Serialize(JSONStream& stream)
		{
			stream.Serialize( *(std::string*)this );
		}


		virtual void Deserialize(JSONStream& stream)
		{
			stream.Deserialize( *(std::string*)this );
		}
	};

}

#endif