/**
 * @file DemoStation.h
 * @brief Concrete Leaf/Observer: an indoor playable game demo station.
 */
#ifndef DEMOSTATION_H
#define DEMOSTATION_H

#include "EventUnit.h"

/**
 * @class DemoStation
 * @brief Indoor playable demo pod (Concrete Leaf + Concrete Observer).
 *
 * Indoor, so weather alerts leave it running. On a CAPACITY_ALERT it opens
 * a virtual overflow queue; on the custom TOURNAMENT_UPSET notice it
 * extends demo sessions for the featured game.
 */
class DemoStation : public EventUnit {
public:
    /**
     * @param name     Station name.
     * @param capacity Number of simultaneous players.
     * @param game     Title currently playable at the station.
     */
    DemoStation(const std::string& name, int capacity,
                const std::string& game);

    virtual void update(const Notice& notice);
    virtual void reportStatus(int indent = 0) const;

private:
    std::string game_;          /**< Featured game title.        */
    bool        overflowQueue_; /**< Virtual queue active flag.  */
};

#endif
