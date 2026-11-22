#include "game_00.h"

MATCH void func_801A3D1C(void* unused) {
    Actor* work;
    s32    slot;
    s32    index;
    s8     n;
    s8     old_a;
    s8     old_b;

    if (g_Task->unk_06 == 0x0A) {
        slot = (s32)(-(((s32)g_CurrentActor - (s32)g_PartyActors) * 0xD79435E5)) >> 3;
        n    = slot;
        if (n < 0) {
            n = 4;
        }
        index = n;
        old_a = g_ActorTurnRamps[index].frames_xy;
        if (old_a != 0) {
            g_ActorTurnRamps[index].frames_xy = old_a - 1;
            work                              = g_Task;
            work->unk_64 += g_ActorTurnRamps[index].step_x;
            work->unk_68 += g_ActorTurnRamps[index].step_y;
        }
        old_b = g_ActorTurnRamps[index].frames_z;
        if (old_b != 0) {
            g_ActorTurnRamps[index].frames_z = old_b - 1;
            work                             = g_Task;
            work->unk_6C += g_ActorTurnRamps[index].step_z;
        }
    }
}
