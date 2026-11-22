#include "area121_14.h"

MATCH void func_801F6068(void) {
    u8 count;

    count = TASK(Actor)->unk_0A;
    if (count == 0) {
        TASK(Actor)->pos.x.fixed = g_Game.members[0].pos.x.fixed;
        TASK(Actor)->pos.y.fixed = g_Game.members[0].pos.y.fixed;
        TASK(Actor)->pos.z.fixed = g_Game.members[0].pos.z.fixed + TO_COORD(128);
        func_801F60F4(g_Task);
        TASK(Actor)->header.mode += 1;
        return;
    }
    TASK(Actor)->unk_0A = count - 1;
}
