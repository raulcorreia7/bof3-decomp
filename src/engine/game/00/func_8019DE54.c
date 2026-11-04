#include "game_00.h"

/* K&R call keeps a0 undisturbed; the callee ignores its mode argument. */

MATCH void func_8019DE54(void) {
    s32    i;
    u8     index;
    Actor* work;

    for (i = 0; i < 10; i++) {
        index = Actor_FindFreeSlot() & BYTE_MASK;
        if (index != GAME_NONE) {
            g_ActorSlots[index].flags_00 = 1;
            g_ActorSlots[index].type     = 0x34;
            g_ActorSlots[index].unk_02   = 2;
            g_ActorSlots[index].unk_06   = i;
            work                         = g_SpadWork;
            g_ActorSlots[index].x.fixed  = work->x.fixed;
            g_ActorSlots[index].y.fixed  = work->y.fixed;
            g_ActorSlots[index].z.fixed  = work->z.fixed;
        }
    }
    SND_PlayCue(EMI_CUE_ID(1, 12));
    if (g_SpadWork->unk_0B != 0) {
        g_AreaCameraRefreshCount = 3;
        g_AreaCameraOffsetZ      = (s16)(g_AreaCameraOffsetZ - 0x80);
        g_SpadWork->state_02     = (u8)(g_SpadWork->state_02 + 1);
        return;
    }
    Actor_Clear();
}
