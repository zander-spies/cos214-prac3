/**
 * @file EventControl.h
 * @brief The event-level coordinator: a Concrete Subject outside the tree.
 */
#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include <vector>
#include "Subject.h"

/**
 * @class EventControl
 * @brief Central control centre for the event (GoF Concrete Subject).
 *
 * EventControl is deliberately NOT part of the Composite: it is not "a part
 * of the venue", it is the coordinator that observes nothing and issues
 * notices to the top-level areas registered with it. It keeps the notice
 * log as its subject state (push model: the whole Notice is sent along).
 * It owns no components and no observers.
 */
class EventControl : public Subject {
public:
    /** @brief Virtual destructor. */
    virtual ~EventControl();

    /**
     * @brief Issues a notice: stores it as current state and notifies all
     *        registered observers (the start of every cascade).
     * @param notice The notice to broadcast.
     */
    void issueNotice(const Notice& notice);

    /** @return Chronological log of every notice issued so far. */
    const std::vector<Notice>& log() const;

private:
    std::vector<Notice> log_; /**< Subject state: notice history. */
};

#endif
