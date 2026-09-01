#include "DemoStation.h"
#include <iostream>

DemoStation::DemoStation(const std::string& name, int capacity,
                         const std::string& game)
    : EventUnit(name, capacity), game_(game), overflowQueue_(false) {}

void DemoStation::update(const Notice& notice) {
    switch (notice.type) {
        case WEATHER_ALERT:
            std::cout << "[" << name_ << "] indoor station: demos of "
                      << game_ << " continue despite the weather."
                      << std::endl;
            break;
        case CAPACITY_ALERT:
            overflowQueue_ = true;
            std::cout << "[" << name_ << "] opening virtual overflow queue"
                      << " for " << game_ << "." << std::endl;
            break;
        case TOURNAMENT_UPSET:
            std::cout << "[" << name_ << "] upset hype! Extending "
                      << game_ << " demo sessions by " << notice.value
                      << " minutes." << std::endl;
            break;
        case EVACUATE:
        case CLOSE_NOTICE:
            close();
            break;
        case PAUSE_NOTICE:
            paused_ = true;
            std::cout << "[" << name_ << "] sessions paused." << std::endl;
            break;
        case RESUME_NOTICE:
            paused_ = false;
            overflowQueue_ = false;
            std::cout << "[" << name_ << "] sessions resumed." << std::endl;
            break;
        case OPEN_NOTICE: open(); break;
        default:
            std::cout << "[" << name_ << "] " << notice.typeName()
                      << " noted; demos unaffected." << std::endl;
    }
}

void DemoStation::reportStatus(int indent) const {
    printIndent(indent);
    std::cout << "- " << name_ << " [" << game_ << "] (" << stateWord()
              << ", capacity " << capacity_
              << (overflowQueue_ ? ", overflow queue ON" : "")
              << ")" << std::endl;
}
