#include "EventComponent.h"
#include <iostream>

EventComponent::EventComponent(const std::string& name, int capacity)
    : name_(name), capacity_(capacity), open_(false) {}

EventComponent::~EventComponent() {}

const std::string& EventComponent::getName() const { return name_; }

bool EventComponent::isOpen() const { return open_; }

void EventComponent::printIndent(int indent) const {
    for (int i = 0; i < indent; ++i) std::cout << "  ";
}
