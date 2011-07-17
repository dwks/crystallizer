#include <iostream>
#include <string>
#include <cstdlib>  // for std::strtol

#include "config.h"
#include "worker/WorkerMind.h"

#include "log/LogOpener.h"
#include "log/Logger.h"

int main(int argc, char *argv[]) {
    Crystallizer::Log::LogOpener::openLogs();
    LOG2(GLOBAL, PROGRESS, "Launching worker");
    
    std::string host = "localhost";
    unsigned short port = DEFAULT_PORT;
    
    if(argc > 1) host = argv[1];
    if(argc > 2) port = std::strtol(argv[2], NULL, 0);
    
    Crystallizer::Worker::WorkerMind worker;
    worker.run(host, port);
    
    Crystallizer::Log::LogOpener::closeLogs();
    return 0;
}
