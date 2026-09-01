# EventFlow — PixelStorm Gaming Convention
**COS 214 Practical 3**

## Event concept
PixelStorm is a two-day gaming convention. A central **EventControl** desk
issues notices (schedule changes, capacity alerts, weather alerts, pauses,
evacuations, resumptions and the custom **TOURNAMENT_UPSET** notice) that
cascade down a nested venue: the Convention contains the Main Expo Hall,
the Outdoor Plaza and the Tournament Wing; the Expo Hall contains Indie
Alley; and every area contains operational units (gates, demo stations,
merch vendors, a medical team, a cosplay stage and a shuttle stop) that
react to the same notice in genuinely different ways.

## Team
- Emmanuel - u23586975
- Zander - u25033931
- Tshego - u23605032

## Build & run
```
make          # builds the executable `eventflow` (g++ -std=c++11)
./eventflow   # runs the full event simulation
make clean    # removes objects and the executable
```

## Doxygen
```
doxygen Doxyfile     # or: make docs
# open docs/doxygen/html/index.html
```
Generation produces **zero warnings**: every class and public operation is
documented, including ownership/lifetime expectations for raw pointers.

## Architecture overview
- **Composite** (`EventComponent` / `EventUnit` / `EventGroup`): the venue
  is a part-whole tree. `EventGroup` **owns** its children and deletes the
  whole subtree exactly once; `release()`/`transferChild()` move ownership
  safely at runtime.
- **Observer** (`Subject` / `Observer` / `EventControl`): **push** model —
  the full `Notice` value object is passed to `update(const Notice&)`.
  Subjects hold **non-owning** observer pointers; `attach` ignores
  duplicates/nullptr, `detach` is a no-op when absent, and `notify`
  iterates a snapshot so registrations may change mid-notification.
- `EventGroup` is deliberately **both Observer and Subject**: it receives a
  notice from above (Observer collaboration with its parent) and cascades
  it to the observers registered below (Subject collaboration with its
  children) — two different collaborations, not a pattern misuse.

## Repository layout
One `.h`/`.cpp` pair per class; `main.cpp` drives the demonstration;
`docs/` holds the UML diagrams (PlantUML sources + PNG) and the submitted
design PDF; `Doxyfile` configures documentation.
