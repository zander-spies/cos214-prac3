/**
 * @file Notice.h
 * @brief Defines the notice/order representation pushed from Subjects to Observers.
 */
#ifndef NOTICE_H
#define NOTICE_H

#include <string>

/**
 * @brief The kinds of operational notices EventControl (or a cascading
 *        EventGroup) can issue to registered observers.
 *
 * TOURNAMENT_UPSET is the custom, event-specific notice invented for the
 * PixelStorm Gaming Convention scenario.
 */
enum NoticeType {
    OPEN_NOTICE,      /**< Ordinary operational change: area opens.           */
    CLOSE_NOTICE,     /**< Ordinary operational change: area closes.          */
    SCHEDULE_CHANGE,  /**< A programme item moved or was cancelled.           */
    CAPACITY_ALERT,   /**< Capacity-related change: crowd threshold reached.  */
    WEATHER_ALERT,    /**< Safety-related change: storm/rain warning.         */
    PAUSE_NOTICE,     /**< Temporary pause instruction.                       */
    RESUME_NOTICE,    /**< Resumption notice after a pause.                   */
    EVACUATE,         /**< Safety-related change: clear the area.             */
    TOURNAMENT_UPSET  /**< Custom notice: a headline tournament upset.        */
};

/**
 * @brief Value object carried by every notification (push-model Observer).
 *
 * The Notice is copied by value along the notification cascade, so no
 * ownership questions arise: every Observer receives a const reference to
 * the Subject's current Notice and may copy what it needs.
 */
struct Notice {
    NoticeType  type;     /**< What kind of change occurred.                  */
    std::string message;  /**< Human-readable description of the change.      */
    int         value;    /**< Numeric payload (e.g. capacity %, minutes).    */
    std::string origin;   /**< Name of the Subject that first issued it.      */

    /**
     * @brief Constructs a notice.
     * @param t   Kind of notice.
     * @param msg Human-readable description.
     * @param v   Numeric payload; defaults to 0 when not meaningful.
     * @param o   Name of the issuing subject; defaults to "EventControl".
     */
    Notice(NoticeType t, const std::string& msg, int v = 0,
           const std::string& o = "EventControl")
        : type(t), message(msg), value(v), origin(o) {}

    /** @return A short human-readable label for this notice's type. */
    std::string typeName() const;
};

#endif
