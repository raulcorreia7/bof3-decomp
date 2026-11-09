#include "area135_14.h"

MATCH bool func_801F60E0(void) {
    u8 i;

    for (i = 0; i < g_Game.party_size; i++) {
        if ((u16)(g_Game.members[i].pos.x.part.integer - 0x2C) < 2 && (u16)(g_Game.members[i].pos.y.part.integer - 0x30) < 8) {
            return 1;
        }
    }
    return 0;
}
