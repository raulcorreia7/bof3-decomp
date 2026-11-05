#include "battle_03.h"

MATCH void func_801E347C(void) {
    PartyBattler* work;
    s32           old38;
    s32           old34;

    work = g_Task;
    work->flags &= ~ACTOR_FLAG_HIDDEN;
    func_801E2314(0);
    old34          = g_Task->pos.x.raw;
    old38          = g_Task->pos.y.raw;
    g_Task->unk_0C = 0x80000;
    g_Task->unk_10 = 0;
    g_Task->unk_18 = old34;
    work           = g_Task;
    work->unk_1C   = old38;
    func_801DD350((s32)work);
    {
        s32 dx;
        s32 dy;
        s32 depth;

        depth          = g_Task->pos.x.raw;
        dx             = g_Task->unk_0C;
        dy             = g_Task->unk_10;
        g_Task->unk_0C = 0x8000;
        g_Task->unk_10 = 0;
        depth -= dx;
        ((volatile PartyBattler*)g_Task)->pos.x.raw = depth;
        depth -= dy;
        work            = g_Task;
        work->pos.x.raw = depth;
        func_801DD350((s32)work);
    }
    work       = g_Task;
    work->step = work->step + 1;
}
