#include "MedicalStation.h"
#include <iostream>

MedicalStation::MedicalStation(const std::string& name, int capacity)
    : EventUnit(name, capacity), elevated_(false) {}

void MedicalStation::update(const Notice& notice) {
    switch (notice.type) {
        case WEATHER_ALERT:
        case CAPACITY_ALERT:
        case EVACUATE:
        case PAUSE_NOTICE:
            elevated_ = true;
            std::cout << "[" << name_ << "] REMAINS OPERATIONAL at elevated"
                      << " readiness (" << notice.typeName() << ")."
                      << std::endl;
            break;
        case RESUME_NOTICE:
            elevated_ = false;
            std::cout << "[" << name_ << "] readiness back to normal."
                      << std::endl;
            break;
        case CLOSE_NOTICE:
            // Medical only stands down on an explicit close of its area.
            close();
            break;
        case OPEN_NOTICE: open(); break;
        default:
            std::cout << "[" << name_ << "] monitoring ("
                      << notice.typeName() << ")." << std::endl;
    }
}
