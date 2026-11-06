#include "game_00.h"

MATCH void func_801B016C(void) {
    Actor* work;
    Actor* work2;
    Actor* pos;

    Actor_ClearVelocity();
    work          = g_Task;
    work->unk_09  = 0;
    work2         = g_Task;
    work->unk_18  = 0;
    work->unk_1C  = 0;
    work->gravity = 0;
    work2->unk_0A = 0;

    g_Task->unk_06       = 0;
    g_Task->option_flags = 0;
    g_Task->unk_0B       = 0;

    pos                               = g_Task;
    COORD_INT(g_Task->z)              = Area_ReadHeight(pos->x.fixed, pos->y.fixed);
    g_GameState->counter_11C.s8_value = 3;
    g_GameState->step_12A.s8_value    = 0;
    g_GameState->mode_12B.s8_value    = 0;
    g_GameState->flags_12C.s8_value   = 0;
    g_Task->unk_4B                    = 0xFF;
    if (g_GameRequestFlags & 0x20) {
        g_Task->flags |= ACTOR_FLAG_HIDDEN;
        g_Task->mode = 0xC;
    } else if (LOHU(g_GameAreaId) == 0xBD) {
        g_Task->flags |= ACTOR_FLAG_HIDDEN;
        g_Task->mode = 0xD;
    } else {
        func_801B5BDC(g_Task->direction_08);
        g_Task->mode = g_Task->mode + 1;
    }
    ACTOR_CLEAR_STEP();
}
