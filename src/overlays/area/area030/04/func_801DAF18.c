#include "area030_04.h"

/* Advances the AREA030 sub-state counter, seeds the battle
 * parameters from the current slot, and enters the next mode. */
MATCH void func_801DAF18(void) {
    u8 counter;

    g_SpawnedActors[4].unk_06      = 2;
    counter                        = g_SpawnedActors[4].header.mode;
    g_SpawnedActors[2].header.mode = 0;
    g_SpawnedActors[4].header.mode = (counter + 1);

    g_AreaScrollTargetCoordY.fixed = *(u32*)(D_801468C0 + g_FishingHookedFish * 152);
    SND_StartDecrescendo(0, 0, 0x64, 8);
    g_SpawnedActors[3].header.mode = 7;
    TASK(FishingState)->sub_index += 1;
}
