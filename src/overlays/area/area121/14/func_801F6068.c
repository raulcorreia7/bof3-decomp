#include "area121_14.h"

MATCH void func_801F6068(void) {
    u8 count;

    count = g_Task->unk_0A;
    if (count == 0) {
        g_Task->pos.x.fixed = g_Game.members[0].pos.x.fixed;
        g_Task->pos.y.fixed = g_Game.members[0].pos.y.fixed;
        g_Task->pos.z.fixed = g_Game.members[0].pos.z.fixed + TO_COORD(128);
        func_801F60F4(g_Task);
        g_Task->header.mode += 1;
        return;
    }
    g_Task->unk_0A = count - 1;
}
