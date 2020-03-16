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

    JSONStream(const char* input)
      {
        int insize = strlen (input);
        buffsize = std::max(buffsize, insize);

        first = new char[buffsize];
        last = first+buffsize-1;
        current = first;

        std::memset(first, 0, buffsize);
        std::memcpy(first, input, insize);
      }

    ~JSONStream()
    {
    }

    JSONStream& Deserialize(float& val)
    {
      skipToOneOf("-.0123456789");

      current += sscanf(current, "%f", &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& Deserialize(int& val)
    {
      skipToOneOf("-0123456789");

      current += sscanf(current, "%d", &val);
      skipToOneOf(",]}");

      return *this;
    }

    JSONStream& Deserialize(bool& val)
    {
      skipToOneOf("tf");

      if( 0==strncmp(current, "true", 4) )
      {
        val = true;
      }
      else if( 0==strncmp(current, "false", 5) )
      {
        val = false;
      }
      
      skipToOneOf(",]}");

      return *this;
    }
/*
    JSONStream& Deserialize(std::string& val)
    {
      skipTo('\"');

      char* skipper = current+1;

      while( current!=last && *skipper != '\"' )
      {
        if(*skipper=='\\' )
        {
          ++skipper;
          if( current==last )
            break;
        }
        ++skipper;
      }
      
      val.assign(current+1, skipper);

      current = skipper;
      skipToOneOf(":,]}");

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

      char* skipper = current+1;

      while( current!=last && *skipper != '\"' )
      {
        if( *skipper=='\\' )
        {
          ++skipper;
          if( current==last )
          {
            m_status = status::NOK;
            return *this;
          }
        }
        ++skipper;
      }

      int size = skipper-current+1;
      char* buff = new char[size];

      int streamC = 1;
      int buffC = 0;

      for(;;)
      {
        if( current[streamC]=='\\' && current[streamC+1]=='\"' )
        {
          ++streamC;
        }
        else if( current[streamC]=='\"' && current[streamC-1]!='\\' )
        {
          buff[buffC] = '\0';
          break;
        }
        buff[buffC] = current[streamC];

        ++streamC;
        ++buffC;
      }
      
      val.assign(buff);

      delete buff;

      current = skipper;
      skipToOneOf(":,]}");

      return *this;
    }


    JSONStream& operator>> ( SerializableBase& val)
    {
      val.Deserialize(*this);

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
      //this->sprintf("\"%s\"", val.c_str() );

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

    JSONStream& operator<< ( SerializableBase& val)
    {
      val.Serialize(*this);

      return *this;
    }
  };
}

#endif