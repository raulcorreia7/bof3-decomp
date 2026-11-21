#include "game_00.h"

MATCH void func_801B70D4(void) {
    Actor* work;
    s32    delta[3];

    if (g_Task->timer == 0) {
        g_Task->active_flags |= 0x20;
        work              = g_Task;
        work->pos.x.fixed = g_PartyActors[work->unk_18].pos.x.fixed;
        work->pos.y.fixed = g_PartyActors[work->unk_18].pos.y.fixed;
        work->pos.z.fixed = FIELD(s32, &D_80147A94, work->unk_18 * ACTOR_SIZE);
        work->unk_64      = g_PartyActors[work->unk_18].unk_64;
        work->unk_68      = g_PartyActors[work->unk_18].unk_68;
        work->unk_6C      = g_PartyActors[work->unk_18].unk_6C;
        func_801AC1DC(delta, FIELD(u8, g_Task, 0x1Cu));
        work = g_Task;
        work->pos.x.fixed += delta[0];
        work->pos.y.fixed += delta[1];
        COORD_INT(work->pos.z) += delta[2];
    }
    func_801B6A04();
}
