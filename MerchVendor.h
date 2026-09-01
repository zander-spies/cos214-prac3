/**
 * @file MerchVendor.h
 * @brief Concrete Leaf/Observer: a merchandise vendor stall.
 */
#ifndef MERCHVENDOR_H
#define MERCHVENDOR_H

#include "EventUnit.h"

/**
 * @class MerchVendor
 * @brief Merch stall (Concrete Leaf + Concrete Observer).
 *
 * An outdoor stall covers its stock and suspends service on a
 * WEATHER_ALERT; an indoor stall keeps selling. On the custom
 * TOURNAMENT_UPSET notice the vendor rushes featured-team merch to the
 * front of the stall.
 */
class MerchVendor : public EventUnit {
public:
    /**
     * @param name     Stall name.
     * @param capacity Queue capacity.
     * @param outdoor  true when the stall stands in the open air.
     */
    MerchVendor(const std::string& name, int capacity, bool outdoor);

    virtual bool isOutdoor() const;
    virtual void update(const Notice& notice);

private:
    bool outdoor_;   /**< Weather sensitivity flag.       */
    bool suspended_; /**< Service suspended flag.         */
};

#endif
