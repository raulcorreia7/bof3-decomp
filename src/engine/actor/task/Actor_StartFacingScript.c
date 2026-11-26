#include "engine/game/00/game_00.h"

/* func_801A4914 */
/* Selects the animation script for the current actor's facing, mirrored by its option flags when route-locked. */
MATCH void Actor_StartFacingScript(void) {
    Actor* work;
    u8     flags;

    SELF(Actor)->script_record = 0xFF;
    work                       = SELF(Actor);
    flags                      = work->option_flags;
    if (flags & ACTOR_OPT_ROUTE_LOCKED) {
        work->mirror = (flags >> 4) & 0x1;
        Script_Select(SELF(Actor)->direction);
        return;
    }
    Script_DispatchSelector(work->direction);
}
