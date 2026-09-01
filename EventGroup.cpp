#include "EventGroup.h"
#include <algorithm>
#include <iostream>

EventGroup::EventGroup(const std::string& name)
    : EventComponent(name, 0) {}

EventGroup::~EventGroup() {
    // The whole owned subtree is released exactly once: each child is
    // owned by exactly one parent, and release()/transferChild() removes
    // a child from children_ before anyone else may own it.
    for (std::size_t i = 0; i < children_.size(); ++i) {
        delete children_[i];
    }
    children_.clear();
}

void EventGroup::add(EventComponent* child) {
    if (child == 0) return;
    children_.push_back(child); // ownership taken
}

void EventGroup::remove(EventComponent* child) {
    EventComponent* released = release(child);
    delete released; // delete nullptr is safe
}

EventComponent* EventGroup::release(EventComponent* child) {
    std::vector<EventComponent*>::iterator it =
        std::find(children_.begin(), children_.end(), child);
    if (it == children_.end()) return 0;
    children_.erase(it);
    // Structural removal also ends the observation relationship with THIS
    // group; the two relationships are managed together here on purpose,
    // so a released unit can never receive a stale notification.
    Observer* obs = dynamic_cast<Observer*>(child);
    if (obs != 0) detach(obs);
    return child;
}

bool EventGroup::transferChild(EventComponent* child, EventGroup& destination) {
    EventComponent* released = release(child);
    if (released == 0) return false;
    destination.add(released);                      // ownership moves
    Observer* obs = dynamic_cast<Observer*>(released);
    if (obs != 0) destination.attach(obs);          // registration moves
    std::cout << "[" << name_ << "] transferred '" << released->getName()
              << "' to [" << destination.getName() << "]." << std::endl;
    return true;
}

void EventGroup::open() {
    open_ = true;
    std::cout << "[" << name_ << "] zone opening..." << std::endl;
    for (std::size_t i = 0; i < children_.size(); ++i) children_[i]->open();
}

void EventGroup::close() {
    std::cout << "[" << name_ << "] zone closing..." << std::endl;
    for (std::size_t i = 0; i < children_.size(); ++i) children_[i]->close();
    open_ = false;
}

void EventGroup::reportStatus(int indent) const {
    printIndent(indent);
    std::cout << "+ " << name_ << " (" << (open_ ? "open" : "closed")
              << ", total capacity " << getCapacity() << ")" << std::endl;
    for (std::size_t i = 0; i < children_.size(); ++i) {
        children_[i]->reportStatus(indent + 1);
    }
}

int EventGroup::getCapacity() const {
    int total = 0;
    for (std::size_t i = 0; i < children_.size(); ++i) {
        total += children_[i]->getCapacity();
    }
    return total;
}

void EventGroup::update(const Notice& notice) {
    std::cout << "[" << name_ << "] received " << notice.typeName()
              << " from " << notice.origin << " -> cascading to "
              << observerCount() << " observer(s)." << std::endl;
    if (notice.type == EVACUATE) open_ = false; // group-level rule
    notify(notice); // Subject role: cascade downwards
}

std::size_t EventGroup::childCount() const { return children_.size(); }
