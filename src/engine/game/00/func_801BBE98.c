#include "game_00.h"

MATCH void func_801BBE98(void) {
    Actor* work;
    Actor* work2;
    /* FAKE: post-call reload must land in a0 for the retail schedule. */
    MATCH_REG(Actor*, ptr, "a0");
    s16 ret;

    Actor_ClearVelocity();

    work                = g_SpadWork;
    work->unk_06        = work->unk_05 - 1;
    work2               = g_SpadWork;
    work->unk_18        = 0;
    work->unk_1C        = 0;
    work->gravity       = 0;
    work2->option_flags = 0;

    work2 = g_SpadWork;
    ret   = Area_ReadHeight(work2->x.fixed, work2->y.fixed);

    work                          = g_SpadWork;
    work->tint.bytes.unk_5D       = 0;
    ptr                           = g_SpadWork;
    work->z.part.integer          = ret;
    ptr->tint.bytes.unk_5E        = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;
    g_SpadWork->tint.bytes.flags  = 2;

    g_GameState->counter_11C.s8_value = 3;
    g_GameState->mode_12B.s8_value    = 0;
    g_GameState->step_12A.s8_value    = 0;

    Actor_SelectScript(g_SpadWork->direction_08);

    work = g_SpadWork;
    work->unk_01++;
    ACTOR_CLEAR_STATE();
}
