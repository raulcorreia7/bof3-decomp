#include "area085_13.h"

MATCH void func_801F2FCC(void) {
    Actor* actor;
    Actor* record;
    s32    i;

    actor = SELF(Actor);
    i     = 0;
    do {
        record = &g_Actors[i & BYTE_MASK];
        g_Self = record;
        if (record->header.flags & 0x1) {
            record->draw_layer = 5;
            Area_AddGridActor();
        }
        i += 1;
    } while ((i & BYTE_MASK) < 0x1EU);
    g_Self                   = (Actor*)&g_Game;
    g_Game.members[0].unk_29 = 5;
    Area_AddGridActor();
    g_Self = actor;
}
