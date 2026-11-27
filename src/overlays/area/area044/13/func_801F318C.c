#include "area044_13.h"

/* Starts a party actor walking along a facing; a member already bound to it catches up first. */
MATCH void func_801F318C(u8 facing, u8 actor_index) {
    Actor* actor;
    u8     i;
    s8     slot;
    s32    step_y;

    g_PartyActors[actor_index].vx    = ((Offset2*)g_FacingSteps)[facing].x >> 2;
    step_y                           = g_FacingStepY[facing * 2];
    g_PartyActors[actor_index].vz    = 0;
    g_PartyActors[actor_index].timer = 0x20;
    g_PartyActors[actor_index].vy    = step_y >> 2;
    for (i = 1; i < g_Game.party_size; i++) {
        SELF_SET(&g_Game.members[i]);
        slot = func_8014DE78() - 0x1E;
        if (slot != actor_index) {
            continue;
        }
        actor = SELF(Actor);
        if (actor->timer != 0) {
            actor->pos.x.fixed += actor->vx * actor->timer;
            actor->pos.y.fixed += actor->vy * actor->timer;
            actor->pos.z.fixed += actor->vz * actor->timer;
        }
        setVector(SELF(Actor), g_PartyActors[actor_index].vx, g_PartyActors[actor_index].vy, g_PartyActors[actor_index].vz);
        SELF(Actor)->timer       = 0x20;
        SELF(Actor)->header.mode = 1;
        SELF(Actor)->header.step = 1;
    }
}
