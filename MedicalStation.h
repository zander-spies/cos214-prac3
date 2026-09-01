/**
 * @file MedicalStation.h
 * @brief Concrete Leaf/Observer: an on-site medical/first-aid team.
 */
#ifndef MEDICALSTATION_H
#define MEDICALSTATION_H

#include "EventUnit.h"

/**
 * @class MedicalStation
 * @brief First-aid unit (Concrete Leaf + Concrete Observer).
 *
 * The safety-critical unit: it stays operational during WEATHER_ALERT,
 * PAUSE and even EVACUATE (it raises readiness instead of closing). This
 * is the required "same alert, unit remains operational" behaviour, and it
 * is the unit that gets transferred between halls at runtime.
 */
class MedicalStation : public EventUnit {
public:
    /**
     * @param name     Team name.
     * @param capacity Number of patients treatable at once.
     */
    MedicalStation(const std::string& name, int capacity);

    virtual void update(const Notice& notice);

private:
    bool elevated_; /**< Elevated readiness flag. */
};

#endif
