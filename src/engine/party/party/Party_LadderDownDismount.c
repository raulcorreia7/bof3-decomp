#include "engine/game/00/game_00.h"

/* func_801B80B4 */
/* Steps the dismount frames, then returns the actor to mode 1. */
MATCH void Party_LadderDownDismount(void) {
    s32 next_step;

    TASK(Actor)->timer = (TASK(Actor)->timer - 1);
    if (TASK(Actor)->timer != 0) {
        return;
    }
    TASK(Actor)->unk_0A = (TASK(Actor)->unk_0A + 1);
    if (TASK(Actor)->direction == FACING_RIGHT) {
        next_step = 7;
        next_step -= TASK(Actor)->unk_0A;
    } else {
        next_step = TASK(Actor)->unk_0A;
        next_step += 1;
    }
    Script_Request(next_step);
    if (TASK(Actor)->unk_0A == 4) {
        if (TASK(Actor)->unk_05 == 0) {
            g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
        }
        TASK(Actor)->timer       = 0;
        TASK(Actor)->unk_0A      = 0;
        TASK(Actor)->header.mode = 1;
        ACTOR_CLEAR_STEP();
        TASK(Actor)->unk_03 = 0;
        TASK(Actor)->unk_04 = 0;
    } else {
        TASK(Actor)->timer = 2;
    }
}
