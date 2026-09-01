#include "CosplayStage.h"
#include <iostream>

CosplayStage::CosplayStage(const std::string& name, int capacity)
    : EventUnit(name, capacity), showtimeOffsetMin_(0) {}

bool CosplayStage::isOutdoor() const { return true; }

void CosplayStage::update(const Notice& notice) {
    switch (notice.type) {
        case WEATHER_ALERT:
        case PAUSE_NOTICE:
        case EVACUATE:
            paused_ = true;
            std::cout << "[" << name_ << "] outdoor stage: PAUSING the show"
                      << " and clearing performers." << std::endl;
            break;
        case RESUME_NOTICE:
            if (open_) {
                paused_ = false;
                std::cout << "[" << name_ << "] show resumes!" << std::endl;
            }
            break;
        case SCHEDULE_CHANGE:
            showtimeOffsetMin_ += notice.value;
            std::cout << "[" << name_ << "] next show shifted by "
                      << notice.value << " min (total offset "
                      << showtimeOffsetMin_ << " min)." << std::endl;
            break;
        case CLOSE_NOTICE: close(); break;
        case OPEN_NOTICE:  open();  break;
        default:
            std::cout << "[" << name_ << "] show continues unaffected by "
                      << notice.typeName() << "." << std::endl;
    }
}
