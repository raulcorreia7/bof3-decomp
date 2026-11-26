#include "area104_14.h"

MATCH void func_801F5B24(void) {
    Actor* work;
    u8     count;

    work  = SELF(Actor);
    count = work->unk_0A;
    if (count == 0) {
        work->pos.x.fixed = g_Game.members[0].pos.x.fixed;
        work->pos.y.fixed = g_Game.members[0].pos.y.fixed;
        work->pos.z.fixed = g_Game.members[0].pos.z.fixed + TO_COORD(128);
        func_801F5BB0(work);
        SELF(Actor)->header.mode += 1;
        return;
    }
    work->unk_0A = count - 1;
}
