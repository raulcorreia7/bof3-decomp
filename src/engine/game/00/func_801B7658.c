#include "game_00.h"

MATCH void func_801B7658(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count == 0) {
        g_Task->vx     = 0;
        g_Task->vy     = 0;
        g_Task->unk_03 = 3;
    } else {
        g_Task->unk_09 = (count - 1);
    }
    g_Task->vz += g_Task->gravity;
    func_801B0DFC();
    if (g_Task->unk_05 == 0) {
        Area_AdvanceScroll(g_Task->z.part.integer);
    }
    func_8014D978();
}
