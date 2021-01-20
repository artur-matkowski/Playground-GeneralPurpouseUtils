#ifndef _H_SerializableVarVector
#define _H_SerializableVarVector
#include "SerializableVar.hpp"
#include <vector>

namespace bfu{

	template<class T>
	class SerializableVarVector: public std::vector<T, custom_allocator<T> >, public SerializableBase
	{
		SerializableVarVector( MemBlockBase* mBlock )
			:std::vector<T, custom_allocator<T> >( custom_allocator<T>(mBlock) )
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock )
			:std::vector<T, custom_allocator<T> >( custom_allocator<T>(mBlock) )
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{}


		
		SerializableVarVector<T>& operator=(const std::vector<T, custom_allocator<T> >& in)
		{
			this->clear();

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

			return *this;
		}

		SerializableVarVector<T>& operator=(const std::vector<T>& in)
		{
			this->clear();

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

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
	class SerializableVarVector<bfu::string>: public std::vector<bfu::string, custom_allocator<bfu::string> >, public SerializableBase
	{
		SerializableVarVector( MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
			:std::vector<bfu::string, custom_allocator<bfu::string> >( custom_allocator<bfu::string>(mBlock) )
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
			:std::vector<bfu::string, custom_allocator<bfu::string> >( custom_allocator<bfu::string>(mBlock) )
		{
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{}

		SerializableVarVector<bfu::string>& operator=(const std::vector<bfu::string, custom_allocator<bfu::string> >& in)
		{
			this->clear();

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

			return *this;
		}

		SerializableVarVector<bfu::string>& operator=(const std::vector<bfu::string>& in)
		{
			this->clear();

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

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
			bfu::string cache;

			while(stream.peak() != ']')
			{
				//deserializationCache.Deserialize(stream);
				stream.Deserialize( cache );

				this->push_back( cache );
			}


		}
	};



	template<class T>
	class SerializableVarVector<T*>: public std::vector<T*, custom_allocator<T*> >, public SerializableBase
	{
		SerializableVarVector( MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
			:std::vector<T*, custom_allocator<T*>>( custom_allocator<T*>(mBlock) )
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
			:std::vector<T*, custom_allocator<T*>>( custom_allocator<T*>(mBlock) )
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

		
		SerializableVarVector<T*>& operator=(const std::vector<T, custom_allocator<T*> >& in)
		{
			this->clear();

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

			return *this;
		}

		SerializableVarVector<T*>& operator=(const std::vector<T*>& in)
		{
			this->clear();

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

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
	class SerializableVarVector<bfu::string*>: public std::vector<bfu::string*, custom_allocator<bfu::string*> >, public SerializableBase
	{
		SerializableVarVector( MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
			:std::vector<bfu::string*, custom_allocator<bfu::string*> >( custom_allocator<bfu::string*>(mBlock) )
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
			:std::vector<bfu::string*, custom_allocator<bfu::string*> >( custom_allocator<bfu::string*>(mBlock) )
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


		SerializableVarVector<bfu::string*>& operator=(const std::vector<bfu::string*, custom_allocator<bfu::string*> >& in)
		{
			this->clear();

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

			return *this;
		}

		SerializableVarVector<bfu::string*>& operator=(const std::vector<bfu::string*>& in)
		{
			this->clear();

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

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
				bfu::string* cache = new bfu::string;
				//deserializationCache.Deserialize(stream);
				stream.Deserialize( *cache );

				this->push_back( cache );
			}


		}
	};

}


#endif