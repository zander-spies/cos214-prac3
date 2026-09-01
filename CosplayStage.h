/**
 * @file CosplayStage.h
 * @brief Concrete Leaf/Observer: the outdoor cosplay stage.
 */
#ifndef COSPLAYSTAGE_H
#define COSPLAYSTAGE_H

#include "EventUnit.h"

/**
 * @class CosplayStage
 * @brief Outdoor performance stage (Concrete Leaf + Concrete Observer).
 *
 * Being OUTDOOR, it pauses its show on a WEATHER_ALERT while indoor units
 * carry on — the clearest example of "same notice, different reaction
 * through polymorphism". SCHEDULE_CHANGE shifts the next showtime by the
 * notice's numeric payload (minutes).
 */
class CosplayStage : public EventUnit {
public:
    /**
     * @param name     Stage name.
     * @param capacity Audience capacity.
     */
    CosplayStage(const std::string& name, int capacity);

    virtual bool isOutdoor() const;
    virtual void update(const Notice& notice);

private:
    int showtimeOffsetMin_; /**< Accumulated schedule shift in minutes. */
};

#endif
