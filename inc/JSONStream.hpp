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
    char  m_buff[1024] = {'0'};
    JSONStream()
      :stream(m_buff, 1024)
    {
    }

    JSONStream(const JSONStream& input)
      :stream(input)
    {
    }

    ~JSONStream()
    {
    }

    JSONStream& operator>> (float& val)
    {
      skipToOneOf("-.0123456789");

      m_readCursor += sscanf(m_readCursor, "%f", &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (int64_t& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%" SCNd64, &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (int32_t& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%" SCNd32, &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (int16_t& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%" SCNd16, &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (int8_t& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%" SCNd8, &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (uint64_t& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%" SCNu64, &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (uint32_t& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%" SCNu32, &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (uint16_t& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%" SCNu16, &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (uint8_t& val)
    {
      skipToOneOf("-0123456789");

      m_readCursor += sscanf(m_readCursor, "%" SCNu8, &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& operator>> (bool& val)
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
/*
    JSONStream& operator>> ( SerializableBase& val )
    {
      val.Deserialize(*this);
      return *this;
    }
*/

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

    JSONStream& operator>> ( stream& val)
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




    JSONStream& operator<<(const float& val)
    {
      this->sprintf("%f", val);
      return *this;
    }

    JSONStream& operator<<(const int64_t& val)
    {
      this->sprintf("%" PRId64, val);
      return *this;
    }
    JSONStream& operator<<(const int32_t& val)
    {
      this->sprintf("%" PRId32, val);
      return *this;
    }
    JSONStream& operator<<(const int16_t& val)
    {
      this->sprintf("%" PRId16, val);
      return *this;
    }
    JSONStream& operator<<(const int8_t& val)
    {
      this->sprintf("%" PRId8, val);
      return *this;
    }

    JSONStream& operator<<(const uint64_t& val)
    {
      this->sprintf("%" PRIu64, val);
      return *this;
    }
    JSONStream& operator<<(const uint32_t& val)
    {
      this->sprintf("%" PRIu32, val);
      return *this;
    }
    JSONStream& operator<<(const uint16_t& val)
    {
      this->sprintf("%" PRIu16, val);
      return *this;
    }
    JSONStream& operator<<(const uint8_t& val)
    {
      this->sprintf("%" PRIu8, val);
      return *this;
    }

    JSONStream& operator<<(const bool& val)
    {
      this->sprintf("%s", (val ? "true" : "false") );
      return *this;
    }
/*
    JSONStream& operator<<( SerializableBase& val)
    {
      val.Serialize(*this);
      return *this;
    }
*/
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

    JSONStream& operator<< ( bfu::stream& val)
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
  };
}

#endif