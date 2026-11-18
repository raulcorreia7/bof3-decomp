#include "area149_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3140(s8 span) {
    s32 offset;
    s32 y;
    u8  i;
    s32 slot;
    u8  slot2;

    if ((g_FrameCount & 3) != 0) {
        return;
    }

    /* Two trail actors straddle the scroll target this run. */
    for (i = 0; i < 2; i++) {
        slot = Actor_FindFreeSpawned();
        if (slot != 0xFF) {
            g_SpawnedActors[(u8)slot].header.flags  = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[(u8)slot].type          = 0x37;
            g_SpawnedActors[(u8)slot].unk_2C        = 0x2C0;
            g_SpawnedActors[(u8)slot].pos.x.fixed   = g_AreaScrollTargetX + TO_COORD(span);
            offset                                  = (i == 0) ? TO_COORD(1) : -TO_COORD(1);
            y                                       = g_AreaScrollTargetY;
            g_SpawnedActors[(u8)slot].pos.y.fixed   = y + offset;
            slot2                                   = (u8)slot;
            COORD_INT(g_SpawnedActors[slot2].pos.z) = Area_SampleHeight(g_SpawnedActors[slot2].pos.x.fixed, g_SpawnedActors[slot2].pos.y.fixed);
            g_SpawnedActors[slot2].unk_2C           = 0x2C0;
            g_SpawnedActors[slot2].layer            = 1;
            g_SpawnedActors[slot2].unk_06           = 0;
            g_SpawnedActors[slot2].unk_07           = 0;
            g_SpawnedActors[slot2].unk_29           = 6;
        }
    }
}
#else
INCLUDE_ASM(func_801F3140);
#endif
