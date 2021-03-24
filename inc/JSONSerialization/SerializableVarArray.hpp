#ifndef _H_SerializableVarArray
#define _H_SerializableVarArray
#include "JSONSerialization/SerializableVarVector.hpp"
#include <vector>

namespace bfu
{

	template<class T>
	class SerializableVarArray: public SerializableBase
	{
		MemBlockBase* 	m_mBlock = 0;
		int 			m_mySize = 0;
		T* 				m_array = 0;

		SerializableVarArray( MemBlockBase* mBlock )
			:m_mBlock(mBlock)
		{}
	public:

		SerializableVarArray(const char* Name, SerializableClassBase* parent, int arraySize, MemBlockBase* mBlock)
			:m_mBlock(mBlock)
			,m_mySize(arraySize)
		{
			m_array = (T*) mBlock->allocate(arraySize, sizeof(T), alignof(T));

			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarArray()
		{
			m_mBlock->deallocate(m_array, m_mySize * sizeof(T));
		}


		
		SerializableVarArray<T>& operator=(const std::vector<T, custom_allocator<T> >& in)
		{
			if( in.size()>m_mySize )
			{
				m_mBlock->deallocate(m_array, m_mySize * sizeof(T));
				m_mySize = in.size();
				m_array = (T*) m_mBlock->allocate(m_mySize, sizeof(T), alignof(T));
			}

			for(int i=0; i<m_mySize; ++i)
			{
				m_array[i] = in[i];
			} 

			return *this;
		}

		SerializableVarArray<T>& operator=(const std::vector<T>& in)
		{
			if( in.size()>m_mySize )
			{
				m_mBlock->deallocate(m_array, m_mySize * sizeof(T));
				m_mySize = in.size();
				m_array = (T*) m_mBlock->allocate(m_mySize, sizeof(T), alignof(T));
			}

			for(int i=0; i<m_mySize; ++i)
			{
				m_array[i] = in[i];
			} 

			return *this;
		}

		SerializableVarArray<T>& operator=(const SerializableVarArray<T>& in)
		{
			if( in.m_mySize>m_mySize )
			{
				m_mBlock->deallocate(m_array, m_mySize * sizeof(T));
				m_mySize = in.m_mySize;
				m_array = (T*) m_mBlock->allocate(m_mySize, sizeof(T), alignof(T));
			}

			for(int i=0; i<m_mySize; ++i)
			{
				m_array[i] = in.m_array[i];
			} 

			return *this;
		}

		T& operator[](const int i)
		{
			return m_array[i];
		}

		const int size() { return m_mySize; }


		void Serialize(JSONStream& stream) override
		{
			stream.sprintf("[");

			for(auto it = m_array; ; )
			{
				stream << (*it);

				++it;

				if( it != &m_array[m_mySize] )
				{
					stream.sprintf(", ");
				}
				else
				{
					break;
				}
			}
			

			stream.sprintf("]");
		}


		void Deserialize(JSONStream& stream) override
		{
			stream.skipTo('[');
			stream.skip( 1 );

			int index = 0;

			while(stream.peak() != ']')
			{
				stream >> m_array[index];
				++index;
			}
		}
	};

	template<>
	class SerializableVarArray<bfu::string>: public SerializableBase
	{
		MemBlockBase* 	m_mBlock = 0;
		int 			m_mySize = 0;
		bfu::string* 	m_array = 0;

		SerializableVarArray( MemBlockBase* mBlock )
			:m_mBlock(mBlock)
		{}
	public:

		SerializableVarArray(const char* Name, SerializableClassBase* parent, int arraySize, MemBlockBase* mBlock )
			:m_mBlock(mBlock)
			,m_mySize(arraySize)
		{
			m_array = (bfu::string*) mBlock->allocate(arraySize, sizeof(bfu::string), alignof(bfu::string));

			if(parent!=0)
				parent->PushReferenceToMap(Name, this);
		}

		virtual ~SerializableVarArray()
		{
			m_mBlock->deallocate(m_array, m_mySize * sizeof(bfu::string));
		}

		SerializableVarArray<bfu::string>& operator=(const std::vector<bfu::string, custom_allocator<bfu::string> >& in)
		{
			if( in.size()>m_mySize )
			{
				m_mBlock->deallocate(m_array, m_mySize * sizeof(bfu::string));
				m_mySize = in.size();
				m_array = (bfu::string*) m_mBlock->allocate(m_mySize, sizeof(bfu::string), alignof(bfu::string));
			}

			for(int i=0; i<m_mySize; ++i)
			{
				m_array[i] = in[i];
			} 

			return *this;
		}

		SerializableVarArray<bfu::string>& operator=(const std::vector<bfu::string>& in)
		{
			if( in.size()>m_mySize )
			{
				m_mBlock->deallocate(m_array, m_mySize * sizeof(bfu::string));
				m_mySize = in.size();
				m_array = (bfu::string*) m_mBlock->allocate(m_mySize, sizeof(bfu::string), alignof(bfu::string));
			}

			for(int i=0; i<m_mySize; ++i)
			{
				m_array[i] = in[i];
			} 

			return *this;
		}


		SerializableVarArray<bfu::string>& operator=(const SerializableVarArray<bfu::string>& in)
		{
			if( in.m_mySize>m_mySize )
			{
				m_mBlock->deallocate(m_array, m_mySize * sizeof(bfu::string));
				m_mySize = in.m_mySize;
				m_array = (bfu::string*) m_mBlock->allocate(m_mySize, sizeof(bfu::string), alignof(bfu::string));
			}

			for(int i=0; i<m_mySize; ++i)
			{
				m_array[i] = in.m_array[i];
			} 

			return *this;
		}

		bfu::string& operator[](const int i)
		{
			return m_array[i];
		}

		const int size() { return m_mySize; }

		void Serialize(JSONStream& stream) override
		{
			stream.sprintf("[");

		
			for(auto it = m_array; ; )
			{
				stream.Serialize(*it);

				++it;

				if( it != &m_array[m_mySize] )
				{
					stream.sprintf(", ");
				}
				else
				{
					break;
				}
			}
			

			stream.sprintf("]");
		}


		void Deserialize(JSONStream& stream) override
		{
			stream.skipTo('[');
			stream.skip( 1 );

			int index = 0;


			while(stream.peak() != ']')
			{
				stream.Deserialize( m_array[index] );
				++index;
			}


		}
	};

}


#endif