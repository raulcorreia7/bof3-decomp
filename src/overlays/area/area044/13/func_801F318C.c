#include "area044_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F318C(u8 facing, u8 actor_index) {
    Actor* actor;
    u8     i;
    s8     slot;

    g_PartyActors[actor_index].vx    = g_FacingSteps[facing].x >> 2;
    g_PartyActors[actor_index].vz    = 0;
    g_PartyActors[actor_index].timer = 0x20;
    g_PartyActors[actor_index].vy    = g_FacingStepY[facing * 2] >> 2;
    for (i = 1; i < g_Game.party_size; i++) {
        TASK_SET(&g_Game.members[i]);
        slot = func_8014DE78() - 0x1E;
        if (slot != actor_index) {
            continue;
        }
        actor = g_Task;
        if (actor->timer != 0) {
            actor->pos.x.fixed += actor->vx * actor->timer;
            actor->pos.y.fixed += actor->vy * actor->timer;
            actor->pos.z.fixed += actor->vz * actor->timer;
        }
        setVector(TASK(Actor), g_PartyActors[actor_index].vx, g_PartyActors[actor_index].vy, g_PartyActors[actor_index].vz);
        TASK(Actor)->timer       = 0x20;
        TASK(Actor)->header.mode = 1;
        TASK(Actor)->header.step = 1;
    }
}
#else
INCLUDE_ASM(func_801F318C);
#endif
