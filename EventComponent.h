/**
 * @file EventComponent.h
 * @brief GoF Composite participant: the abstract Component.
 */
#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include <string>

/**
 * @class EventComponent
 * @brief Common abstraction for every part of the event (GoF Component).
 *
 * The client can open, close, query capacity and request a status report
 * without knowing whether it holds a single unit (Leaf) or an entire
 * zone (Composite). Child management lives in EventGroup only (the "safe"
 * Composite variant), so a Leaf can never be handed children by mistake.
 *
 * Ownership: every EventComponent is owned by exactly one parent
 * EventGroup, except the root, which is owned by the client (main).
 */
class EventComponent {
public:
    /**
     * @brief Constructs a component.
     * @param name     Display name of this part of the event.
     * @param capacity Maximum number of attendees this part can hold.
     */
    EventComponent(const std::string& name, int capacity);

    /** @brief Virtual destructor: polymorphic base of the whole tree. */
    virtual ~EventComponent();

    /** @brief Opens this part of the event (recursively for groups). */
    virtual void open() = 0;

    /** @brief Closes this part of the event (recursively for groups). */
    virtual void close() = 0;

    /**
     * @brief Prints a human-readable status line (recursively for groups).
     * @param indent Indentation depth used for tree-shaped reports.
     */
    virtual void reportStatus(int indent = 0) const = 0;

    /** @return Total attendee capacity of this part (sum for groups). */
    virtual int getCapacity() const = 0;

    /** @return The display name of this part of the event. */
    const std::string& getName() const;

    /** @return true when this part is currently open. */
    bool isOpen() const;

protected:
    /** @brief Prints @p indent levels of indentation. */
    void printIndent(int indent) const;

    std::string name_;     /**< Display name.                        */
    int         capacity_; /**< Own (leaf) or nominal capacity.      */
    bool        open_;     /**< Current open/closed state.           */
};

#endif
