/**
 * @file Observer.h
 * @brief GoF Observer participant: the abstract Observer.
 */
#ifndef OBSERVER_H
#define OBSERVER_H

#include "Notice.h"

/**
 * @class Observer
 * @brief Abstract receiver of event notifications (GoF Observer role).
 *
 * The design uses a PUSH model: the Subject passes the full Notice to
 * update(), so observers never need a back-pointer to the subject just to
 * fetch state. Observers are NOT owned by the Subjects they register with;
 * ownership of every observing object lies in the Composite tree (or with
 * the client for EventControl-level helpers).
 */
class Observer {
public:
    /** @brief Virtual destructor: Observer is a polymorphic base. */
    virtual ~Observer() {}

    /**
     * @brief Called by a Subject when a change occurs (push model).
     * @param notice The full notice describing the change. The reference is
     *               only valid for the duration of the call; copy if needed.
     */
    virtual void update(const Notice& notice) = 0;
};

#endif
