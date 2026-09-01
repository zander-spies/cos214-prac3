#include "EventControl.h"
#include <iostream>

EventControl::~EventControl() {}

void EventControl::issueNotice(const Notice& notice) {
    log_.push_back(notice);
    std::cout << std::endl << "=== EventControl issues " << notice.typeName()
              << ": " << notice.message << " ===" << std::endl;
    notify(notice);
}

const std::vector<Notice>& EventControl::log() const { return log_; }
