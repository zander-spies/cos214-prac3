#include "ShuttleStop.h"
#include <iostream>

ShuttleStop::ShuttleStop(const std::string& name, int capacity)
    : EventUnit(name, capacity), route_("standard loop"), shuttles_(2) {}

bool ShuttleStop::isOutdoor() const { return true; }

void ShuttleStop::update(const Notice& notice) {
    switch (notice.type) {
        case WEATHER_ALERT:
            route_ = "covered route";
            std::cout << "[" << name_ << "] rerouting shuttles to the "
                      << route_ << "." << std::endl;
            break;
        case CAPACITY_ALERT:
            ++shuttles_;
            std::cout << "[" << name_ << "] adding a shuttle ("
                      << shuttles_ << " now serving this stop)."
                      << std::endl;
            break;
        case EVACUATE:
            shuttles_ += 3;
            std::cout << "[" << name_ << "] EVACUATION SERVICE: "
                      << shuttles_ << " shuttles at maximum frequency."
                      << std::endl;
            break;
        case RESUME_NOTICE:
            route_ = "standard loop";
            shuttles_ = 2;
            std::cout << "[" << name_ << "] back to the " << route_
                      << " with " << shuttles_ << " shuttles." << std::endl;
            break;
        case CLOSE_NOTICE: close(); break;
        case OPEN_NOTICE:  open();  break;
        default:
            std::cout << "[" << name_ << "] " << notice.typeName()
                      << " noted; timetable unchanged." << std::endl;
    }
}
