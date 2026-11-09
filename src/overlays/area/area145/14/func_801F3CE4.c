#include "area145_14.h"

MATCH void func_801F3CE4(void) {
    u8*          index;
    s32          offset;
    s32          delta;
    ScriptState* state;

    index                          = &D_1F800001;
    *index                         = (s32)(-(((s32)g_CurrentActor - (s32)D_80147A58) * 0xD79435E5)) >> 3;
    D_80147CBA[*index * 0x10]      = 0x10;
    D_80147CB9[*index * 0x10]      = 0;
    offset                         = *index * 0x10;
    delta                          = 0x200 / D_80147CBA[offset];
    state                          = g_ScriptState;
    FIELD(s32, D_80147CC4, offset) = delta;
    state->flag_00 |= 8;
}
