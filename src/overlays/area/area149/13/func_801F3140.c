#include "area149_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3140(s8 span) {
    s32 slot;
    s32 y;
    u8  i;

    if ((g_FrameCount & 3) != 0) {
        return;
    }

    /* Two trail actors straddle the scroll target this run. */
    for (i = 0; i < 2; i++) {
        slot = Actor_FindFreeSpawned();
        if ((u8)slot != 0xFF) {
            g_SpawnedActors[(u8)slot].header.flags     = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[(u8)slot].type             = 0x37;
            g_SpawnedActors[(u8)slot].unk_2C           = 0x2C0;
            g_SpawnedActors[(u8)slot].pos.x.fixed      = g_AreaScrollTargetX + TO_COORD(span);
            y                                          = g_AreaScrollTargetY;
            g_SpawnedActors[(u8)slot].pos.y.fixed      = y + (i == 0 ? TO_COORD(1) : -TO_COORD(1));
            COORD_INT(g_SpawnedActors[(u8)slot].pos.z) = Area_HeightSample(g_SpawnedActors[(u8)slot].pos.x.fixed, g_SpawnedActors[(u8)slot].pos.y.fixed);
            g_SpawnedActors[(u8)slot].unk_2C           = 0x2C0;
            g_SpawnedActors[(u8)slot].layer            = 1;
            g_SpawnedActors[(u8)slot].unk_06           = 0;
            g_SpawnedActors[(u8)slot].unk_07           = 0;
            g_SpawnedActors[(u8)slot].unk_29           = 6;
        }
    }
}
#else
INCLUDE_ASM(func_801F3140);
#endif
