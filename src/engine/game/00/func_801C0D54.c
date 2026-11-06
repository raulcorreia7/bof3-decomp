#include "game_00.h"

MATCH void func_801C0D54(void) {
    u8 arg;

    if (func_801C0E48() & 0xFF) {
        arg = 0x3B;
        if (g_Task->direction_08 == 3)
            arg = 0x3A;
        Actor_RequestScript(arg);
        g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
        COORD_INT(g_Task->pos.z) = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) + 0x7D0;
        Actor_ClearVelocity();
        g_Task->gravity     = -8;
        g_Task->header.mode = 2;
        g_Task->header.step = 3;
        g_Task->unk_03      = 3;
        g_GameState->flags_12C.u8_value &= 0xFD;
    }
}
