/**
 * @file EventGroup.h
 * @brief GoF Composite participant that is also both Observer and Subject.
 */
#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include <vector>
#include "EventComponent.h"
#include "Subject.h"
#include "Observer.h"

/**
 * @class EventGroup
 * @brief A zone/hall/wing of the event (GoF Composite role).
 *
 * Participates in THREE collaborations, for three different reasons:
 *  - Composite: owns child EventComponents (leaves and sub-groups) and
 *    implements the common operations recursively.
 *  - Observer:  receives notices from the Subject above it (EventControl
 *    or a parent EventGroup).
 *  - Subject:   after reacting, cascades the notice to the observers
 *    registered below it.
 *
 * Ownership policy: children added with add() are OWNED and deleted in the
 * destructor. release() gives ownership back to the caller WITHOUT deleting
 * and also detaches the child from this group's observer list, which is
 * what makes double deletion during a transfer impossible.
 */
class EventGroup : public EventComponent, public Subject, public Observer {
public:
    /**
     * @brief Constructs a group; capacity is derived from the children.
     * @param name Display name of the zone/hall/wing.
     */
    explicit EventGroup(const std::string& name);

    /** @brief Deletes every owned child exactly once (recursively). */
    virtual ~EventGroup();

    /**
     * @brief Takes ownership of @p child and appends it to this group.
     * @param child Component to adopt; nullptr is ignored. Must not already
     *              be owned by another group (transfer via release() first).
     */
    void add(EventComponent* child);

    /**
     * @brief Removes and DESTROYS the given child (and its subtree).
     * @param child Child to remove; no-op when not a child of this group.
     */
    void remove(EventComponent* child);

    /**
     * @brief Removes @p child from this group WITHOUT deleting it and
     *        detaches it from this group's observer list.
     *
     * Ownership passes to the caller, who must either add() the component
     * to another group or delete it. This is the transfer mechanism used
     * for runtime reorganisation.
     *
     * @param child Child to release.
     * @return The released component, or nullptr when it was not a child.
     */
    EventComponent* release(EventComponent* child);

    /**
     * @brief Transfers @p child from this group into @p destination,
     *        updating BOTH the ownership tree and Observer registrations.
     * @param child       Child currently owned by this group.
     * @param destination Group that will own and notify the child next.
     * @return true when the transfer happened.
     */
    bool transferChild(EventComponent* child, EventGroup& destination);

    virtual void open();
    virtual void close();
    virtual void reportStatus(int indent = 0) const;

    /** @return Sum of the capacities of all children. */
    virtual int getCapacity() const;

    /**
     * @brief Observer role: receive a notice from above, react, cascade.
     *
     * The group reacts (logs / applies group-level rules) and then, as a
     * Subject, calls notify() so the notice cascades to its own observers.
     *
     * @param notice The notice pushed from the parent Subject.
     */
    virtual void update(const Notice& notice);

    /** @return Number of direct children (for tests/demonstration). */
    std::size_t childCount() const;

private:
    std::vector<EventComponent*> children_; /**< OWNED children. */
};

#endif
