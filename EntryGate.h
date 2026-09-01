/**
 * @file EntryGate.h
 * @brief Concrete Leaf/Observer: an admission gate with occupancy tracking.
 */
#ifndef ENTRYGATE_H
#define ENTRYGATE_H

#include "EventUnit.h"

/**
 * @class EntryGate
 * @brief Admission gate (Concrete Leaf + Concrete Observer).
 *
 * Original feature: the gate tracks live occupancy. On a CAPACITY_ALERT it
 * throttles admissions only when occupancy has actually reached the alert
 * threshold (the condition modelled by the alt fragment in SD3). During an
 * EVACUATE it flips to exit-only mode instead of closing outright.
 */
class EntryGate : public EventUnit {
public:
    /**
     * @param name     Gate name.
     * @param capacity Maximum occupancy this gate is responsible for.
     */
    EntryGate(const std::string& name, int capacity);

    /**
     * @brief Admits attendees through the gate (when not throttled).
     * @param count Number of attendees trying to enter.
     * @return Number actually admitted.
     */
    int admit(int count);

    /** @return Current occupancy counted at this gate. */
    int getOccupancy() const;

    virtual void update(const Notice& notice);

private:
    int  occupancy_; /**< Attendees currently inside via this gate. */
    bool throttled_; /**< true while admissions are slowed.         */
    bool exitOnly_;  /**< true during an evacuation.                */
};

#endif
