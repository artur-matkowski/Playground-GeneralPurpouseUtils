#ifndef H_LOG
#define H_LOG
#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <fstream>
#include "stream.hpp"


enum class DebugLevel {
	ALL,
    INFO,
    WARNING,
    ERROR
};

#ifndef LOG_LEVEL
#define LOG_LEVEL DebugLevel::ALL
#endif

#define error Log(__FILE__,__LINE__)(DebugLevel::ERROR)
#define warning Log(__FILE__,__LINE__)(DebugLevel::WARNING)
#define info Log(__FILE__,__LINE__)(DebugLevel::INFO)
#define debug Log(__FILE__,__LINE__)(DebugLevel::ALL)




class log {

	static char 		time[];
	static time_t 		rawtime;
	static struct tm 	timeinfo;
	

    static char* getTime();
    static char* getDate();

public:
        /*  other log class methods/properties
            ...
        */

        

        // out stream object
        static struct OutStream {

                char  m_buff[1024] = {'0'};
                bfu::stream     	stream;
                DebugLevel 			level = DebugLevel::ALL;
                bool 				loggingToFile = false;
                char           		LogFileName[1024] = {'0'};
               	std::ofstream 		outfile;
                const char*         path = "./Logs/";

                inline const char* LogLvl(DebugLevel lvl)
                {
                	switch(lvl)
                	{
                		case DebugLevel::ALL:
                			return "  [DEBUG]    ";
                		case DebugLevel::INFO:
                			return "  [INFO]     ";
                		case DebugLevel::WARNING:
                			return "  [WARNING]  ";
                		case DebugLevel::ERROR:
                			return "  [ERROR]    ";
                	}
                	return "UNKNOWN";
                }
            public:
                OutStream()
                    :stream(m_buff, 1024)
                {
                    stream << path << "LOG " << log::getDate() << " " << log::getTime() << ".txt";

                    memcpy(LogFileName, stream.c_str(), stream.size() );
                }
                ~OutStream()
                {}
                
            	OutStream& operator()(const char* file, int line)
            	{
                    #ifndef NOTRACE
            		stream << file << ":" << line << "  ";
                    #endif
            		return *this;
            	}

            	void EnableFileLogging();

                // here you can add parameters to the object, every line log
                OutStream& operator()(DebugLevel l) {
                    level = l;
                    return *this;
                }

                // this overload receive the single values to append via <<
                template<typename T>
                OutStream& operator<<(T&& value) {
                	if(LOG_LEVEL <= level)
                    	stream << value;
                    return *this;
                }
                OutStream& operator<<(const char* value) {
                    if(LOG_LEVEL <= level)
                        stream << value;
                    return *this;
                }

                OutStream& operator<<(const size_t& value) {
                    if(LOG_LEVEL <= level)
                        stream.sprintf("%16x", value );
                    return *this;
                }
                OutStream& operator<<(size_t value) {
                    if(LOG_LEVEL <= level)
                        stream.sprintf("%16x", value );
                    return *this;
                }


                // this overload intercept std::endl, to flush the stream and send all to std::cout
                OutStream& operator<<(std::ostream& (*os)(std::ostream&)) {

                	if(LOG_LEVEL > level)
                		return *this;

                	if(loggingToFile)
                    {
						outfile.open(LogFileName, std::ios_base::app); // append instead of overwrite
						if(outfile.fail())
						{
							DebugLevel tmp = level;
							log::warning << "\nFailed to open log file in location: " << LogFileName << " traying to log into executable folder";
							outfile.open(LogFileName, std::ios_base::app);
							if(outfile.fail())
							{
								log::error << "\nFailed to log into executable folder, disabling file logging";
								loggingToFile = false;
							}
							level = tmp;
						}
						outfile << log::getTime() << LogLvl(level) << stream << os;
						outfile.close();
                    }


					switch(level)
					{
						case DebugLevel::ERROR:
							printf("\033[1;31m");
							break;
						case DebugLevel::WARNING:
							printf("\033[1;33m");
							break;
						case DebugLevel::ALL:
							printf("\033[1;35m");
							break;

					}
                    // here you can build the real console log line, add colors and infos, or even write out to a log file
                    std::cout << log::getTime() << LogLvl(level) << stream << os;
					printf("\033[0m");



                    stream.clear(); // reset the string stream
                    level = DebugLevel::ALL; // reset the level to info
                    return *this;
                }

        } Log;

        static void file()
        {
            Log.EnableFileLogging();
        }


};

#endif