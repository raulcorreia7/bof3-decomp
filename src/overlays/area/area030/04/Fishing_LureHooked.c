#include "area030_04.h"

/* Selects the load mode from the scheduled-area flag, then copies the
 * selected AREA030 table row into the scratch record's probe fields and runs
 * the per-frame tail. */
/* func_801D28DC */
MATCH void Fishing_LureHooked(void) {
    FishingState* work;

    if (D_8014421C < 0) {
        Actor_RequestScript(2);
    } else {
        Actor_RequestScript(3);
    }

    work                        = FISHING_STATE;
    work->motion_34.unk_34      = g_Actors[g_FishingHookedFish].pos.x.fixed;
    work->y_38.pos_y            = g_Actors[g_FishingHookedFish].pos.y.fixed;
    work->bounce_3C.half.key_3E = COORD_INT(g_Actors[g_FishingHookedFish].pos.z);

    func_8014D978();
    func_801E084C();
}
