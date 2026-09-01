/**
 * @file Subject.h
 * @brief GoF Observer participant: the abstract Subject.
 */
#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

/**
 * @class Subject
 * @brief Anything that can be observed (GoF Subject role).
 *
 * Registration policy:
 *  - attach(): nullptr and duplicate registrations are silently ignored,
 *    so an observer is notified at most once per notify().
 *  - detach(): detaching an unregistered observer is a harmless no-op.
 *  - notify(): iterates over a snapshot copy of the registration list, so
 *    an observer may attach/detach (itself or others) while a notification
 *    is in progress without invalidating the iteration. Changes take
 *    effect from the next notification onwards (single-threaded policy).
 *
 * Ownership: the Subject stores NON-OWNING pointers. Observer lifetime is
 * guaranteed by the Composite ownership tree: a group only notifies
 * observers it (transitively) owns or that the client keeps alive, and
 * removal/transfer of a child always detaches it first.
 */
class Subject {
public:
    /** @brief Virtual destructor: Subject is a polymorphic base. */
    virtual ~Subject() {}

    /**
     * @brief Registers an observer for future notifications.
     *
     * Stores a non-owning pointer. The observer must remain alive while
     * registered and must be detached before it is destroyed.
     *
     * @param observer Observer to register; nullptr and duplicates ignored.
     */
    virtual void attach(Observer* observer);

    /**
     * @brief Deregisters an observer.
     * @param observer Observer to remove; no-op when not registered.
     */
    virtual void detach(Observer* observer);

    /**
     * @brief Notifies every currently registered observer (push model).
     * @param notice The notice pushed to each observer's update().
     */
    virtual void notify(const Notice& notice);

    /** @return Number of currently registered observers. */
    std::size_t observerCount() const;

private:
    std::vector<Observer*> observers_; /**< Non-owning registrations. */
};

#endif
