#include "area117_13.h"

MATCH void func_801F2F5C(void) {
    if (abs(g_Game.members[0].pos.x.fixed - TO_COORD_HALF(2)) > TO_COORD_HALF(1)) {
        goto set;
    }
    if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(0x15)) <= TO_COORD_HALF(1)) {
        goto done;
    }
    if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(0x16)) <= TO_COORD_HALF(1)) {
        goto done;
    }
set:
    g_Task->header.step = 4;
done:
    if (g_AreaSceneMode != 0) {
        g_Task->header.step = 3;
    }
    func_801F314C();
}
