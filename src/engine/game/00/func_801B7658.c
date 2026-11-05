#include "game_00.h"

MATCH void func_801B7658(void) {
    u8 count;

    count = g_SpadWork->unk_09;
    if (count == 0) {
        g_SpadWork->vx     = 0;
        g_SpadWork->vy     = 0;
        g_SpadWork->unk_03 = 3;
    } else {
        g_SpadWork->unk_09 = (u8)(count - 1);
    }
    g_SpadWork->vz += g_SpadWork->gravity;
    func_801B0DFC();
    if (g_SpadWork->unk_05 == 0) {
        Area_AdvanceScroll(g_SpadWork->z.part.integer);
    }
    func_8014D978();
}
