#include "Subject.h"
#include <algorithm>

void Subject::attach(Observer* observer) {
    if (observer == 0) return;
    if (std::find(observers_.begin(), observers_.end(), observer)
            != observers_.end()) {
        return; // duplicate registration ignored
    }
    observers_.push_back(observer);
}

void Subject::detach(Observer* observer) {
    std::vector<Observer*>::iterator it =
        std::find(observers_.begin(), observers_.end(), observer);
    if (it != observers_.end()) {
        observers_.erase(it); // not found -> harmless no-op
    }
}

void Subject::notify(const Notice& notice) {
    // Snapshot copy: registration changes during notification are legal
    // and take effect from the next notify() onwards.
    std::vector<Observer*> snapshot(observers_);
    for (std::size_t i = 0; i < snapshot.size(); ++i) {
        snapshot[i]->update(notice);
    }
}

std::size_t Subject::observerCount() const {
    return observers_.size();
}
