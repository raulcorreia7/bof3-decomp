#include "engine/game/00/game_00.h"

/* func_801A22CC */
/* Pace of step 4: adds one move to the move counter when bit 0 of the party step count changed. */
MATCH s32 Actor_PaceByPartyStep(Actor* value_a, s32 value_b, u8 flag_bits) {
    return Game_AddStepByFlag(1u, value_a, value_b, flag_bits);
}
