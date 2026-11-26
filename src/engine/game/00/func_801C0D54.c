#include "game_00.h"

MATCH void func_801C0D54(void) {
    u8 arg;

    if (func_801C0E48() & BYTE_MASK) {
        arg = 0x3B;
        if (SELF(Actor)->direction == FACING_RIGHT)
            arg = 0x3A;
        Script_Request(arg);
        SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        COORD_INT(SELF(Actor)->pos.z) = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) + 0x7D0;
        Actor_ClearVelocity();
        SELF(Actor)->gravity     = -8;
        SELF(Actor)->header.mode = 2;
        SELF(Actor)->header.step = 3;
        SELF(Actor)->unk_03      = 3;
        g_Game.current->status.field.flags.unsigned_value &= 0xFD;
    }
}
