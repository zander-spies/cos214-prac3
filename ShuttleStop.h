/**
 * @file ShuttleStop.h
 * @brief Concrete Leaf/Observer: an attendee shuttle stop.
 */
#ifndef SHUTTLESTOP_H
#define SHUTTLESTOP_H

#include "EventUnit.h"

/**
 * @class ShuttleStop
 * @brief Shuttle stop (Concrete Leaf + Concrete Observer).
 *
 * Reacts to the same notices differently again: WEATHER_ALERT switches to
 * the covered route, CAPACITY_ALERT adds extra shuttles, EVACUATE boosts
 * departure frequency to move people out instead of closing.
 */
class ShuttleStop : public EventUnit {
public:
    /**
     * @param name     Stop name.
     * @param capacity Queue capacity at the stop.
     */
    ShuttleStop(const std::string& name, int capacity);

    virtual bool isOutdoor() const;
    virtual void update(const Notice& notice);

private:
    std::string route_;    /**< Current route name.            */
    int         shuttles_; /**< Shuttles serving this stop.    */
};

#endif
