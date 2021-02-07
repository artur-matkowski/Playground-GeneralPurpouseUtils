#ifndef _H_SerializableVarVector
#define _H_SerializableVarVector
#include "SerializableVar.hpp"
#include <vector>

namespace bfu{


	// Or we can use enable_if from Boost:
	template <bool, typename T = void>
	struct enable_if {
	};
	template <typename T>
	struct enable_if<true, T> {
	    typedef T type;
	};

	typedef MemBlockBase* MemBlockBasePtr;


	template <typename T>
	struct ConstructoFinder {
	    /* If T provides a constructor matching this signature, this is the declaration of SFINAE that will succeed,
	     * of size 4 bytes
	     */
	    template<typename U>
	    static int32_t SFINAE(decltype(U(MemBlockBasePtr()))*);

	    /* Otherwise the ellipsis will accept just about anything (and has minimum priority) so in the fallback case
	     * we'll use this definition and SFINAE will be 1 byte big
	     */
	    template<typename U>
	    static int8_t SFINAE(...);

	    // Check what size SFINAE ended up being, this tells us if the constructor matched the right signature or not
	    static const bool value = sizeof(SFINAE<T>(nullptr)) == sizeof(int32_t);
	};

	class ConditionalBuilder {
	public:

	    /**
	     * Construct an element which has a constructor with two int arguments.
	     */
	    template <class U>
	    /* Here we have a dummy argument which defaults to a null pointer of type U* if there is a 2-int constructor.
	     *
	     * Otherwise the resolution of enable_if will fail. The compiler will quietly discard this method
	     * during overload resolution and call the no-arg constructor version instead.
	     */
	    static U constructCandidate(MemBlockBase* mBlock, typename enable_if<ConstructoFinder<U>::value, U>::type* = 0) {
	        return U(mBlock);
	    }

	    /**
	     * Fallback for element types without two-int signatures.
	     */
	    template <class U>
	    static U constructCandidate(MemBlockBase* mBlock,typename enable_if<!ConstructoFinder<U>::value, U>::type* = 0) {
	        return U();
	    }

	};


	template<class T>
	class SerializableVarVector: public std::vector<T, custom_allocator<T> >, public SerializableBase
	{
		MemBlockBase* m_mBlock = 0;
		SerializableVarVector( MemBlockBase* mBlock )
			:std::vector<T, custom_allocator<T> >( custom_allocator<T>(mBlock) )
			,m_mBlock(mBlock)
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock )
			:std::vector<T, custom_allocator<T> >( custom_allocator<T>(mBlock) )
			,m_mBlock(mBlock)
		{
			std::vector<T, custom_allocator<T> >::reserve(16);
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{}


		
		SerializableVarVector<T>& operator=(const std::vector<T, custom_allocator<T> >& in)
		{
			this->clear();

			this->reserve( in.size() );

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

			return *this;
		}

		SerializableVarVector<T>& operator=(const std::vector<T>& in)
		{
			this->clear();

			this->reserve( in.size() );

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
			T cache = ConditionalBuilder::constructCandidate<T>(m_mBlock);

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
		MemBlockBase* m_mBlock = 0;
		SerializableVarVector( MemBlockBase* mBlock )
			:std::vector<bfu::string, custom_allocator<bfu::string> >( custom_allocator<bfu::string>(mBlock) )
			,m_mBlock(mBlock)
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock )
			:std::vector<bfu::string, custom_allocator<bfu::string> >( custom_allocator<bfu::string>(mBlock) )
			,m_mBlock(mBlock)
		{
			std::vector<bfu::string, custom_allocator<bfu::string> >::reserve(16);
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{}

		SerializableVarVector<bfu::string>& operator=(const std::vector<bfu::string, custom_allocator<bfu::string> >& in)
		{
			this->clear();

			this->reserve( in.size() );

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

			return *this;
		}

		SerializableVarVector<bfu::string>& operator=(const std::vector<bfu::string>& in)
		{
			this->clear();

			this->reserve( in.size() );

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
			bfu::string cache(m_mBlock);

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
		MemBlockBase* m_mBlock = 0;
		SerializableVarVector( MemBlockBase* mBlock )
			:std::vector<T*, custom_allocator<T*>>( custom_allocator<T*>(mBlock) )
			,m_mBlock(mBlock)
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock  )
			:std::vector<T*, custom_allocator<T*>>( custom_allocator<T*>(mBlock) )
			,m_mBlock(mBlock)
		{
			std::vector<T*, custom_allocator<T*> >::reserve(16);
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{
			
		}

		
		SerializableVarVector<T*>& operator=(const std::vector<T*, custom_allocator<T*> >& in)
		{
			this->clear();

			this->reserve( in.size() );

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

			return *this;
		}

		SerializableVarVector<T*>& operator=(const std::vector<T*>& in)
		{
			this->clear();

			this->reserve( in.size() );

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
				//delete *it;
				m_mBlock->deallocate(*it, sizeof(T));
			}
			this->clear();

			stream.skipTo('[');
			stream.skip( 1 );

			//SerializableVar<T> deserializationCache("", 0);

			while(stream.peak() != ']')
			{
				//T* cache = new T;
				T* cache = (T*)m_mBlock->allocate(1, sizeof(T), alignof(T));
				//deserializationCache.Deserialize(stream);
				stream >>( *cache );

				this->push_back( cache );
			}


		}
	};
/*
	template<>
	class SerializableVarVector<bfu::string*>: public std::vector<bfu::string*, custom_allocator<bfu::string*> >, public SerializableBase
	{
		MemBlockBase* m_mBlock = 0;
		SerializableVarVector( MemBlockBase* mBlock )
			:std::vector<bfu::string*, custom_allocator<bfu::string*> >( custom_allocator<bfu::string*>(mBlock) )
			,m_mBlock(mBlock)
		{}
	public:

		SerializableVarVector(const char* Name, SerializableClassBase* parent, MemBlockBase* mBlock )
			:std::vector<bfu::string*, custom_allocator<bfu::string*> >( custom_allocator<bfu::string*>(mBlock) )
			,m_mBlock(mBlock)
		{
			std::vector<bfu::string*, custom_allocator<bfu::string*> >::reserve(16);
			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarVector()
		{

		}


		SerializableVarVector<bfu::string*>& operator=(const std::vector<bfu::string*, custom_allocator<bfu::string*> >& in)
		{
			this->clear();

			this->reserve( in.size() );

			std::copy(in.begin(), in.end(), std::back_inserter(*this)); 

			return *this;
		}

		SerializableVarVector<bfu::string*>& operator=(const std::vector<bfu::string*>& in)
		{
			this->clear();

			this->reserve( in.size() );

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
				//delete *it;
				m_mBlock->deallocate(*it, sizeof(bfu::string));
			}
			this->clear();

			stream.skipTo('[');
			stream.skip( 1 );

			//SerializableVar<T> deserializationCache("", 0);

			while(stream.peak() != ']')
			{
				bfu::string* cache = (bfu::string*)m_mBlock->allocate(1, sizeof(bfu::string*), alignof(bfu::string*));
				//deserializationCache.Deserialize(stream);
				stream.Deserialize( *cache );

				this->push_back( cache );
			}


		}
	};*/

}


#endif