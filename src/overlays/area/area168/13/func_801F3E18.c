#include "area168_13.h"

MATCH void func_801F3E18(void) {
    bool found;
    s32  i;

    found = false;
    for (i = 0; i < 3; i++) {
        if (g_Game.members[i].header.flags == 0) {
            continue;
        }
        if (abs(g_Game.members[i].pos.y.fixed - ((s32)COORD_INT(g_Task->pos.y) << 16)) > TO_COORD_HALF(1)) {
            continue;
        }
        if (abs(g_Game.members[i].pos.x.fixed - ((s32)COORD_INT(g_Task->pos.x) << 16)) <= TO_COORD(1) ||
            abs(g_Game.members[i].pos.x.fixed - (((s32)COORD_INT(g_Task->pos.x) + 1) << 16)) <= TO_COORD(1)) {
            found = true;
        }
    }
    if (found) {
        if (g_GameStateIndex == 0) {
            SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 2));
        }
        g_Task->header.step += 1;
    }
    func_801F4158_area168(0, 1);
    func_801F4158_area168(1, 2);
}
