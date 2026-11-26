#include "area030_04.h"

/* Selects the load mode from the scheduled-area flag, then copies the
 * selected AREA030 table row into the scratch record's probe fields and runs
 * the per-frame tail. */
/* func_801D28DC */
MATCH void Fishing_LureHooked(void) {
    FishingState* work;

    if (g_SpawnedActors[5].selection < 0) {
        Script_Request(2);
    } else {
        Script_Request(3);
    }

    work                  = SELF(FishingState);
    work->motion.unk_34   = g_Actors[g_FishingHookedFish].pos.x.fixed;
    work->y_38.pos_y      = g_Actors[g_FishingHookedFish].pos.y.fixed;
    work->bounce.half.key = COORD_INT(g_Actors[g_FishingHookedFish].pos.z);

    Script_AnimStepLoop();
    func_801E084C();
}
