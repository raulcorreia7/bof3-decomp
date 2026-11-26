#include "engine/game/00/game_00.h"

/* func_801A239C */
/* Pace of step 5: adds two moves to the move counter when bit 0 of the party step count changed. */
MATCH s32 Actor_PaceByPartyStepDouble(Actor* value_a, s32 value_b, u8 flag_bits) {
    return Game_AddStepByFlag(2u, value_a, value_b, flag_bits);
}
