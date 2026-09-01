#include "Notice.h"

std::string Notice::typeName() const {
    switch (type) {
        case OPEN_NOTICE:      return "OPEN";
        case CLOSE_NOTICE:     return "CLOSE";
        case SCHEDULE_CHANGE:  return "SCHEDULE_CHANGE";
        case CAPACITY_ALERT:   return "CAPACITY_ALERT";
        case WEATHER_ALERT:    return "WEATHER_ALERT";
        case PAUSE_NOTICE:     return "PAUSE";
        case RESUME_NOTICE:    return "RESUME";
        case EVACUATE:         return "EVACUATE";
        case TOURNAMENT_UPSET: return "TOURNAMENT_UPSET";
    }
    return "UNKNOWN";
}
