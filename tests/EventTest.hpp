#ifndef _H_EventTest
#define _H_EventTest
#include "bfu.hpp"
#include "ObjectSerializableClassBase.hpp"
#include "JSONSerializer.hpp"

#define TESTPORT 8889

std::ostream& hexdump(std::ostream& os, const void *buffer, 
                       std::size_t bufsize, bool showPrintableChars = true)
{
    if (buffer == nullptr) {
        return os;
    }
    auto oldFormat = os.flags();
    auto oldFillChar = os.fill();
    constexpr std::size_t maxline{8};
    // create a place to store text version of string
    char renderString[maxline+1];
    char *rsptr{renderString};
    // convenience cast
    const unsigned char *buf{reinterpret_cast<const unsigned char *>(buffer)};

    for (std::size_t linecount=maxline; bufsize; --bufsize, ++buf) {
        os << std::setw(2) << std::setfill('0') << std::hex 
           << static_cast<unsigned>(*buf) << ' ';
        *rsptr++ = std::isprint(*buf) ? *buf : '.';
        if (--linecount == 0) {
            *rsptr++ = '\0';  // terminate string
            if (showPrintableChars) {
                os << " | " << renderString;
            } 
            os << '\n';
            rsptr = renderString;
            linecount = std::min(maxline, bufsize);
        }
    }
    // emit newline if we haven't already
    if (rsptr != renderString) {
        if (showPrintableChars) {
            for (*rsptr++ = '\0'; rsptr != &renderString[maxline+1]; ++rsptr) {
                 os << "   ";
            }
            os << " | " << renderString;
        }
        os << '\n';
    }

    os.fill(oldFillChar);
    os.flags(oldFormat);
    return os;
}

struct Receiver
{
	int i = -1;
	static void alter(void* target, void* data)
	{
		int* arg = (int*)data;
		Receiver* _this = (Receiver*)target;
		_this->i = *arg;
	}
};

class SerializedEventArg: public bfu::SerializableClassBase<SerializedEventArg> 
{ 
public: 
	SERIALIZABLE_VAR(SerializedEventArg, uint32_t, i); 
public: 
	SerializedEventArg() 
	{}; 
	~SerializedEventArg(){}; 
}; 


bool EventTest( bfu::MemBlockBase* mBlock )
{
	bool result = true;


/////////////////////////////////
//
//
//
// local event test
//
//
//
//
/////////////////////////////////
	{
		bfu::EventSystem es;
		Receiver receiver;


		es.RegisterFastEvent("test event", sizeof(int), mBlock, false);
		bfu::Event* ev = es.GetFastEvent("test event");

		ev->RegisterCallback(&receiver, Receiver::alter);

		int arg = (int)'r';
		ev->Invoke(&arg);

		result = result && receiver.i==(int)'r';
		log::debug << "Local event callback arg: int="<<arg<<" result="<< receiver.i << std::endl;
	}


/////////////////////////////////
//
//
//
// remote event test (raw data):
//
//
//
//
/////////////////////////////////	
	{
		bfu::JSONSerializer serializer(mBlock);
		bfu::EventSystem es;
		Receiver receiver;
		int arg = (int)'r';


		es.PushPropagationTarget("127.0.0.1", TESTPORT);


		es.RegisterFastEvent("test event", sizeof(int), mBlock, true );
		bfu::Event* ev = es.GetFastEvent("test event");

		ev->RegisterCallback(&receiver, Receiver::alter);
		//ev->SetSerializer( &serializer );

		int pid = fork();

		if( pid == 0 )
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));

			ev->Invoke(&arg);

			std::cout<<"\nOut buffer:\n";
			hexdump(std::cout, es.GetNetworkBuffer(), 100);

			result = false;

			exit(0);
		}
		else
		{
			es.StartListening(TESTPORT);
			int timeout = 3;
			while(es.PullNetworkEvents()<=0)
			{
				--timeout;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				if(timeout==0)
				{
					log::error << "Network event timeout FAILED\n" << std::endl;
					break;
				} 
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			std::cout<<"\nIncoming buffer:\n";
			hexdump(std::cout, es.GetNetworkBuffer(), 100);
		}
		



		result = result && receiver.i==(int)'r';
		log::debug << "Remote event callback arg: int="<<arg<<" result="<< receiver.i << " pid:" << pid << std::endl;
	}



/////////////////////////////////
//
//
//
// remote event test (serialized data):
//
//
//
//
/////////////////////////////////
	{



		struct SerilizedReceiver
		{
			int i = -1;
			static void alter(void* target, void* data)
			{
				SerializedEventArg* arg = (SerializedEventArg*)data;
				SerilizedReceiver* _this = (SerilizedReceiver*)target;
				_this->i = arg->i;
			}
		};


		bfu::JSONSerializer serializer(mBlock);
		bfu::EventSystem es;
		SerilizedReceiver receiver;
		SerializedEventArg arg;
		arg.i = (int)'f';
		SerializedEventArg* cache = (SerializedEventArg*)SerializedEventArg::AllocateAndInit(mBlock);


		es.PushPropagationTarget("127.0.0.1", TESTPORT);


		es.RegisterFastEvent("test event", sizeof(SerializedEventArg), mBlock, true, cache );
		bfu::Event* ev = es.GetFastEvent("test event");

		ev->RegisterCallback(&receiver, SerilizedReceiver::alter);
		ev->SetSerializer( &serializer );

		int pid = fork();

		if( pid == 0 )
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			arg.i = (int)'r';

			ev->Invoke(&arg);

			std::cout<<"\nOut buffer:\n";
			hexdump(std::cout, es.GetNetworkBuffer(), 100);

			result = false;

			exit(0);
		}
		else
		{
			es.StartListening(TESTPORT);
			int timeout = 3;
			while(es.PullNetworkEvents()<=0)
			{
				--timeout;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				if(timeout==0)
				{
					log::error << "Network event timeout FAILED\n" << std::endl;
					break;
				} 
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			std::cout<<"\nIncoming buffer:\n";
			hexdump(std::cout, es.GetNetworkBuffer(), 100);
		}
		



		result = result && receiver.i==(int)'r';
		log::debug << "Remote event callback arg: int="<<arg.i<<" result="<< receiver.i << " pid:" << pid << std::endl;
	}




    if( result )
	{
		log::warning << "<<<<<<<<<<<<<<<< Event Test concluded : SUCCES\n" << std::endl;
		return true;
	}
	else
	{
		log::error << "<<<<<<<<<<<<<<<< Event Test concluded : FAILED\n" << std::endl;
		return false;		
	}
}

#endif