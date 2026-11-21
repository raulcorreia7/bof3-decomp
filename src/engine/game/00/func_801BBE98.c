#include "game_00.h"

MATCH void func_801BBE98(void) {
    Actor* work;
    Actor* work2;
    /* FAKE: post-call reload must land in a0 for the retail schedule. */
    FAKE_REG(Actor*, ptr, "a0");
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
    ret   = Area_ReadHeight(work2->pos.x.fixed, work2->pos.y.fixed);

    work                     = g_Task;
    work->tint.bytes.rgb.r   = 0;
    ptr                      = g_Task;
    COORD_INT(work->pos.z)   = ret;
    ptr->tint.bytes.rgb.g    = 0;
    g_Task->tint.bytes.rgb.b = 0;
    g_Task->tint.bytes.flags = 2;

    g_Game.current->u.field.counter.value = 3;
    g_Game.current->u.field.mode.value    = 0;
    g_Game.current->u.field.step.value    = 0;

    Script_Select(g_Task->direction);

    work = g_Task;
    work->header.mode++;
    ACTOR_CLEAR_STEP();
}
