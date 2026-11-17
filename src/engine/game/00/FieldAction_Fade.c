#include "game_00.h"

/* func_801AD9F0 */
MATCH void FieldAction_Fade(void) {
    Actor* work;
    Actor* area;
    s8     count;

    work  = g_Task;
    count = work->tint.steps.delta.r;
    if (count == 0) {
        if ((work->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
            Actor_DispatchSelectorScript(work->direction);
        }
        area = (Actor*)GAME_WORK_AREA_PTR;
        area->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
        g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
        area         = g_Task;
        area->unk_04 = 0;
    } else {
        work->tint.steps.delta.r = (count + 0x10);
        work                     = g_Task;
        work->tint.bytes.rgb.b   = (work->tint.bytes.rgb.b + 0x10);
        work                     = g_Task;
        work->tint.bytes.rgb.g   = (work->tint.bytes.rgb.g + 0x10);
    }
}
