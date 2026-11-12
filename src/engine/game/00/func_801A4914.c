#include "game_00.h"

MATCH void func_801A4914(void) {
    Actor* work;
    u8     flags;

    g_Task->unk_4B = 0xFF;
    work           = g_Task;
    flags          = work->option_flags;
    if (flags & ACTOR_OPT_ROUTE_LOCKED) {
        work->unk_2A = (flags >> 4) & 0x1;
        Actor_SelectScript(g_Task->direction_08);
        return;
    }
    func_8015BAC4(work->direction_08);
}
