#include "overlays/area/WorldMap_AdvanceWhenPartyNear.h"

/* Advances the actor state when the party stands in the actor's cell, then runs the area update. */
/* func_801F2DB8 (area158), func_801F2DB8 (area160), func_801F2DB8 (area161), func_801F2DB8 (area162), func_801F2DB8
   (area163), func_801F2DB8 (area164), func_801F2DB8 (area165), func_801F2DB8 (area166), func_801F2DCC (area169),
   func_801F2DEC (area157), func_801F2EA0 (area167), func_801F35F8 (area168), func_801F363C (area174), func_801F3C68
   (area139), func_801F3DE8 (area170) */
MATCH void Actor_AdvanceWhenPartyNear(void) {
    WorldMap_AdvanceWhenPartyNear();
    Area_Update();
}
