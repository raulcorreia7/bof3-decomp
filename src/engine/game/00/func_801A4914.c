#include "game_00.h"

MATCH void func_801A4914(void) {
    Actor* work;
    u8     flags;

    g_SpadWork->unk_4B = 0xFF;
    work               = g_SpadWork;
    flags              = work->option_flags;
    if (flags & ACTOR_OPT_ROUTE_LOCKED) {
        work->unk_2A = (flags >> 4) & 1;
        Actor_SelectScript(g_SpadWork->direction_08);
        return;
    }
    func_8015BAC4(work->direction_08);
}
