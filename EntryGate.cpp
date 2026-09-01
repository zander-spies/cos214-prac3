#include "EntryGate.h"
#include <iostream>

EntryGate::EntryGate(const std::string& name, int capacity)
    : EventUnit(name, capacity), occupancy_(0),
      throttled_(false), exitOnly_(false) {}

int EntryGate::admit(int count) {
    if (!open_ || exitOnly_) {
        std::cout << "[" << name_ << "] not admitting (closed/exit-only)."
                  << std::endl;
        return 0;
    }
    int admitted = throttled_ ? count / 2 : count;
    if (occupancy_ + admitted > capacity_) admitted = capacity_ - occupancy_;
    if (admitted < 0) admitted = 0;
    occupancy_ += admitted;
    std::cout << "[" << name_ << "] admitted " << admitted << "/" << count
              << " (occupancy " << occupancy_ << "/" << capacity_ << ")."
              << std::endl;
    return admitted;
}

int EntryGate::getOccupancy() const { return occupancy_; }

void EntryGate::update(const Notice& notice) {
    switch (notice.type) {
        case CAPACITY_ALERT:
            if (occupancy_ >= notice.value) {          // alt guard in SD3
                throttled_ = true;
                std::cout << "[" << name_ << "] occupancy " << occupancy_
                          << " >= threshold " << notice.value
                          << ": throttling admissions." << std::endl;
            } else {
                std::cout << "[" << name_ << "] occupancy " << occupancy_
                          << " below threshold: admitting normally."
                          << std::endl;
            }
            break;
        case EVACUATE:
            exitOnly_ = true;
            std::cout << "[" << name_ << "] switching to EXIT-ONLY mode."
                      << std::endl;
            break;
        case RESUME_NOTICE:
            throttled_ = false;
            exitOnly_ = false;
            paused_ = false;
            std::cout << "[" << name_ << "] normal admissions resumed."
                      << std::endl;
            break;
        case CLOSE_NOTICE:
            close();
            break;
        case OPEN_NOTICE:
            open();
            break;
        default:
            std::cout << "[" << name_ << "] notes " << notice.typeName()
                      << ", gate operation unchanged." << std::endl;
    }
}
