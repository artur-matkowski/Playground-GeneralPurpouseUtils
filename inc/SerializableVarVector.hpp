#ifndef _H_SerializableVarVector
#define _H_SerializableVarVector
#include "SerializableVar.hpp"
#include <vector>

namespace bfu{

	template<class T>
	class SerializableVarVector: public std::vector<T>, public SerializableBase
	{
		SerializableVarVector()
			:std::vector<T>()
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent)
			:std::vector<T>()
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{}


		//TODO optimize me:
		SerializableVarVector<T>& operator=(const std::vector<T>& in)
		{
			this->clear();

			for(auto it = in.begin(); it != in.end(); ++it)
			{
				this->push_back(*it);
			}

			return *this;
		}

		void Serialize(JSONStream& stream) override
		{
			stream.sprintf("[");

			if( this->begin() != this->end() )
			{
				for(auto it = this->begin(); ; )
				{
					//stream << *it;
					stream << (*it);

					++it;

					if( it != this->end() )
					{
						stream.sprintf(", ");
					}
					else
					{
						break;
					}
				}
			}

			stream.sprintf("]");
		}


		void Deserialize(JSONStream& stream) override
		{
			this->clear();

			stream.skipTo('[');
			stream.skip( 1 );

			//SerializableVar<T> deserializationCache("", 0);
			T cache;

			while(stream.peak() != ']')
			{
				//deserializationCache.Deserialize(stream);
				stream >> ( cache );

				this->push_back( cache );
			}


		}
	};

	template<>
	class SerializableVarVector<std::string>: public std::vector<std::string>, public SerializableBase
	{
		SerializableVarVector()
			:std::vector<std::string>()
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent)
			:std::vector<std::string>()
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{}


		//TODO optimize me:
		SerializableVarVector<std::string>& operator=(const std::vector<std::string>& in)
		{
			this->clear();

			for(auto it = in.begin(); it != in.end(); ++it)
			{
				this->push_back(*it);
			}

			return *this;
		}

		void Serialize(JSONStream& stream) override
		{
			stream.sprintf("[");

			if( this->begin() != this->end() )
			{
				for(auto it = this->begin(); ; )
				{
					//stream << *it;
					stream.Serialize(*it);

					++it;

					if( it != this->end() )
					{
						stream.sprintf(", ");
					}
					else
					{
						break;
					}
				}
			}

			stream.sprintf("]");
		}


		void Deserialize(JSONStream& stream) override
		{
			this->clear();

			stream.skipTo('[');
			stream.skip( 1 );

			//SerializableVar<T> deserializationCache("", 0);
			std::string cache;

			while(stream.peak() != ']')
			{
				//deserializationCache.Deserialize(stream);
				stream.Deserialize( cache );

				this->push_back( cache );
			}


		}
	};



	template<class T>
	class SerializableVarVector<T*>: public std::vector<T*>, public SerializableBase
	{
		SerializableVarVector()
			:std::vector<T*>()
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent)
			:std::vector<T*>()
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{
			for(auto it = this->begin(); it!=this->end(); ++it)
			{
				delete *it;
			}
		}


		//TODO optimize me:
		SerializableVarVector<T*>& operator=(const std::vector<T*>& in)
		{
			this->clear();

			for(auto it = in.begin(); it != in.end(); ++it)
			{
				this->push_back(*it);
			}

			return *this;
		}

		void Serialize(JSONStream& stream) override
		{
			stream.sprintf("[");

			if( this->begin() != this->end() )
			{
				for(auto it = this->begin(); ; )
				{
					//stream << *it;
					stream <<(**it);

					++it;

					if( it != this->end() )
					{
						stream.sprintf(", ");
					}
					else
					{
						break;
					}
				}
			}

			stream.sprintf("]");
		}


		void Deserialize(JSONStream& stream) override
		{
			for(auto it = this->begin(); it!=this->end(); ++it)
			{
				delete *it;
			}
			this->clear();

			stream.skipTo('[');
			stream.skip( 1 );

			//SerializableVar<T> deserializationCache("", 0);

			while(stream.peak() != ']')
			{
				T* cache = new T;
				//deserializationCache.Deserialize(stream);
				stream >>( *cache );

				this->push_back( cache );
			}


		}
	};

	template<>
	class SerializableVarVector<std::string*>: public std::vector<std::string*>, public SerializableBase
	{
		SerializableVarVector()
			:std::vector<std::string*>()
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent)
			:std::vector<std::string*>()
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{
			for(auto it = this->begin(); it!=this->end(); ++it)
			{
				delete *it;
			}
		}


		//TODO optimize me:
		SerializableVarVector<std::string*>& operator=(const std::vector<std::string*>& in)
		{
			this->clear();

			for(auto it = in.begin(); it != in.end(); ++it)
			{
				this->push_back(*it);
			}

			return *this;
		}

		void Serialize(JSONStream& stream) override
		{
			stream.sprintf("[");

			if( this->begin() != this->end() )
			{
				for(auto it = this->begin(); ; )
				{
					//stream << *it;
					stream.Serialize(**it);

					++it;

					if( it != this->end() )
					{
						stream.sprintf(", ");
					}
					else
					{
						break;
					}
				}
			}

			stream.sprintf("]");
		}


		void Deserialize(JSONStream& stream) override
		{
			for(auto it = this->begin(); it!=this->end(); ++it)
			{
				delete *it;
			}
			this->clear();

			stream.skipTo('[');
			stream.skip( 1 );

			//SerializableVar<T> deserializationCache("", 0);

			while(stream.peak() != ']')
			{
				std::string* cache = new std::string;
				//deserializationCache.Deserialize(stream);
				stream.Deserialize( *cache );

				this->push_back( cache );
			}


		}
	};

}


#endif