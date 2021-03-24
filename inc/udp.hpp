#ifndef H_UDP
#define	H_UDP
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

#include "JSONSerialization/SerializableVarVector.hpp"

#define PACKAGESIZE 65507


namespace bfu{
	class udp
	{
	public:
		class packet: public SerializableClassBase
		{
    		char  m_buff[PACKAGESIZE] = {'0'};
		public:
			SerializableVar<stream> m_id;
			SerializableVar<JSONStream> m_data;
			#define HOSTSIZE 16
			char m_host[HOSTSIZE] = {0};
			int m_port;
			MemBlockBase* m_mBlock;

			packet( MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() )
				:SerializableClassBase(mBlock)
				,m_id("m_id",this, m_buff, PACKAGESIZE, mBlock)
				,m_data("m_data",this, mBlock)
				,m_mBlock(mBlock)
			{}

			packet(const packet& cp)
				:SerializableClassBase(cp.m_mBlock)
				,m_id("m_id",this, m_buff, PACKAGESIZE, cp.m_mBlock)
				,m_data("m_data",this, cp.m_mBlock)
				,m_mBlock(cp.m_mBlock)
			{
				m_id = cp.m_id;
				m_data = cp.m_data;
				m_port = cp.m_port;

				std::strncpy(m_host, cp.m_host, HOSTSIZE);
			}

			void SetHost(const char* host)
			{
				std::strncpy(m_host, host, HOSTSIZE);
			}

			void SetData(SerializableClassBase& data)
			{
				m_data.GetRef().clear();
				m_data.GetRef() << data;
			}

			void SetId(const char* data)
			{
				m_id.GetRef().clear();
				m_id.GetRef() << data;
			}

			void clear()
			{
				m_id.GetRef().clear();
				m_data.GetRef().clear();
			}
		};

	private:
		int m_socket = -1; 
		int m_port = -1;
		MemBlockBase* m_mBlock;
		unsigned int slen = sizeof(sockaddr_in);
		packet m_cache;
		struct sockaddr_in si_me, si_other;
		JSONStream m_json;

	
	public:

		udp(int Port = -1, MemBlockBase* mBlock = StdAllocatorMemBlock::GetMemBlock() );
		udp(MemBlockBase* mBlock);
		~udp();

		bool StartListening(int port);
		void StopListening();

		bool Read( packet &out, bool isBlocking );
		bool Write( packet &in );
		bool Write( SerializableClassBase &in, const char* eventId, const char* host, int port);
		
		bfu::string Read(bfu::string & remoteHost);
		void Read(char* outBuff, int buffSize);
		void Read(char* outBuff, int buffSize, bfu::string & remoteHost);
		static void Write(const bfu::string & buff, const char* host, int port);
		static void Write(const char * buff, int buffsize, const char* host, int port);

		int GetPort();
	};
}




#endif