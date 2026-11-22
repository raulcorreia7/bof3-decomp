#include "game_00.h"

MATCH void func_801A4B80(s32 index) {
    s32 slot;

    slot                             = index & BYTE_MASK;
    g_ActorTurnRamps[slot].frames_xy = 0;
    g_ActorTurnRamps[slot].frames_z  = 0;
    g_ActorTurnRamps[slot].unk_03    = 0;
    g_ActorTurnRamps[slot].flags     = 0;
}
