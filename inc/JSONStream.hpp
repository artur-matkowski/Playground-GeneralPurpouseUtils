#ifndef _H_JSONStream
#define _H_JSONStream
#include "SerializableBase.hpp"
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include "stream.hpp"

namespace bfu{
  
  template<class T>
  class SerializableVarVector;


  class JSONStream: public stream{
  public:
    JSONStream()
      :stream()
    {
    }

    JSONStream(const int size)
      :stream(size)
    {
    }

    JSONStream(const JSONStream& input)
      :stream(input)
    {
    }

    ~JSONStream()
    {
    }

    JSONStream& Deserialize(float& val)
    {
      skipToOneOf("-.0123456789");

      m_readCursor += sscanf(m_readCursor, "%f", &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& Deserialize(int& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%d", &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& Deserialize(bool& val)
    {
      skipToOneOf("tf");

      if( 0==strncmp(m_readCursor, "true", 4) )
      {
        val = true;
      }
      else if( 0==strncmp(m_readCursor, "false", 5) )
      {
        val = false;
      }
      
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& Deserialize( SerializableBase& val )
    {
      val.Deserialize(*this);
      return *this;
    }


    JSONStream& Deserialize(std::string& val)
    {
      if(m_status < status::OK)
      {
        return *this;        
      }

      skipTo('\"');

      char* skipper = m_readCursor+1;

      while( m_readCursor!=m_last )
      {
        if( skipper[0] == '\"' && skipper[-1] != '\\' )
        {
          break;
        }

        ++skipper;
      }

      int size = skipper-m_readCursor+1;
      char* buff = new char[size];

      int buffC = 0;

      for(char* cursor = m_readCursor+1; m_readCursor<skipper; ++cursor)
      {
        if( cursor[0]=='\\' && cursor[1]=='\"' )
        {
          ++cursor;
        }
        //yes looks like shit, but this is never going to be first element of array anyway
        else if( cursor[0]=='\"' && cursor[-1]!='\\' )
        {
          buff[buffC] = '\0';
          break;
        }
        buff[buffC] = *cursor;

        ++buffC;
      }
      
      val.assign(buff);

      delete buff;

      m_readCursor = skipper;
      skipToOneOf(":,]}");

      return *this;
    }


    JSONStream& Deserialize(bfu::stream& val)
    {
      
      if(m_status < status::OK)
      {
        return *this;        
      }

      skipTo('\"');

      char* skipper = m_readCursor+1;

      while( m_readCursor!=m_last )
      {
        if( skipper[0] == '\"' && skipper[-1] != '\\' )
        {
          break;
        }

        ++skipper;
      }

      int size = skipper-m_readCursor+1;

      val.grow( size );

      for(char* cursor = m_readCursor+1; cursor<skipper; ++cursor)
      {
        if( cursor[0]=='\\' && cursor[1]=='\"' )
        {
          ++cursor;
        }
        else if( cursor[0]=='\"' && cursor[-1]!='\\' )
        {
          val.put( '\0' );
          break;
        }
        val.put( *cursor );
      }
      

      m_readCursor = skipper;
      skipToOneOf(":,]}");

      return *this;
    }


    JSONStream& operator>> ( SerializableBase& val)
    {
      val.Deserialize(*this);

      return *this;
    }

    JSONStream& operator>> ( JSONStream& val)
    {
      this->Deserialize( val );

      return *this;
    }




    JSONStream& Serialize(const float& val)
    {
      this->sprintf("%f", val);
      return *this;
    }

    JSONStream& Serialize(const int& val)
    {
      this->sprintf("%d", val);
      return *this;
    }

    JSONStream& Serialize(const bool& val)
    {
      this->sprintf("%s", (val ? "true" : "false") );
      return *this;
    }

    JSONStream& Serialize( SerializableBase& val)
    {
      val.Serialize(*this);
      return *this;
    }

    JSONStream& Serialize(const std::string& val)
    {
      const char* buff = val.c_str();
      const int buffsize = val.size();

      put('\"');

      for(int i=0; i<buffsize; ++i)
      {
        if( buff[i] == '\"' )
        {
          put('\\');
        }
        put(buff[i]);
      }

      put('\"');

      return *this;
    }

    JSONStream& Serialize(const bfu::stream& val)
    {
      int buffsize = val.size();

      put('\"');

      for(int i=0; i<buffsize; ++i)
      {
        if( val[i] == '\"' )
        {
          put('\\');
        }
        put(val[i]);
      }

      put('\"');

      return *this;
    }

    JSONStream& operator<< ( SerializableBase& val)
    {
      val.Serialize(*this);

      return *this;
    }

    JSONStream& operator<< ( JSONStream& val)
    {
      this->Serialize( val );

      return *this;
    }
  };
}

#endif