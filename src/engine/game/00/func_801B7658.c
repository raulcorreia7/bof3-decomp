#include "game_00.h"

MATCH void func_801B7658(void) {
    u8 count;

    count = TASK(Actor)->timer;
    if (count == 0) {
        TASK(Actor)->vx     = 0;
        TASK(Actor)->vy     = 0;
        TASK(Actor)->unk_03 = 3;
    } else {
        TASK(Actor)->timer = (count - 1);
    }
    TASK(Actor)->vz += TASK(Actor)->gravity;
    Actor_MovementUpdate();
    if (TASK(Actor)->unk_05 == 0) {
        Area_ScrollAdvance(COORD_INT(TASK(Actor)->pos.z));
    }
    Script_AnimStepLoop();
}
