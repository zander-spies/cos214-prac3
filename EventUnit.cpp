#include "EventUnit.h"
#include <iostream>

EventUnit::EventUnit(const std::string& name, int capacity)
    : EventComponent(name, capacity), paused_(false) {}

EventUnit::~EventUnit() {}

void EventUnit::open() {
    open_ = true;
    paused_ = false;
    std::cout << "[" << name_ << "] is now open." << std::endl;
}

void EventUnit::close() {
    open_ = false;
    std::cout << "[" << name_ << "] is now closed." << std::endl;
}

void EventUnit::reportStatus(int indent) const {
    printIndent(indent);
    std::cout << "- " << name_ << " (" << stateWord()
              << ", capacity " << capacity_ << ")" << std::endl;
}

int EventUnit::getCapacity() const { return capacity_; }

bool EventUnit::isOutdoor() const { return false; }

std::string EventUnit::stateWord() const {
    if (!open_)  return "closed";
    if (paused_) return "paused";
    return "open";
}
