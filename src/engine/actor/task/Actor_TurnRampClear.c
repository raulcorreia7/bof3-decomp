#include "engine/game/00/game_00.h"

/* func_801A4B80 */
/* Clears the turn ramp of one party slot. */
MATCH void Actor_TurnRampClear(s32 index) {
    s32 slot;

    slot                             = index & BYTE_MASK;
    g_ActorTurnRamps[slot].frames_xy = 0;
    g_ActorTurnRamps[slot].frames_z  = 0;
    g_ActorTurnRamps[slot].unk_03    = 0;
    g_ActorTurnRamps[slot].flags     = 0;
}
