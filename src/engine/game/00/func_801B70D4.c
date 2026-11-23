#include "game_00.h"

MATCH void func_801B70D4(void) {
    Actor* work;
    s32    delta[3];

    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->active_flags |= 0x20;
        work              = TASK(Actor);
        work->pos.x.fixed = g_PartyActors[work->unk_18].pos.x.fixed;
        work->pos.y.fixed = g_PartyActors[work->unk_18].pos.y.fixed;
        work->pos.z.fixed = FIELD(s32, &g_PartyActors[0].pos.z.fixed, work->unk_18 * ACTOR_SIZE);
        work->angle_x     = g_PartyActors[work->unk_18].angle_x;
        work->angle_y     = g_PartyActors[work->unk_18].angle_y;
        work->angle_z     = g_PartyActors[work->unk_18].angle_z;
        func_801AC1DC(delta, FIELD(u8, g_Task, 0x1Cu));
        work = TASK(Actor);
        work->pos.x.fixed += delta[0];
        work->pos.y.fixed += delta[1];
        COORD_INT(work->pos.z) += delta[2];
    }
    func_801B6A04();
}
