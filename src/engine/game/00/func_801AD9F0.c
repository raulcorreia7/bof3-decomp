#include "game_00.h"

MATCH void func_801AD9F0(void) {
    Actor* work;
    Actor* area;
    s8     count;

    work  = g_Task;
    count = work->tint.signed_bytes.delta.red;
    if (count == 0) {
        if ((work->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
            Actor_DispatchSelectorScript(work->direction_08);
        }
        area = (Actor*)GAME_WORK_AREA_PTR;
        area->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
        g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
        area         = g_Task;
        area->unk_04 = 0;
    } else {
        work->tint.signed_bytes.delta.red = (count + 0x10);
        work                              = g_Task;
        work->tint.bytes.rgb.blue         = (work->tint.bytes.rgb.blue + 0x10);
        work                              = g_Task;
        work->tint.bytes.rgb.green        = (work->tint.bytes.rgb.green + 0x10);
    }
}
