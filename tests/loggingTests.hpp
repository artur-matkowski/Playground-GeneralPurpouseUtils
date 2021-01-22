#ifndef _H_loggingTests
#define _H_loggingTests
#include "testsbase.hpp"
#include "log.hpp"

bool loggingTests( bfu::MemBlockBase* mBlock )
{
	//log::Log.EnableFileLogging();

	unsigned char t[] = "testing unsined char*";

	log::error << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
  	log::warning << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::info << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::info << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::info << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::info << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::info << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::info << "Hello Log! dadf adfads df asdf fsg sdfg sdfgs dfg dafsadf sfsf sfd sd sdf s s" << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::info << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::debug << "Hello Log! " << 2 << " " << __FUNCTION__ << ":" << __LINE__ << std::endl;
	log::info << "unsigned char: " << t << std::endl;

	return true;
}

#endif