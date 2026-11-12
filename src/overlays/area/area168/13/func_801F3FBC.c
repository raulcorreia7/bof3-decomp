#include "area168_13.h"

MATCH void func_801F3FBC(void) {
    s32 found;
    s32 i;

    found = 0;
    for (i = 0; i < 3; i++) {
        if (g_Game.members[i].header.flags == 0) {
            continue;
        }
        if (abs(g_Game.members[i].pos.y.fixed - ((s32)COORD_INT(g_Task->pos.y) << 16)) > TO_COORD_HALF(2)) {
            continue;
        }
        if (abs(g_Game.members[i].pos.x.fixed - ((s32)COORD_INT(g_Task->pos.x) << 16)) <= TO_COORD(2) ||
            abs(g_Game.members[i].pos.x.fixed - (((s32)COORD_INT(g_Task->pos.x) + 1) << 16)) <= TO_COORD(2)) {
            found = 1;
        }
    }
    if (!found) {
        g_Task->header.step += 1;
    }
    func_801F4158_area168(0, 0);
    func_801F4158_area168(1, 3);
}
