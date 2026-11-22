#include "game_00.h"

MATCH void func_801C0D54(void) {
    u8 arg;

    if (func_801C0E48() & BYTE_MASK) {
        arg = 0x3B;
        if (TASK(Actor)->direction == FACING_RIGHT)
            arg = 0x3A;
        Script_Request(arg);
        TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) + 0x7D0;
        Actor_ClearVelocity();
        TASK(Actor)->gravity     = -8;
        TASK(Actor)->header.mode = 2;
        TASK(Actor)->header.step = 3;
        TASK(Actor)->unk_03      = 3;
        g_Game.current->status.field.flags.unsigned_value &= 0xFD;
    }
}
