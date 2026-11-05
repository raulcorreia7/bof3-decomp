#include "game_00.h"

MATCH void func_801B9478(void) {
    Actor* work;
    Actor* flag_work;
    u8     countdown;

    if (g_Task->unk_09 != 0) {
        func_801C57B4();
        work         = g_Task;
        work->unk_09 = (u8)(work->unk_09 - 1);
        if (g_Task->unk_09 == 0) {
            Actor_ClearVelocity();
        }
    }
    work      = g_Task;
    countdown = work->unk_0A;
    if (countdown != 0) {
        work->unk_0A = (u8)(countdown - 1);
        flag_work    = g_Task;
        if (flag_work->unk_0A & 1) {
            flag_work->flags = (u8)(flag_work->flags & ~ACTOR_FLAG_HIDDEN);
            return;
        }
        flag_work->flags = (u8)(flag_work->flags | ACTOR_FLAG_HIDDEN);
        return;
    }
    work->flags    = (u8)(work->flags & ~ACTOR_FLAG_HIDDEN);
    g_Task->mode   = 1;
    g_Task->step   = 0;
    g_Task->unk_03 = 0;
}
