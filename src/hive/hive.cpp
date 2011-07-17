#include <iostream>

#include "log/LogOpener.h"
#include "log/Logger.h"

int main() {
    Crystallizer::Log::LogOpener::openLogs();
    
    LOG2(GLOBAL, PROGRESS, "Launching hive");
    
    Crystallizer::Log::LogOpener::closeLogs();
    return 0;
}
