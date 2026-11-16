#include "area149_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3140(s8 span) {
    s32 offset;
    s32 y;
    u8  i;
    u8  slot;

    if ((g_FrameCount & 3) != 0) {
        return;
    }

    /* Two trail actors straddle the scroll target this run. */
    for (i = 0; i < 2; i++) {
        slot = Actor_FindFreeSpawned();
        if (slot != 0xFF) {
            g_SpawnedActors[slot].header.flags     = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[slot].type             = 0x37;
            g_SpawnedActors[slot].unk_2C           = 0x2C0;
            g_SpawnedActors[slot].pos.x.fixed      = g_AreaScrollTargetX + TO_COORD(span);
            y                                      = g_AreaScrollTargetY;
            offset                                 = (i != 0) ? -TO_COORD(1) : TO_COORD(1);
            g_SpawnedActors[slot].pos.y.fixed      = y + offset;
            COORD_INT(g_SpawnedActors[slot].pos.z) = Area_SampleHeight(g_SpawnedActors[slot].pos.x.fixed, g_SpawnedActors[slot].pos.y.fixed);
            g_SpawnedActors[slot].unk_2C           = 0x2C0;
            g_SpawnedActors[slot].layer            = 1;
            g_SpawnedActors[slot].unk_06           = 0;
            g_SpawnedActors[slot].unk_07           = 0;
            g_SpawnedActors[slot].unk_29           = 6;
        }
    }
}
#else
INCLUDE_ASM(func_801F3140);
#endif
