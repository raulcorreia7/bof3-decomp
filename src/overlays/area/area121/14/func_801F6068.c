#include "area121_14.h"

MATCH void func_801F6068(void) {
    u8 count;

    count = SELF(Actor)->unk_0A;
    if (count == 0) {
        SELF(Actor)->pos.x.fixed = g_Game.members[0].pos.x.fixed;
        SELF(Actor)->pos.y.fixed = g_Game.members[0].pos.y.fixed;
        SELF(Actor)->pos.z.fixed = g_Game.members[0].pos.z.fixed + TO_COORD(128);
        func_801F60F4(g_Self);
        SELF(Actor)->header.mode += 1;
        return;
    }
    SELF(Actor)->unk_0A = count - 1;
}
