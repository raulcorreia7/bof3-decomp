#include "battle_03.h"

MATCH void func_801E347C(void) {
    PartyMember* work;
    s32          old38;
    s32          old34;

    work = g_Task;
    work->header.flags &= ~ACTOR_FLAG_HIDDEN;
    Battle_RequestEnemyScript(0);
    old34               = BATTLE_WORK->pos.x.fixed;
    old38               = BATTLE_WORK->pos.y.fixed;
    BATTLE_WORK->unk_0C = 0x80000;
    BATTLE_WORK->unk_10 = 0;
    BATTLE_WORK->unk_18 = old34;
    work                = g_Task;
    work->unk_1C        = old38;
    Effect_RotatePosition(work);
    {
        s32 dx;
        s32 dy;
        s32 depth;

        depth               = BATTLE_WORK->pos.x.fixed;
        dx                  = BATTLE_WORK->unk_0C;
        dy                  = BATTLE_WORK->unk_10;
        BATTLE_WORK->unk_0C = 0x8000;
        BATTLE_WORK->unk_10 = 0;
        depth -= dx;
        TASK(volatile PartyMember)->pos.x.fixed = depth;
        depth -= dy;
        work              = g_Task;
        work->pos.x.fixed = depth;
        Effect_RotatePosition(work);
    }
    work              = g_Task;
    work->header.step = work->header.step + 1;
}
