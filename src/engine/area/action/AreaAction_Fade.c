#include "engine/game/00/game_00.h"

/* func_801AD9F0 */
MATCH void AreaAction_Fade(void) {
    Actor* work;
    Actor* area;
    s8     count;

    work  = SELF(Actor);
    count = work->tint.steps.delta.r;
    if (count == 0) {
        if ((work->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
            Script_DispatchSelector(work->direction);
        }
        area = (Actor*)GAME_WORK_AREA_PTR;
        area->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
        g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
        area         = SELF(Actor);
        area->unk_04 = 0;
    } else {
        work->tint.steps.delta.r = (count + 0x10);
        work                     = SELF(Actor);
        work->tint.bytes.rgb.b   = (work->tint.bytes.rgb.b + 0x10);
        work                     = SELF(Actor);
        work->tint.bytes.rgb.g   = (work->tint.bytes.rgb.g + 0x10);
    }
}
