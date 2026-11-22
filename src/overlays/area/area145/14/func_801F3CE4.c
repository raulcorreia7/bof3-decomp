#include "area145_14.h"

MATCH void func_801F3CE4(void) {
    u8*          index;
    s32          offset;
    s32          delta;
    ScriptState* state;

    index                              = &D_1F800001;
    *index                             = (s32)(-(((s32)g_CurrentActor - (s32)g_PartyActors) * 0xD79435E5)) >> 3;
    g_ActorTurnRamps[*index].frames_z  = 0x10;
    g_ActorTurnRamps[*index].frames_xy = 0;
    offset                             = *index;
    delta                              = 0x200 / g_ActorTurnRamps[offset].frames_z;
    state                              = g_ScriptState;
    g_ActorTurnRamps[offset].delta_z   = delta;
    state->flags |= 8;
}
