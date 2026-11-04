#include "game_00.h"

MATCH void func_801B016C(void) {
    Actor* work;
    Actor* work2;
    Actor* pos;

    Actor_ClearVelocity();
    work          = g_SpadWork;
    work->unk_09  = 0;
    work2         = g_SpadWork;
    work->unk_18  = 0;
    work->unk_1C  = 0;
    work->gravity = 0;
    work2->unk_0A = 0;

    g_SpadWork->unk_06       = 0;
    g_SpadWork->option_flags = 0;
    g_SpadWork->unk_0B       = 0;

    pos                               = g_SpadWork;
    g_SpadWork->z.part.integer        = Area_ReadHeight(pos->x.fixed, pos->y.fixed);
    g_GameState->counter_11C.s8_value = 3;
    g_GameState->step_12A.s8_value    = 0;
    g_GameState->mode_12B.s8_value    = 0;
    g_GameState->flags_12C.s8_value   = 0;
    g_SpadWork->unk_4B                = 0xFF;
    if (g_GameRequestFlags & 0x20) {
        g_SpadWork->flags_00 |= ACTOR_FLAG_HIDDEN;
        g_SpadWork->unk_01 = 0xC;
    } else if (LOHU(g_GameAreaId) == 0xBD) {
        g_SpadWork->flags_00 |= ACTOR_FLAG_HIDDEN;
        g_SpadWork->unk_01 = 0xD;
    } else {
        func_801B5BDC(g_SpadWork->direction_08);
        g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
    }
    ACTOR_CLEAR_STATE();
}
