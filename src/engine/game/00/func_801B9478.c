#include "game_00.h"

MATCH void func_801B9478(void) {
    Actor* work;
    Actor* flag_work;
    u8     countdown;

    if (g_Task->timer != 0) {
        Actor_Move();
        work        = g_Task;
        work->timer = (work->timer - 1);
        if (g_Task->timer == 0) {
            Actor_ClearVelocity();
        }
    }
    work      = g_Task;
    countdown = work->unk_0A;
    if (countdown != 0) {
        work->unk_0A = (countdown - 1);
        flag_work    = g_Task;
        if (flag_work->unk_0A & 0x1) {
            flag_work->header.flags = (flag_work->header.flags & ~ACTOR_FLAG_HIDDEN);
            return;
        }
        flag_work->header.flags = (flag_work->header.flags | ACTOR_FLAG_HIDDEN);
        return;
    }
    work->header.flags  = (work->header.flags & ~ACTOR_FLAG_HIDDEN);
    g_Task->header.mode = 1;
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}
