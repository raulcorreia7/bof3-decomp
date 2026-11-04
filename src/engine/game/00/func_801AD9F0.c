#include "game_00.h"

MATCH void func_801AD9F0(void) {
    Actor* work;
    Actor* area;
    s8     count;

    work  = g_SpadWork;
    count = work->tint.signed_bytes.unk_5D;
    if (count == 0) {
        if ((work->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
            func_8015BAC4(work->direction_08);
        }
        area = (Actor*)GAME_WORK_AREA_PTR;
        area->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING;
        g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
        area         = g_SpadWork;
        area->unk_04 = 0;
    } else {
        work->tint.signed_bytes.unk_5D = (s8)(count + 0x10);
        work                           = g_SpadWork;
        work->tint.bytes.unk_5F        = (u8)(work->tint.bytes.unk_5F + 0x10);
        work                           = g_SpadWork;
        work->tint.bytes.unk_5E        = (u8)(work->tint.bytes.unk_5E + 0x10);
    }
}
