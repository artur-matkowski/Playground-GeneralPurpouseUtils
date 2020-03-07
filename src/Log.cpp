#include "Log.hpp"
#include <ctime>
#include <cstring>

log::OutStream log::Log;

char log::time[64];
time_t log::rawtime;
struct tm log::timeinfo;

char* log::getTime()
{
	std::memset(log::time, 0, 64);

	::time (&log::rawtime);
	log::timeinfo = *localtime (&log::rawtime);

	sprintf(log::time, "%d:%d:%d", log::timeinfo.tm_hour, log::timeinfo.tm_min, log::timeinfo.tm_sec);

	return log::time;
}

char* log::getDate()
{
	std::memset(log::time, 0, 64);

	::time (&log::rawtime);
	log::timeinfo = *localtime (&log::rawtime);

	sprintf(log::time, "%d-%d-%d", log::timeinfo.tm_mday, log::timeinfo.tm_mon + 1, log::timeinfo.tm_year + 1900);

	return log::time;
}

void log::OutStream::EnableFileLogging()
{
	loggingToFile = true;

	LogFileName = "LOG " + std::string(log::getDate()) + " " + std::string(log::getTime()) + ".txt";
}