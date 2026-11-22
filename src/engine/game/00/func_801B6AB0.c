#include "game_00.h"

MATCH void func_801B6AB0(void) {
    s32 x;

    x = TASK(Actor)->pos.x.fixed;
    if ((((x & 0x7FFF) != 0) || ((TASK(Actor)->pos.y.fixed & 0x7FFF) != 0)) && ((TASK(Actor)->active_flags & 0x20) == 0)) {
        TASK(Actor)->pos.x.fixed      = (x + 0x4800) & ~0x7FFF;
        TASK(Actor)->pos.y.fixed      = (TASK(Actor)->pos.y.fixed + 0x4800) & ~0x7FFF;
        COORD_INT(TASK(Actor)->pos.z) = Area_HeightReadStep(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->direction);
        Script_Request((TASK(Actor)->direction + 8) & BYTE_MASK);
        if (((TASK(Actor)->pos.x.fixed & 0x7FFF) == 0) && ((TASK(Actor)->pos.y.fixed & 0x7FFF) == 0)) {
            Script_Request(TASK(Actor)->direction);
        }
    } else {
        Actor_ClearVelocity();
        TASK(Actor)->unk_03++;
        func_801B6BC8();
    }
}
