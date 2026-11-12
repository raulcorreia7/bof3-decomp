#include "area085_13.h"

MATCH void func_801F2FCC(void) {
    Actor* actor;
    Actor* record;
    s32    i;

    actor = g_Task;
    i     = 0;
    do {
        record = &g_Actors[i & BYTE_MASK];
        g_Task = record;
        if (record->header.flags & 0x1) {
            record->draw_layer = 5;
            func_8014D290();
        }
        i += 1;
    } while ((i & BYTE_MASK) < 0x1EU);
    g_Task                   = (Actor*)&g_Game;
    g_Game.members[0].unk_29 = 5;
    func_8014D290();
    g_Task = actor;
}
