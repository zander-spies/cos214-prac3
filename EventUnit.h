/**
 * @file EventUnit.h
 * @brief Abstract Leaf base: an operational unit that also observes.
 */
#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
#include "Observer.h"

/**
 * @class EventUnit
 * @brief Abstract Leaf of the Composite that is also a GoF Observer.
 *
 * Every concrete operational unit at PixelStorm (gates, stages, vendors,
 * medical, shuttles, demo stations) both *is part of* an area (Composite
 * child, owned by its parent EventGroup) and *listens to* that area
 * (Observer registered with the parent-as-Subject). The two relationships
 * are established separately: containment does not automatically imply
 * registration (see design rationale).
 */
class EventUnit : public EventComponent, public Observer {
public:
    /**
     * @brief Constructs a leaf unit.
     * @param name     Display name of the unit.
     * @param capacity Attendee capacity of the unit.
     */
    EventUnit(const std::string& name, int capacity);

    /** @brief Virtual destructor. */
    virtual ~EventUnit();

    virtual void open();
    virtual void close();
    virtual void reportStatus(int indent = 0) const;
    virtual int  getCapacity() const;

    /** @return true when the unit is outdoors (weather-sensitive). */
    virtual bool isOutdoor() const;

protected:
    /** @return A short state word ("open"/"closed"/"paused"). */
    std::string stateWord() const;

    bool paused_; /**< true while temporarily paused. */
};

#endif
