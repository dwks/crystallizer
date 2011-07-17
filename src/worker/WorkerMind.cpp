#include <sstream>
#include <cstdlib>  // for std::exit
#include <unistd.h>  // sorry

#include "boost/bind.hpp"

#include "WorkerMind.h"

#include "fractal/Computable.h"
#include "fractal/ComputableRange.h"
#include "fractal/MandlebrotComputable.h"

#include "config.h"
#include "log/Logger.h"

namespace Crystallizer {
namespace Worker {

void WorkerMind::run(const std::string &host, unsigned short port) {
    boost::asio::io_service io_service;
    
    LOG2(GLOBAL, PROGRESS, "Worker trying hive " << host << ":" << port);
    
    try {
        hive = boost::shared_ptr<Network::ClientSocket>(
            new Network::ClientSocket(io_service, host.c_str(), port));
    }
    catch(std::exception &e) {
        LOG2(NETWORK, ERROR, "Exception: " << e.what());
        std::exit(1);
    }
    
    hive->addReceiver(
        boost::shared_ptr<Network::DataReceiver>(new Receiver(hive)));
    
    LOG2(GLOBAL, PROGRESS, "Entering tiny little worker mind");
    
    for(;;) {
        LOG(NETWORK, "Worker loop...");
        
        try {
            io_service.run();
            io_service.reset();
        }
        catch(std::exception &e) {
            LOG2(NETWORK, ERROR, "Exception: " << e.what());
        }
        
        sleep(1);
    }
}

bool WorkerMind::Receiver::receive(const std::string &data) {
    if(data == "Mandelbrot") {
        LOG(NETWORK, "Worker is beginning a " << data);
        hive->addReceiverFront(boost::shared_ptr<DataReceiver>(
            new MandelbrotReceiver(hive)));
    }
    else {
        LOG2(NETWORK, ERROR, "Unexpected packet received!");
    }
    
    return true;
}

bool WorkerMind::MandelbrotReceiver::receive(const std::string &data) {
    std::istringstream stream(data);
    
    LOG(FRACTAL, "Mandelbrot on " << data);
    
    real bailoutDistance;
    int bailoutIterations;
    if(!(stream >> bailoutDistance >> bailoutIterations)) {
        LOG2(NETWORK, ERROR, "Expecting bailouts");
        return false;
    }
    
    double startr, starti, endr, endi, granr, grani;
    if(!(stream >> startr >> starti >> endr >> endi >> granr >> grani)) {
        LOG2(NETWORK, ERROR, "Expecting ComputableRange");
    }
    
    Fractal::ComputableRange range(
        Fractal::DataPoint(startr, starti),
        Fractal::DataPoint(endr, endi),
        Fractal::DataPoint(granr, grani));
    
    Fractal::MandlebrotComputable mandelbrot;
    Fractal::ComputableRange::Iterator it = range.getIterator();
    while(it.hasNext()) {
        Fractal::DataPoint data = it.next();
        Fractal::DataPoint result
            = mandelbrot.calculate(data, bailoutDistance, bailoutIterations);
        
        LOG(FRACTAL, result.real() << "+" << result.imag() << "i");
    }
    
    return false;
}

}  // namespace Worker
}  // namespace Crystallizer
