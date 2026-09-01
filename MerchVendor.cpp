#include "MerchVendor.h"
#include <iostream>

MerchVendor::MerchVendor(const std::string& name, int capacity, bool outdoor)
    : EventUnit(name, capacity), outdoor_(outdoor), suspended_(false) {}

bool MerchVendor::isOutdoor() const { return outdoor_; }

void MerchVendor::update(const Notice& notice) {
    switch (notice.type) {
        case WEATHER_ALERT:
            if (outdoor_) {
                suspended_ = true;
                std::cout << "[" << name_ << "] outdoor stall: covering"
                          << " stock and suspending sales." << std::endl;
            } else {
                std::cout << "[" << name_ << "] indoor stall: sales"
                          << " continue." << std::endl;
            }
            break;
        case TOURNAMENT_UPSET:
            std::cout << "[" << name_ << "] rushing '" << notice.message
                      << "' merch to the front of the stall!" << std::endl;
            break;
        case RESUME_NOTICE:
            suspended_ = false;
            paused_ = false;
            std::cout << "[" << name_ << "] sales resumed." << std::endl;
            break;
        case EVACUATE:
        case CLOSE_NOTICE:
            close();
            break;
        case OPEN_NOTICE: open(); break;
        case PAUSE_NOTICE:
            paused_ = true;
            std::cout << "[" << name_ << "] till paused." << std::endl;
            break;
        default:
            std::cout << "[" << name_ << "] " << notice.typeName()
                      << " noted; stall unaffected." << std::endl;
    }
}
