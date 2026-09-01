/**
 * @file main.cpp
 * @brief PixelStorm Gaming Convention — EventFlow demonstration client.
 *
 * Demonstrates (Task 8.1): Composite construction (3 nested group levels),
 * observer registration, several different notices, cascading notification
 * through 4 runtime levels, a registration change, Composite traversal and
 * queries, a runtime reorganisation (transfer), and clean shutdown.
 */
#include <iostream>

#include "EventControl.h"
#include "EventGroup.h"
#include "EntryGate.h"
#include "CosplayStage.h"
#include "DemoStation.h"
#include "MerchVendor.h"
#include "MedicalStation.h"
#include "ShuttleStop.h"

int main() {
    std::cout << "======= PixelStorm Gaming Convention : EventFlow ======="
              << std::endl;

    // ---------------------------------------------------------------
    // 1. Build the Composite ownership tree (3 nested group levels).
    //    add(...)  = OWNERSHIP (Composite)
    //    attach()  = OBSERVATION (Observer) — established separately.
    // ---------------------------------------------------------------
    EventControl control;

    EventGroup* convention = new EventGroup("PixelStorm Convention"); // root
    EventGroup* expoHall   = new EventGroup("Main Expo Hall");        // L1
    EventGroup* indieAlley = new EventGroup("Indie Alley");           // L2
    EventGroup* plaza      = new EventGroup("Outdoor Plaza");         // L1
    EventGroup* wing       = new EventGroup("Tournament Wing");       // L1

    EntryGate*      northGate  = new EntryGate("North Gate", 400);
    DemoStation*    aaaWall    = new DemoStation("AAA Demo Wall", 60,
                                                 "Starforge II");
    DemoStation*    indiePod   = new DemoStation("Indie Pod A", 12,
                                                 "Moss & Machine");     // L3
    MerchVendor*    indieCart  = new MerchVendor("Indie Merch Cart", 20,
                                                 false);                // L3
    MedicalStation* medicOne   = new MedicalStation("Medic One", 8);
    CosplayStage*   stage      = new CosplayStage("Grand Cosplay Stage",
                                                  600);
    MerchVendor*    plazaTent  = new MerchVendor("Plaza Merch Tent", 40,
                                                 true);
    ShuttleStop*    shuttle    = new ShuttleStop("Plaza Shuttle Stop", 80);
    EntryGate*      arenaGate  = new EntryGate("Arena Gate", 250);
    DemoStation*    finalsPods = new DemoStation("Finals Practice Pods", 16,
                                                 "Starforge II");

    // Ownership tree
    convention->add(expoHall);
    convention->add(plaza);
    convention->add(wing);
    expoHall->add(northGate);
    expoHall->add(aaaWall);
    expoHall->add(medicOne);
    expoHall->add(indieAlley);
    indieAlley->add(indiePod);
    indieAlley->add(indieCart);
    plaza->add(stage);
    plaza->add(plazaTent);
    plaza->add(shuttle);
    wing->add(arenaGate);
    wing->add(finalsPods);

    // Observer registrations (deliberately separate from ownership)
    control.attach(convention);
    convention->attach(expoHall);
    convention->attach(plaza);
    convention->attach(wing);
    expoHall->attach(northGate);
    expoHall->attach(aaaWall);
    expoHall->attach(medicOne);
    expoHall->attach(indieAlley);
    indieAlley->attach(indiePod);
    indieAlley->attach(indieCart);
    plaza->attach(stage);
    plaza->attach(plazaTent);
    plaza->attach(shuttle);
    wing->attach(arenaGate);
    wing->attach(finalsPods);

    // ---------------------------------------------------------------
    // 2. Open the event and traverse/query through the base interface.
    // ---------------------------------------------------------------
    convention->open();
    std::cout << "\nTotal convention capacity: "
              << convention->getCapacity() << " attendees\n" << std::endl;
    convention->reportStatus();

    // Attendees arrive
    std::cout << std::endl;
    northGate->admit(350);
    arenaGate->admit(120);

    // ---------------------------------------------------------------
    // 3. Notices cascading Control -> root -> zone -> (sub-zone) -> unit
    // ---------------------------------------------------------------
    control.issueNotice(Notice(SCHEDULE_CHANGE,
        "Cosplay finals moved later", 30));

    control.issueNotice(Notice(CAPACITY_ALERT,
        "Crowd threshold reached at gates", 300));

    control.issueNotice(Notice(WEATHER_ALERT,
        "Thunderstorm approaching the venue"));

    control.issueNotice(Notice(TOURNAMENT_UPSET,
        "Team Nova", 45));

    // ---------------------------------------------------------------
    // 4. Registration change at runtime: the Plaza radio link goes down,
    //    so it is detached and misses the next notice, then reattached.
    // ---------------------------------------------------------------
    std::cout << "\n--- Plaza radio link down: detaching Outdoor Plaza ---"
              << std::endl;
    convention->detach(plaza);
    control.issueNotice(Notice(PAUSE_NOTICE,
        "Brief pause for a sponsor broadcast"));
    std::cout << "--- Radio restored: reattaching Outdoor Plaza ---"
              << std::endl;
    convention->attach(plaza);

    // ---------------------------------------------------------------
    // 5. Runtime reorganisation: Medic One is transferred from the Expo
    //    Hall to the Outdoor Plaza (ownership AND registration move).
    // ---------------------------------------------------------------
    std::cout << std::endl;
    expoHall->transferChild(medicOne, *plaza);

    // ---------------------------------------------------------------
    // 6. Safety response followed by recovery.
    // ---------------------------------------------------------------
    control.issueNotice(Notice(EVACUATE,
        "Lightning within 5 km: clear outdoor areas"));
    control.issueNotice(Notice(RESUME_NOTICE,
        "Storm passed: all areas may resume"));

    std::cout << std::endl;
    convention->reportStatus();

    // ---------------------------------------------------------------
    // 7. Clean shutdown: close, then destroy the root exactly once.
    //    Deleting `convention` recursively deletes the whole owned tree.
    // ---------------------------------------------------------------
    std::cout << std::endl;
    convention->close();
    delete convention;

    std::cout << "\nNotices issued this event: " << control.log().size()
              << ". Goodbye from PixelStorm!" << std::endl;
    return 0;
}
