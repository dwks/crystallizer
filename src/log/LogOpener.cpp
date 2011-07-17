#include "config.h"

#ifdef USE_WINDOWS_LOG_OPENER
    #include <windows.h>
#elif defined(USE_BOOST_LOG_OPENER)
    #include "boost/filesystem.hpp"
#else  // USE_POSIX_LOG_OPENER
    #include <unistd.h>
    #include <sys/stat.h>
#endif

#include <iostream>  // for std::cout

#include "LogOpener.h"
#include "Logger.h"

#include "FileStream.h"
#include "AliasStream.h"

namespace Crystallizer {
namespace Log {

void LogOpener::openLogs() {
#ifdef USE_WINDOWS_LOG_OPENER
    CreateDirectory((LPCWSTR)LOG_DIRECTORY, NULL);
#elif defined(USE_BOOST_LOG_OPENER)
    boost::filesystem::create_directory(LOG_DIRECTORY);
#else
    mkdir(LOG_DIRECTORY, 0755);
#endif
    
    std::string logfile;
    for(int x = 0; x < 10000; x ++) {
        logfile = Misc::StreamAsString() << LOG_DIRECTORY << x;
    
#ifdef USE_WINDOWS_LOG_OPENER
        if(GetFileAttributes((LPCWSTR)logfile.c_str()) == 0xFFFFFFFF)
#elif defined(USE_BOOST_LOG_OPENER)
        if(!boost::filesystem::exists(logfile))
#else
        if(access(logfile.c_str(), F_OK) != 0)
#endif
        {
            break;
        }
    }
    
    Logger::getInstance().addStream(
        new AliasStream(VerbosityLevel(), std::cout, false));
    Logger::getInstance().addStream(
        new FileStream(VerbosityLevel(), logfile.c_str()));
    
    LOG2(GLOBAL, PROGRESS, "Logging to \"" << logfile << '"');
}

void LogOpener::closeLogs() {
    LOG2(GLOBAL, PROGRESS, "Closing log files");
    
    Logger::getInstance().closeAllStreams();
}

}  // namespace Log
}  // namespace Crystallizer
