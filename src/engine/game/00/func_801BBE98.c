#include "game_00.h"

MATCH void func_801BBE98(void) {
    Actor* work;
    Actor* work2;
    /* FAKE: post-call reload must land in a0 for the retail schedule. */
    MATCH_REG(Actor*, ptr, "a0");
    s16 ret;

    Actor_ClearVelocity();

    work                = g_Task;
    work->unk_06        = work->unk_05 - 1;
    work2               = g_Task;
    work->unk_18        = 0;
    work->unk_1C        = 0;
    work->gravity       = 0;
    work2->option_flags = 0;

    work2 = g_Task;
    ret   = Area_ReadHeight(work2->x.fixed, work2->y.fixed);

    work                      = g_Task;
    work->tint.bytes.unk_5D   = 0;
    ptr                       = g_Task;
    COORD_INT(work->z)      = ret;
    ptr->tint.bytes.unk_5E    = 0;
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->tint.bytes.flags  = 2;

    g_GameState->counter_11C.s8_value = 3;
    g_GameState->mode_12B.s8_value    = 0;
    g_GameState->step_12A.s8_value    = 0;

    Actor_SelectScript(g_Task->direction_08);

    work = g_Task;
    work->mode++;
    ACTOR_CLEAR_STATE();
}
