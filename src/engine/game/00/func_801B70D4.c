#include "game_00.h"

MATCH void func_801B70D4(void) {
    Actor* work;
    s32    delta[3];

    if (g_Task->unk_09 == 0) {
        g_Task->flags_24 |= 0x20;
        work          = g_Task;
        work->x.fixed = D_80147A58[work->unk_18].x.fixed;
        work->y.fixed = D_80147A58[work->unk_18].y.fixed;
        work->z.fixed = *(s32*)((u8*)&D_80147A94 + work->unk_18 * ACTOR_SIZE);
        work->unk_64  = D_80147A58[work->unk_18].unk_64;
        work->unk_68  = D_80147A58[work->unk_18].unk_68;
        work->unk_6C  = D_80147A58[work->unk_18].unk_6C;
        func_801AC1DC(delta, FIELD(u8, g_Task, 0x1Cu));
        work = g_Task;
        work->x.fixed += delta[0];
        work->y.fixed += delta[1];
        work->z.part.integer += delta[2];
    }
    func_801B6A04();
}
