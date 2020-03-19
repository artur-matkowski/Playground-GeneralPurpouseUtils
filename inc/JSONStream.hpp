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

      m_current += sscanf(m_current, "%f", &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& Deserialize(int& val)
    {
      skipToOneOf("-0123456789");

      m_current += sscanf(m_current, "%d", &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& Deserialize(bool& val)
    {
      skipToOneOf("tf");

      if( 0==strncmp(m_current, "true", 4) )
      {
        val = true;
      }
      else if( 0==strncmp(m_current, "false", 5) )
      {
        val = false;
      }
      
      skipToOneOf(",]}");

      return *this;
    }


    JSONStream& Deserialize(std::string& val)
    {
      if(m_status < status::OK)
      {
        return *this;        
      }

      skipTo('\"');

      char* skipper = m_current+1;

      while( m_current!=m_last && *skipper != '\"' )
      {
        if( *skipper=='\\' )
        {
          ++skipper;
          if( m_current==m_last )
          {
            m_status = status::NOK;
            return *this;
          }
        }
        ++skipper;
      }

      int size = skipper-m_current+1;
      char* buff = new char[size];

      int streamC = 1;
      int buffC = 0;

      for(;;)
      {
        if( m_current[streamC]=='\\' && m_current[streamC+1]=='\"' )
        {
          ++streamC;
        }
        else if( m_current[streamC]=='\"' && m_current[streamC-1]!='\\' )
        {
          buff[buffC] = '\0';
          break;
        }
        buff[buffC] = m_current[streamC];

        ++streamC;
        ++buffC;
      }
      
      val.assign(buff);

      delete buff;

      m_current = skipper;
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

      char* skipper = m_current+1;

      while( m_current!=m_last && *skipper != '\"' )
      {
        if( *skipper=='\\' )
        {
          ++skipper;
          if( m_current==m_last )
          {
            m_status = status::NOK;
            return *this;
          }
        }
        ++skipper;
      }

      int size = skipper-m_current+1;
      char* buff = new char[size];

      val.grow( size );

      int streamC = 1;
      int buffC = 0;

      for(;;)
      {
        if( m_current[streamC]=='\\' && m_current[streamC+1]=='\"' )
        {
          ++streamC;
        }
        else if( m_current[streamC]=='\"' && m_current[streamC-1]!='\\' )
        {
          //buff[buffC] = '\0';
          val.put( '\0' );
          break;
        }
        //buff[buffC] = m_current[streamC];
        val.put( m_current[streamC] );

        ++streamC;
        ++buffC;
      }
      
      //val.assign(buff);

      delete buff;

      m_current = skipper;
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