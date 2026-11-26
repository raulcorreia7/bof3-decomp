#include "area099_13.h"

/* Advances the actor by its velocity, damps vz by 0x700 and requests script 0x51 when it lands. */
MATCH void func_801F2FD4(void) {
    Actor* actor;
    Actor* task;
    /* FAKE: retail keeps the mode byte in a2 and the x velocity in a0; against 53 instructions the pure-C best leaves 7 rows. */
    FAKE_REG(u8, mode, "a2");
    s32 x;
    FAKE_REG(s32, vx, "a0");
    s32 y;
    s32 vy;
    s32 vz;

    actor = g_Task;
    x     = actor->pos.x.fixed;
    mode  = actor->unk_0A;
    /* FAKE: the barrier keeps the mode load above the vx load. */
    FAKE_BARRIER();
    vx                 = actor->vx;
    vy                 = actor->vy;
    actor->pos.x.fixed = x + vx;
    y                  = actor->pos.y.fixed;
    vz                 = actor->vz;
    actor->unk_0A      = mode - 1;
    actor->pos.y.fixed = y + vy;
    COORD_INT(actor->pos.z) += actor->vz >> 8;
    actor->vz = vz - 0x700;
    if (vz > 0 && TASK(Actor)->vz < 0) {
        Script_Request(0x51);
    }
    task = g_Task;
    if (task->unk_0A == 0) {
        task->unk_04 = 0;
    } else {
        g_Game.current->u.field.unk_122 -= 2;
    }
}
