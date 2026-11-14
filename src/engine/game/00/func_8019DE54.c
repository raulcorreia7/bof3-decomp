#include "game_00.h"

/* K&R call keeps a0 undisturbed; the callee ignores its mode argument. */

MATCH void func_8019DE54(void) {
    s32    i;
    u8     index;
    Actor* work;

    for (i = 0; i < 10; i++) {
        index = Actor_FindFreeSlot() & BYTE_MASK;
        if (index != GAME_NONE) {
            g_SpawnedActors[index].header.flags = 1;
            g_SpawnedActors[index].type         = 0x34;
            g_SpawnedActors[index].header.step  = 2;
            g_SpawnedActors[index].unk_06       = i;
            work                                = g_Task;
            g_SpawnedActors[index].pos.x.fixed  = work->pos.x.fixed;
            g_SpawnedActors[index].pos.y.fixed  = work->pos.y.fixed;
            g_SpawnedActors[index].pos.z.fixed  = work->pos.z.fixed;
        }
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 12));
    if (g_Task->param.unk_0B != 0) {
        g_AreaCameraRefreshCount = 3;
        g_AreaCameraOffsetZ      = (g_AreaCameraOffsetZ - 0x80);
        g_Task->header.step      = (g_Task->header.step + 1);
        return;
    }
    Actor_Clear();
}
