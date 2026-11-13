#include "battle_03.h"

MATCH void func_801E347C(void) {
    PartyMember* work;
    s32          old38;
    s32          old34;

    work = g_Task;
    work->header.flags &= ~ACTOR_FLAG_HIDDEN;
    func_801E2314(0);
    old34          = g_Task->pos.x.fixed;
    old38          = g_Task->pos.y.fixed;
    g_Task->unk_0C = 0x80000;
    g_Task->unk_10 = 0;
    g_Task->unk_18 = old34;
    work           = g_Task;
    work->unk_1C   = old38;
    Effect_RotatePosition(work);
    {
        s32 dx;
        s32 dy;
        s32 depth;

        depth          = g_Task->pos.x.fixed;
        dx             = g_Task->unk_0C;
        dy             = g_Task->unk_10;
        g_Task->unk_0C = 0x8000;
        g_Task->unk_10 = 0;
        depth -= dx;
        ((volatile PartyMember*)g_Task)->pos.x.fixed = depth;
        depth -= dy;
        work              = g_Task;
        work->pos.x.fixed = depth;
        Effect_RotatePosition(work);
    }
    work              = g_Task;
    work->header.step = work->header.step + 1;
}
