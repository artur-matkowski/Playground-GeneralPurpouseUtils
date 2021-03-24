#ifndef H_ObjectSerializableClassBase
#define H_ObjectSerializableClassBase
#include <vector>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include "Allocators/MemBlockBase.hpp"

namespace bfu2
{
	template <bool, typename T = void>
	struct enable_if {
	};
	template <typename T>
	struct enable_if<true, T> {
	    typedef T type;
	};


	typedef bfu::MemBlockBase* MemBlockBasePtr;


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
	    static U constructCandidate(bfu::MemBlockBase* mBlock, typename enable_if<ConstructoFinder<U>::value, U>::type* = 0) {
	        return U(mBlock);
	    }

	    /**
	     * Fallback for element types without two-int signatures.
	     */
	    template <class U>
	    static U constructCandidate(bfu::MemBlockBase* mBlock,typename enable_if<!ConstructoFinder<U>::value, U>::type* = 0) {
	        return U();
	    }

	    template <class U>
	    static U* constructPtrCandidate(bfu::MemBlockBase* mBlock, typename enable_if<ConstructoFinder<U>::value, U>::type* = 0) {
	    	U* ret = (U*)mBlock->allocate(1, sizeof(U), alignof(U));
	    	new (ret) U(mBlock);
	        return ret;
	    }

	    template <class U>
	    static U* constructPtrCandidate(bfu::MemBlockBase* mBlock,typename enable_if<!ConstructoFinder<U>::value, U>::type* = 0) {
	    	U* ret = (U*)mBlock->allocate(1, sizeof(U), alignof(U));
	    	new (ret) U();
	        return ret;
	    }

	};



	class SerializerBase;
	class SerializableClassInterface;
	typedef void (*Func)(SerializerBase*, void*);
	typedef SerializableClassInterface* (*AllocateAndInit)(bfu::MemBlockBase*);

	struct ClassInfo
	{
		ClassInfo* next = nullptr;
		size_t offset = 0;
		size_t hash_code = 0;
		Func jsonSerializeFunc = nullptr;
		Func jsonDeserializeFunc = nullptr;

		const char* name = nullptr;

		ClassInfo* operator[](const char*);

	};


	int FeedInfo(const char* name
				, size_t offset
				, size_t hash_code
				, ClassInfo** firstListEntry
				, Func jsonserialize
				, Func jsondeserialize);

	class SerializableClassInterface
	{
	public:
	public:
		virtual ClassInfo* GetFirstClassInfo() const = 0;
		virtual void Dispouse() = 0;

		virtual void PostDeserializationCallback(){};
		virtual void PreSerializationCallback(){};
	};

	template<class T>
	class SerializableClassBase: public SerializableClassInterface
	{
	protected:
		static char s_className[255];
		static char s_NamespacedClassName[1024];
		
		static constexpr ClassInfo* className()
		{
			const int strl = strlen(__PRETTY_FUNCTION__);
			int i = strl;
			for(; __PRETTY_FUNCTION__[i]!=' ' && __PRETTY_FUNCTION__[i]!=':' ; --i);

			strncpy(s_className, &__PRETTY_FUNCTION__[i+1], 255 );
			s_className[ strlen(s_className)-1 ] = '\0';


			for(i = strl; __PRETTY_FUNCTION__[i]!=' ' && __PRETTY_FUNCTION__[i]!=' ' ; --i);

			strncpy(s_NamespacedClassName, &__PRETTY_FUNCTION__[i+1], 1024 );
			s_NamespacedClassName[ strlen(s_NamespacedClassName)-1 ] = '\0';

			return sp_first;
		}


	public:

		static ClassInfo* sp_first;

		virtual ClassInfo* GetFirstClassInfo() const override { return sp_first; };

		SerializableClassBase()
		{
		}

		static SerializableClassInterface* AllocateAndInit(bfu::MemBlockBase* mBlock)
		{
			SerializableClassInterface* ret = (SerializableClassInterface*)ConditionalBuilder::constructPtrCandidate<T>(mBlock);
			return ret;
		}
		virtual void Dispouse() override
		{
			bfu::MemBlockBase::DeallocateUnknown(this);
		}
	};

	template<class T>
	char SerializableClassBase<T>::s_className[255];

	template<class T>
	char SerializableClassBase<T>::s_NamespacedClassName[1024];

	template<class T>
	ClassInfo* SerializableClassBase<T>::sp_first = className();

}


#endif