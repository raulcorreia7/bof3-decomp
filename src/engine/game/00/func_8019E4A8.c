#include "game_00.h"

MATCH void func_8019E4A8(void) {
    Actor* work;
    u8     index;

    g_Task->unk_09 += 1;
    work = g_Task;
    if (work->unk_09 == 4) {
        work->unk_09 = 0;
        index        = Actor_FindFreeSlot(work);
        if (index != GAME_NONE) {
            g_ActorSlots[index].flags   = 1;
            g_ActorSlots[index].type    = ACCESSORY_COUNT;
            g_ActorSlots[index].mode    = 2;
            g_ActorSlots[index].step    = 2;
            work                        = g_Task;
            g_ActorSlots[index].x.fixed = work->x.fixed;
            g_ActorSlots[index].y.fixed = work->y.fixed;
            g_ActorSlots[index].z.fixed = work->z.fixed;
        }
        g_Task->unk_0A -= 1;
        if (g_Task->unk_0A == 0) {
            Actor_Clear();
        }
    }
}
