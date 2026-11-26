#include "engine/game/00/game_00.h"

/* func_801B80B4 */
/* Steps the dismount frames, then returns the actor to mode 1. */
MATCH void Party_LadderDownDismount(void) {
    s32 next_step;

    SELF(Actor)->timer = (SELF(Actor)->timer - 1);
    if (SELF(Actor)->timer != 0) {
        return;
    }
    SELF(Actor)->unk_0A = (SELF(Actor)->unk_0A + 1);
    if (SELF(Actor)->direction == FACING_RIGHT) {
        next_step = 7;
        next_step -= SELF(Actor)->unk_0A;
    } else {
        next_step = SELF(Actor)->unk_0A;
        next_step += 1;
    }
    Script_Request(next_step);
    if (SELF(Actor)->unk_0A == 4) {
        if (SELF(Actor)->unk_05 == 0) {
            g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
        }
        SELF(Actor)->timer       = 0;
        SELF(Actor)->unk_0A      = 0;
        SELF(Actor)->header.mode = 1;
        ACTOR_CLEAR_STEP();
        SELF(Actor)->unk_03 = 0;
        SELF(Actor)->unk_04 = 0;
    } else {
        SELF(Actor)->timer = 2;
    }
}
