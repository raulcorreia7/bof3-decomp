#include "engine/game/00/game_00.h"

/* func_801A3D1C */
/* Adds one frame of the current party actor's turn ramp to its angles. */
MATCH void Actor_TurnRampStep(void* unused) {
    Actor* work;
    s32    slot;
    s32    index;
    s8     n;
    s8     old_a;
    s8     old_b;

    if (SELF(Actor)->unk_06 == 0x0A) {
        slot = (s32)(-(((s32)g_CurrentActor - (s32)g_PartyActors) * 0xD79435E5)) >> 3;
        n    = slot;
        if (n < 0) {
            n = 4;
        }
        index = n;
        old_a = g_ActorTurnRamps[index].frames_xy;
        if (old_a != 0) {
            g_ActorTurnRamps[index].frames_xy = old_a - 1;
            work                              = SELF(Actor);
            work->angle_x += g_ActorTurnRamps[index].delta_x;
            work->angle_y += g_ActorTurnRamps[index].delta_y;
        }
        old_b = g_ActorTurnRamps[index].frames_z;
        if (old_b != 0) {
            g_ActorTurnRamps[index].frames_z = old_b - 1;
            work                             = SELF(Actor);
            work->angle_z += g_ActorTurnRamps[index].delta_z;
        }
    }
}
