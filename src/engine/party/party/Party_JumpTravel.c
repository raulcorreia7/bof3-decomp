#include "engine/game/00/game_00.h"

/* func_801B7658 */
/* Carries the actor through the air for its remaining travel frames. */
MATCH void Party_JumpTravel(void) {
    u8 count;

    count = SELF(Actor)->timer;
    if (count == 0) {
        SELF(Actor)->vx     = 0;
        SELF(Actor)->vy     = 0;
        SELF(Actor)->unk_03 = PARTY_JUMP_STEP_FALL;
    } else {
        SELF(Actor)->timer = (count - 1);
    }
    SELF(Actor)->vz += SELF(Actor)->gravity;
    Actor_MovementUpdate();
    if (SELF(Actor)->unk_05 == 0) {
        Area_ScrollAdvance(COORD_INT(SELF(Actor)->pos.z));
    }
    Script_AnimStepLoop();
}
